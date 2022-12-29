#include "MapGrobnik.h"

void MapGrobnik::initTexture()
{

	if (!this->image.loadFromFile("Textures/StazaGrobnikBolja.png"))
	{
		std::cout << "ERROR....TEXTURE COULD NOT LOAD...MAP GROBNIK" << std::endl;
	}
	this->texture.loadFromImage(this->image);

}

void MapGrobnik::initSprite()
{
	this->sprite.setTexture(this->texture);
}

void MapGrobnik::initWalls()
{
	//stvaramo zidove staze
	sf::RectangleShape wall1, wall2, wall3, wall4, wall5, wall6, wall7, wall8, wall9, wall10,
		wall11, wall12, wall13, wall14, wall15, wall16, wall17, wall18, wall19, wall20;

	//pozicija
	wall1.setPosition(3297.f, 2825.f);
	//visina i sirina
	wall1.setSize(sf::Vector2f(5418.f, 15.f));
	wall2.setPosition(4368.f, 2406.f);
	wall2.setSize(sf::Vector2f(4168.f, 15.f));
	wall3.setPosition(3297.f, 2841.f);
	wall3.setSize(sf::Vector2f(15.f, 828.f));
	wall4.setPosition(2697.f, 3669.f);
	wall4.setSize(sf::Vector2f(615.f, 15.f));
	wall5.setPosition(1592.f, 3754.f);
	wall5.setSize(sf::Vector2f(1576.f, 15.f));
	wall6.setPosition(1577.f, 3285.f);
	wall6.setSize(sf::Vector2f(15.f, 484.f));
	wall7.setPosition(1020.f, 3269.f);
	wall7.setSize(sf::Vector2f(571.56f, 15.f));
	wall8.setPosition(1004.5f, 1460.f);
	wall8.setSize(sf::Vector2f(15.f, 1824.f));
	wall9.setPosition(8501.f, 2702.f);
	wall9.setSize(sf::Vector2f(552.f, 15.f));
	wall10.setPosition(8979.f, 2540.f);
	wall10.setSize(sf::Vector2f(426.f, 15.f));
	wall11.setPosition(9292.f, 2372.f);
	wall11.setSize(sf::Vector2f(427.f, 15.f));
	wall12.setPosition(9634.f, 2202.f);
	wall12.setSize(sf::Vector2f(423.f, 15.f));
	wall13.setPosition(10058.f, 1949.f);
	wall13.setSize(sf::Vector2f(15.f, 268.f));
	wall14.setPosition(10058.f, 1933.f);
	wall14.setSize(sf::Vector2f(534.87f, 15.f));
	wall15.setPosition(10578.f, 1436.f);
	wall15.setSize(sf::Vector2f(15.f, 496.f));
	wall16.setPosition(249.5f, 248.5f);
	wall16.setSize(sf::Vector2f(15.f, 4500.f));
	wall17.setPosition(249.7f, 232.5f);
	wall17.setSize(sf::Vector2f(11500.f, 15.f));
	wall18.setPosition(11734.5f, 248.5f);
	wall18.setSize(sf::Vector2f(15.f, 4500.f));
	wall19.setPosition(249.47f, 4749.5f);
	wall19.setSize(sf::Vector2f(11500.f, 15.f));
	wall20.setPosition(4368.f, 2138.f);
	wall20.setSize(sf::Vector2f(15.f, 268.f));

	//pokazivac na niz objekta
	this->walls = new sf::RectangleShape[]{ wall1, wall2, wall3, wall4, wall5, wall6, wall7, wall8, wall9, wall10,
											wall11, wall12, wall13, wall14, wall15, wall16, wall17, wall18, wall19, wall20 };

	for (int i = 0; i < 20; i++) {
		this->walls[i].setFillColor(sf::Color(0, 0, 0));
	}
}

void MapGrobnik::initStartLine()
{
	this->startLine.setPosition(6321.f, 2515.f);
	this->startLine.setSize(sf::Vector2f(8.f, 221.f));
}

void MapGrobnik::initCheckPoints()
{
	this->checkPoint1.setSize(sf::Vector2f(1200.f, 1200.f));
	this->checkPoint1.setPosition(420.f, 717.f);

	this->checkPoint2.setSize(sf::Vector2f(1200.f, 1200.f));
	this->checkPoint2.setPosition(10433.f, 860.f);

}


void MapGrobnik::setBestTime(float bt)
{
	this->bestTime = bt;
}

float MapGrobnik::getBestTime()
{
	return this->bestTime;
}

MapGrobnik::MapGrobnik()
{
	this->initTexture();
	this->initSprite();
	this->initWalls();
	this->initStartLine();
	this->initCheckPoints();
}

MapGrobnik::~MapGrobnik()
{
	delete[] this->walls;
}