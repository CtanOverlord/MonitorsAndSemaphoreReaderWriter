#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#include "SFML/Graphics.hpp"
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mutex>

#include <iostream>
#include <fstream>

#include <SFML/Graphics/Text.hpp>

#include <chrono>

#include "Achievement.h"

using namespace std;

sf::Font font;
sf::Text text;

std::vector<sf::Text*> texts;
std::vector<sf::Text*> achvTexts;

struct BoundedBuffer {
	std::string* buffer;
	int capacity;

	int front;
	int rear;
	int count;

	std::mutex lock;

	std::condition_variable not_full;
	std::condition_variable not_empty;

	BoundedBuffer(int capacity) : capacity(capacity), front(0), rear(0), count(0) {
		buffer = new std::string[capacity];
	}

	~BoundedBuffer() {
		delete[] buffer;
	}

	void deposit(std::string data) {
		std::unique_lock<std::mutex> l(lock);

		not_full.wait(l, [this]() {return count != capacity; });

		buffer[rear] = data;
		rear = (rear + 1) % capacity;
		++count;

		not_empty.notify_one();
	}

	std::string fetch() {
		std::unique_lock<std::mutex> l(lock);

		not_empty.wait(l, [this]() {return count != 0; });

		std::string result = buffer[front];
		front = (front + 1) % capacity;
		--count;

		not_full.notify_one();

		return result;
	}
};

void consumer(int id, BoundedBuffer& buffer) {
	while (true){
		std::string value = buffer.fetch();
		//text.setString(value);
		// Create a text
		sf::Text* temp = new sf::Text();
		temp->setFont(font);
		temp->setString(value);
		temp->setCharacterSize(30);
		temp->setStyle(sf::Text::Bold);
		temp->setColor(sf::Color::White);
		temp->setPosition(0, 0);
		texts.push_back(temp);
		//std::cout << "Consumer " << id << " fetched " << value << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void consumer2(int id, BoundedBuffer& buffer) {
	while (true) {
		std::string value = buffer.fetch();
		//text.setString(value);
		// Create a text
		sf::Text* temp = new sf::Text();
		temp->setFont(font);
		temp->setString(value);
		temp->setCharacterSize(30);
		temp->setStyle(sf::Text::Bold);
		temp->setColor(sf::Color::White);
		temp->setPosition(300, 0);
		achvTexts.push_back(temp);
		//std::cout << "Consumer " << id << " fetched " << value << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void producer(int id, BoundedBuffer& buffer) {
	/*for (int i = 0; i < 75; ++i) {
		buffer.deposit(i);
		std::cout << "Produced " << id << " produced " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}*/
}

int main()
{
	std::chrono::steady_clock myClock;
	const auto timePerTick = std::chrono::milliseconds(16);
	auto timeOfLastTick = myClock.now();

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 1000;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Monitors", sf::Style::Default, settings);

	sf::Texture playerText;

	if (!playerText.loadFromFile("Player.png"))
	{
		// error...
	}

	playerText.setSmooth(true);

	sf::Sprite playerSprite;

	playerSprite.setTexture(playerText);

	playerSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	playerSprite.setPosition(sf::Vector2f(640, 200));

	playerSprite.setOrigin(sf::Vector2f(100, 100));

	sf::View view(sf::FloatRect(640, 360, 1280, 720));

	view.setCenter(sf::Vector2f(640, 360));

	window.setView(view);

	sf::Event event;

	float acceleration = 0;

	BoundedBuffer buffer(2000);

	BoundedBuffer buffer2(2000);

	// Declare and load a font
	font.loadFromFile("arial.ttf");
	// Create a text
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	text.setPosition(0, 0);

	std::thread c1(consumer, 0, std::ref(buffer));
	std::thread c2(consumer2, 0, std::ref(buffer2));

	bool right = false;
	bool left = false;

	// Reader Writer

	vector<Achievement*> achievements;

	string line;
	ifstream myfile("achievements.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
			string temp = line;
			getline(myfile, line);
			cout << line << '\n';
			achievements.push_back(new Achievement(temp, line, "Player", playerSprite));
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	while (window.isOpen())
	{
		while (myClock.now() - timeOfLastTick >= timePerTick)
		{
			timeOfLastTick = myClock.now();

			view.setCenter(sf::Vector2f(640, 360));

			right = false;
			left = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				right = true;
				left = false;
				playerSprite.setRotation(0);
				buffer.deposit("Right");
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				//playerSprite.setPosition(playerSprite.getPosition().x - 10, playerSprite.getPosition().y);
				right = false;
				left = true;
				playerSprite.setRotation(180);
				buffer.deposit("Left");
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (playerSprite.getPosition().y >= 500)
				{
					playerSprite.setPosition(playerSprite.getPosition().x, 499);
					acceleration = -8;
					playerSprite.setRotation(270);
					buffer.deposit("Jump");
					for (int i = 0; i < achievements.size(); i++)
					{
						achievements.at(i)->jumpCount++;
					}
				}
			}

			if (right == true)
			{
				playerSprite.setPosition(playerSprite.getPosition().x + 5, playerSprite.getPosition().y);
			}
			else if (left == true)
			{
				playerSprite.setPosition(playerSprite.getPosition().x - 5, playerSprite.getPosition().y);
			}

			if (playerSprite.getPosition().y < 500)
			{
				playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + acceleration);
			}

			if (playerSprite.getPosition().y >= 500)
			{
				playerSprite.setPosition(playerSprite.getPosition().x, 500);
				acceleration = 0;
			}

			if (acceleration < 9.8)
			{
				acceleration += 0.1f;
			}

			for (int i = 0; i < texts.size(); i++)
			{
				if (texts.at(i)->getColor().a > 0)
				{
					texts.at(i)->setColor(sf::Color(255, 255, 255, texts.at(i)->getColor().a - 8));
				}
				if (texts.at(i)->getColor().a < 9)
				{
					texts.at(i)->setColor(sf::Color(255, 255, 255, 0));
				}
				texts.at(i)->setPosition(texts.at(i)->getPosition().x, texts.at(i)->getPosition().y + 7);
			}

			std::vector<sf::Text*>::iterator iter2;
			std::vector<sf::Text*>::iterator endIter2;

			iter2 = texts.begin();
			endIter2 = texts.end();

			for (; iter2 != endIter2; ++iter2)
			{
				if ((*iter2)->getColor().a <= 2)
				{
					if (texts.size() == 1)
					{
						delete texts.at(0);
						texts.clear();
						break;
					}
					else
					{
						delete (*iter2);
						iter2 = texts.erase(iter2);
						iter2 = texts.begin();
						endIter2 = texts.end();
					}
				}
			}

			for (int i = 0; i < achvTexts.size(); i++)
			{
				if (achvTexts.at(i)->getColor().a > 0)
				{
					achvTexts.at(i)->setColor(sf::Color(255, 255, 255, achvTexts.at(i)->getColor().a - 2));
				}
				if (achvTexts.at(i)->getColor().a < 3)
				{
					achvTexts.at(i)->setColor(sf::Color(255, 255, 255, 0));
				}
				achvTexts.at(i)->setPosition(achvTexts.at(i)->getPosition().x, achvTexts.at(i)->getPosition().y + 1);
			}

			std::vector<sf::Text*>::iterator iter3;
			std::vector<sf::Text*>::iterator endIter3;

			iter3 = achvTexts.begin();
			endIter3 = achvTexts.end();

			for (; iter3 != endIter3; ++iter3)
			{
				if ((*iter3)->getColor().a <= 2)
				{
					if (achvTexts.size() == 1)
					{
						delete achvTexts.at(0);
						achvTexts.clear();
						break;
					}
					else
					{
						delete (*iter3);
						iter3 = achvTexts.erase(iter3);
						iter3 = achvTexts.begin();
						endIter3 = achvTexts.end();
					}
				}
			}

			// Reader Writer

			for (int i = 0; i < achievements.size(); i++)
			{
				achievements.at(i)->Update();
			}

			for (int i = 0; i < achievements.size(); i++)
			{
				if (achievements.at(i)->complete == true)
				{
					if (achievements.at(i)->displayed == false)
					{
						buffer2.deposit("Achievement Unlocked: " + achievements.at(i)->content);
						achievements.at(i)->displayed = true;
					}
				}
			}
		}

		//text.setString(buffer.fetch());

		window.setView(view);

		window.clear();

		window.draw(playerSprite);

		//window.draw(text);

		for (int i = 0; i < texts.size(); i++)
		{
			window.draw(*texts.at(i));
		}

		for (int i = 0; i < achvTexts.size(); i++)
		{
			window.draw(*achvTexts.at(i));
		}

		window.display();
	}

	return 0;
}