#pragma once
#include "Map.h"
class MapNurburgring : public Map
{
public:
	MapNurburgring();
	~MapNurburgring();
	void initTexture(); //nadjacano
	void initSprite(); //nadjacano
	void initWalls(); //nadjacano
	void initStartLine(); //nadjacano
	void initCheckPoints();  //nadjacano

	void setBestTime(float bt);
	float getBestTime();
private:
	float bestTime = 0.f;
	//bool firstLap = 1;

};

