#pragma once
#include <SFML/System.hpp>
#include "Racer.h"
class Grass
{
public:
	Grass();
	~Grass();
	void render(sf::RenderTarget& target);

	void CheckGrass(Racer& racer) const;
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;

	void initTexture();
	void initSprite();
};

