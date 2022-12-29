#include "Grass.h"

void Grass::initTexture()
{
	if (!this->image.loadFromFile("Textures/Trava.png"))
	{
		std::cout << "ERROR....TEXTURE COULD NOT LOAD...MAP" << std::endl;
	}
	this->texture.loadFromImage(this->image);
}

void Grass::initSprite()
{
	this->sprite.setTexture(this->texture);
}

Grass::Grass()
{
	this->initTexture();
	this->initSprite();
}

Grass::~Grass()
{
}

void Grass::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Grass::CheckGrass(Racer& racer) const
{
	const auto playerPixel = this->image.getPixel(
		static_cast<unsigned>(racer.getX()),
		static_cast<unsigned>(racer.getY())
	);

	if (playerPixel == sf::Color(62, 62, 63)) {
		racer.setMaxSpeed(5);
		racer.setAcc(0.05);
	}
	else {
		racer.setMaxSpeed(15);
		racer.setAcc(0.2);
	}
}

