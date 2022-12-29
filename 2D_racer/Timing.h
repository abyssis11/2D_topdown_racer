#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Racer.h"
#include "Map.h"
class Timing
{
public:
	Timing(sf::RenderWindow& window);
	~Timing();
	//mjeri vrijeme kruga
	void lapTime(Racer& racer, Map& map);
	//za prikaz vremena na ekranu
	void renderTime(sf::RenderTarget& target, Map& map);
	//provjerava ako je auto presao oba checkpointa
	void validation(Racer& racer, Map& map);
	float getTime();;
	int getLap();
private:
	sf::Clock currentLapTime;
	sf::Clock displayTimer;
	bool startLoop = 1;
	sf::Font font;
	sf::Text text, newRecordText, currentBestTime, lapN;
	bool checkPoint1=0, checkPoint2=0;
	//float bestTime = 0.f;
	float time = 0.f;
	int Lap = 0;

	void initText(sf::RenderWindow& window);
};

