#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Racer
{
public:
	Racer(int map);
	//primarno za ghosta
	Racer(sf::Color c);
	//mozda nekad postane virtualna klasa
	virtual ~Racer(); 

	void render(sf::RenderTarget& target);
	void setPos(float x, float y);
	void setRot(double a);
	void movment(float dt);
	void SkidAnimation(char state);
	void lowerSpeed(float s); //za smanjiti brzinu na travi
	float getSpeed();
	sf::FloatRect globalBounds();
	sf::FloatRect getNextPos();
	sf::Vector2f getVelocity();
	sf::Vector2f getPos();
	void move(sf::Vector2f v);
	void setVelocityX(float vx);
	void setVelocityY(float vy);
	double getAngle();
	sf::FloatRect getMiddleCheckBox();

private:
	sf::Sprite sprite, skid;
	sf::Texture texture, textureSheet;
	sf::IntRect currentSkidFrame;

	float speed = 0.f;
	double angle = -1.570796; //radi boljeg pozicioniranja auta 
	float maxSpeed = 1000.0f;
	float acc = 7.f, dec = 8.f;
	float turnSpeed = 0.03f; //mozda promjeniti 
	sf::FloatRect nextPos;
	sf::Vector2f velocity;
	sf::Clock animationTimer, animationTimer2;
	sf::RectangleShape middleCheckBox;

	void initTexture();
	void initSprite();
	void initSkidMarks();
};

