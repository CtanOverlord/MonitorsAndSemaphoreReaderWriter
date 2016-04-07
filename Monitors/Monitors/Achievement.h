#pragma once
#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

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

#include "SFML\Graphics.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>

using namespace std;

class Achievement
{
private:
	string name;
	string catagory;

	sf::Sprite* player;

public:

	Achievement(string name, string content, string catagory, sf::Sprite& player);
	void Update();
	void Draw(sf::RenderWindow & window);
	int jumpCount;
	bool complete;
	bool displayed;
	string content;

};

#endif

