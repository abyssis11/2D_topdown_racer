#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Racer.h"

class Map
{
public:
	//ovo je apstraktna klasa, ali ima i nekih obicnih funkcija
	Map();
	virtual ~Map(); //jer je apstraktna klasa
	//ucitavanje texture(slike) za mapu
	virtual void initTexture() = 0; 
	virtual void initSprite() = 0; 
	//stvaranje zidova mape, svaka mapa mora imati 20 zidova (promjeniti to)
	virtual void initWalls() = 0; 
	//postavljanje startne linije na mapu putem koje ce se mjeriti krug
	virtual void initStartLine() = 0; 
	//svaka mapa ima 2 checkpointa, ako auto ne prodje oba vrijeme kruga se ne zabiljezi
	virtual void initCheckPoints() = 0; 
	//postvaljanje najboljeg vremena za savku mapu
	virtual void setBestTime(float bt)=0;
	virtual float getBestTime()=0;

	void render(sf::RenderTarget& target);
	//provjerava ako se auto nalazi na travi te ga usporava
	void checkGrass(Racer& racer); //const
	void renderWall(sf::RenderTarget& target);  
	//provjerava udare/kolizije sa zidom
	void checkWall(Racer& racer);
	sf::FloatRect getStartLine();
	sf::FloatRect getCheckPoint1();
	sf::FloatRect getCheckPoint2();

	
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;
	sf::RectangleShape startLine;
	sf::RectangleShape* walls; //pokazivac na niz objekta (zidova)
	sf::RectangleShape checkPoint1, checkPoint2;

};

