#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>
#include "Racer.h"
class Ograda
{
public:
	Ograda();
	~Ograda();
	void render(sf::RenderTarget& target);
	void setPos(float x, float y);

	void checkUdar(Racer& racer);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::FloatRect ruboviW, ruboviP;

	void initTexture();
	void initSprite();
};

