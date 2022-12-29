#include "Ograda.h"

void Ograda::initTexture()
{
	if (!this->texture.loadFromFile("Textures/MalaOgrada.png"))
	{
		std::cout << "ERROR....TEXTURE COULD NOT LOAD...MAP" << std::endl;
	}
}

void Ograda::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(3160.f, 2242.f);
	//this->sprite.setOrigin(347.5f, 206.5f);
}


Ograda::Ograda()
{
	this->initTexture();
	this->initSprite();
}

Ograda::~Ograda()
{
}

void Ograda::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Ograda::setPos(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Ograda::checkUdar(Racer& racer)
{
	//std::cout << this->sprite.getPosition().x << std::endl;
	ruboviW = this->sprite.getGlobalBounds();
	ruboviP = racer.globalBounds();
	/*if(this->ruboviW.intersects(ruboviP))
	{
		std::cout << "udar" << std::endl;
	}
	else { std::cout << "nije udar" << std::endl; }*/
}


