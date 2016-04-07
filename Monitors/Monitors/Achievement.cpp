#include "Achievement.h"

int Worker(void*);

Achievement::Achievement(string n, string c, string cat, sf::Sprite& p)
{
	name = n;
	content = c;
	catagory = cat;
	player = &p;
	complete = false;
	jumpCount = 0;
	displayed = false;
}

void Achievement::Update()
{
	if (name == "WalkR")
	{
		if (complete == false)
		{
			if (player->getPosition().x > 1000)
			{
				bool alreadyComplete = false;
				string line;
				vector<string> lines;
				ifstream myfile("completed.txt");
				if (myfile.is_open())
				{
					while (getline(myfile, line))
					{
						lines.push_back(line);

						if (line == name)
						{
							alreadyComplete = true;
						}
					}
					myfile.close();
				}

				if (alreadyComplete == false)
				{
					complete = true;
					ofstream myfile("completed.txt");
					if (myfile.is_open())
					{
						for (int i = 0; i < lines.size(); i++)
						{
							myfile << lines.at(i) + "\n";
						}
						myfile << name + "\n";
						myfile.close();
					}
					else cout << "Unable to open file";
				}
			}
		}
	}
	else if (name == "WalkL")
	{
		if (complete == false)
		{
			if (player->getPosition().x < 100)
			{
				bool alreadyComplete = false;
				string line;
				vector<string> lines;
				ifstream myfile("completed.txt");
				if (myfile.is_open())
				{
					while (getline(myfile, line))
					{
						lines.push_back(line);

						if (line == name)
						{
							alreadyComplete = true;
						}
					}
					myfile.close();
				}

				if (alreadyComplete == false)
				{
					complete = true;
					ofstream myfile("completed.txt");
					if (myfile.is_open())
					{
						for (int i = 0; i < lines.size(); i++)
						{
							myfile << lines.at(i) + "\n";
						}
						myfile << name + "\n";
						myfile.close();
					}
					else cout << "Unable to open file";
				}
			}
		}
	}
	else if (name == "Jump")
	{
		if (complete == false)
		{
			if (jumpCount == 1)
			{
				bool alreadyComplete = false;
				string line;
				vector<string> lines;
				ifstream myfile("completed.txt");
				if (myfile.is_open())
				{
					while (getline(myfile, line))
					{
						lines.push_back(line);

						if (line == name)
						{
							alreadyComplete = true;
						}
					}
					myfile.close();
				}

				if (alreadyComplete == false)
				{
					complete = true;
					ofstream myfile("completed.txt");
					if (myfile.is_open())
					{
						for (int i = 0; i < lines.size(); i++)
						{
							myfile << lines.at(i) + "\n";
						}
						myfile << name + "\n";
						myfile.close();
					}
					else cout << "Unable to open file";
				}
			}
		}
	}
	else if (name == "Jump3")
	{
		if (complete == false)
		{
			if (jumpCount == 3)
			{
				bool alreadyComplete = false;
				string line;
				vector<string> lines;
				ifstream myfile("completed.txt");
				if (myfile.is_open())
				{
					while (getline(myfile, line))
					{
						lines.push_back(line);

						if (line == name)
						{
							alreadyComplete = true;
						}
					}
					myfile.close();
				}

				if (alreadyComplete == false)
				{
					complete = true;
					ofstream myfile("completed.txt");
					if (myfile.is_open())
					{
						for (int i = 0; i < lines.size(); i++)
						{
							myfile << lines.at(i) + "\n";
						}
						myfile << name + "\n";
						myfile.close();
					}
					else cout << "Unable to open file";
				}
			}
		}
	}
	else if (name == "Jump5")
	{
		if (complete == false)
		{
			if (jumpCount == 5)
			{
				bool alreadyComplete = false;
				string line;
				vector<string> lines;
				ifstream myfile("completed.txt");
				if (myfile.is_open())
				{
					while (getline(myfile, line))
					{
						lines.push_back(line);

						if (line == name)
						{
							alreadyComplete = true;
						}
					}
					myfile.close();
				}

				if (alreadyComplete == false)
				{
					complete = true;
					ofstream myfile("completed.txt");
					if (myfile.is_open())
					{
						for (int i = 0; i < lines.size(); i++)
						{
							myfile << lines.at(i) + "\n";
						}
						myfile << name + "\n";
						myfile.close();
					}
					else cout << "Unable to open file";
				}
			}
		}
	}
}

void Achievement::Draw(sf::RenderWindow & window)
{

}