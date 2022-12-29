#pragma once
#include "Racer.h"
#include "Map.h"
#include "MapGrobnik.h"
#include "MapNurburgring.h"
#include "Timing.h"
#include<iostream>

class Play
{
public:
	Play(sf::RenderWindow& window, int map);
	virtual ~Play();

	void run(sf::RenderWindow& window);
	void updatePollEvents(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	bool getExit();

private:
	Racer* racer, *ghostRacer; 
	Map* map;
	Timing* timing;
	std::vector<sf::Vector2f> bestLap;
	std::vector<sf::Vector2f> currentLap;
	std::vector<double> currentLapRacerAngle;
	std::vector<double> BestLapRacerAngle;
	sf::Vector2f racerStartPosition;
	sf::View mv; //main view
	int currentMove = 0;
	float dt;
	sf::Clock dt_clock; 
	bool newBestLap = 0;
	bool exit=0;

	void initView(float x, float y);
	void initRacer(int map);
	void initMapGrobnik();
	void initMapNurburgring();
	void initTiming(sf::RenderWindow& window);

};

