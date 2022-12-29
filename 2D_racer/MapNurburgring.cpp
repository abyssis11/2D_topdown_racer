#include "MapNurburgring.h"

void MapNurburgring::initTexture()
{
	if (!this->image.loadFromFile("Textures/NurburgringStaza.png"))
	{
		std::cout << "ERROR....TEXTURE COULD NOT LOAD...MAP NURBURGRING" << std::endl;
	}
	this->texture.loadFromImage(this->image);
}

void MapNurburgring::initSprite()
{ 
	this->sprite.setTexture(this->texture);
}

void MapNurburgring::initWalls()
{
	//stvaramo zidove staze 
	sf::RectangleShape wall1, wall2, wall3, wall4, wall5, wall6, wall7, wall8, wall9, wall10,
		wall11, wall12, wall13, wall14, wall15, wall16, wall17, wall18, wall19, wall20;

	//pozicija
	wall1.setPosition(7307.f, 2559.f);
	//visina i sirina
	wall1.setSize(sf::Vector2f(3453.f, 15.f));
	wall2.setPosition(7307.f, 1008.f);
	wall2.setSize(sf::Vector2f(15.f, 1551.f));
	wall3.setPosition(5504.f, 1008.f);
	wall3.setSize(sf::Vector2f(1802.f, 15.f)); 
	wall4.setPosition(5488.f, 1008.f);
	wall4.setSize(sf::Vector2f(15.f, 1279.f)); 
	wall5.setPosition(6342.f, 1454.f);
	wall5.setSize(sf::Vector2f(15.f, 833.f));
	wall6.setPosition(5991.f, 2272.f);
	wall6.setSize(sf::Vector2f(352.f, 15.f));
	wall7.setPosition(5991.f, 2288.f);
	wall7.setSize(sf::Vector2f(15.f, 515.f));
	wall8.setPosition(5201.5f, 2287.f);
	wall8.setSize(sf::Vector2f(302.f, 15.f));
	wall9.setPosition(5201.f, 2303.f);
	wall9.setSize(sf::Vector2f(15.f, 162.f));
	wall11.setPosition(4889.f, 2467.f);
	wall11.setSize(sf::Vector2f(15.f, 183.f));
	wall12.setPosition(4492.f, 2634.f);
	wall12.setSize(sf::Vector2f(396.f, 15.f));
	wall13.setPosition(4492.f, 2650.f);
	wall13.setSize(sf::Vector2f(15.f, 201.f));
	wall15.setPosition(4081.f, 2835.f);
	wall15.setSize(sf::Vector2f(15.f, 212.f));
	wall16.setPosition(249.5f, 248.5f);
	wall16.setSize(sf::Vector2f(15.f, 4500.f));
	wall17.setPosition(249.7f, 232.5f);
	wall17.setSize(sf::Vector2f(11500.f, 15.f));
	wall18.setPosition(11734.5f, 248.5f);
	wall18.setSize(sf::Vector2f(15.f, 4500.f));
	wall19.setPosition(249.47f, 4749.5f);
	wall19.setSize(sf::Vector2f(11500.f, 15.f));
	wall20.setPosition(3728.f, 3031.f);
	wall20.setSize(sf::Vector2f(352.f, 15.f));
	wall14.setPosition(3728.f, 3046.f);
	wall14.setSize(sf::Vector2f(15.f, 836.f));
	wall10.setPosition(1122.f, 3868.f);
	wall10.setSize(sf::Vector2f(2606.f, 15.f));

	//pokazivac na niz objekta (zidova)
	this->walls = new sf::RectangleShape[]{ wall1, wall2, wall3, wall4, wall5, wall6, wall7, wall8, wall9, wall10,
								wall11, wall12, wall13, wall14, wall15, wall16, wall17, wall18, wall19, wall20};

	for (int i = 0; i < 20; i++) {
		this->walls[i].setFillColor(sf::Color(0, 0, 0));
	}
}

void MapNurburgring::initStartLine()
{
	this->startLine.setPosition(8887.f, 2668.f);
	this->startLine.setSize(sf::Vector2f(8.f, 221.f));
}

void MapNurburgring::initCheckPoints()
{
	this->checkPoint1.setSize(sf::Vector2f(1200.f, 1200.f)); 
	this->checkPoint1.setPosition(446.f, 3285.f);

	this->checkPoint2.setSize(sf::Vector2f(1200.f, 1200.f));
	this->checkPoint2.setPosition(7164.f, 141.f);
}

MapNurburgring::MapNurburgring()
{
	this->initTexture();
	this->initSprite();
	this->initWalls();
	this->initStartLine();
	this->initCheckPoints();
}

MapNurburgring::~MapNurburgring()
{
	delete[] this->walls; //provjeriti ako to tu treba
}

void MapNurburgring::setBestTime(float bt)
{
	this->bestTime = bt;
}

float MapNurburgring::getBestTime()
{
	return this->bestTime;
}
