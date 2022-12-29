#include "Map.h"


Map::Map()
{	
}

Map::~Map()
{
}

void Map::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

//provjera ako je igrac izasao izvan staze (sporo i lose)
void Map::checkGrass(Racer& racer) 
{
	//radi i bez ststaic castsa
	const auto playerPixel = this->image.getPixel(
		static_cast<unsigned>(racer.getPos().x),
		static_cast<unsigned>(racer.getPos().y)
	);
	

	//provjerava svaki pixel (sporo)
	if (playerPixel != sf::Color(62, 62, 63) && playerPixel != sf::Color(122, 121, 123))
	{
		if (racer.getSpeed() < 100) racer.lowerSpeed(5.f);
		else  racer.lowerSpeed(17.f);
	}
}

//za crtanje zidova 
void Map::renderWall(sf::RenderTarget& target)
{
	for (int i = 0; i < 20; i++) {
		target.draw(walls[i]);
	}
}

//provjerava udare u zid
void Map::checkWall(Racer& racer)
{
	for (int i = 0; i < 20; i++) { 

		sf::FloatRect wallBounds = walls[i].getGlobalBounds();

		//može biti i globalbounds ali bolje radi sa next position
		if (wallBounds.intersects(racer.getNextPos())) {
			
			//bootom collision
			if (racer.globalBounds().top < wallBounds.top &&
				racer.globalBounds().top + racer.globalBounds().height < wallBounds.top + wallBounds.height &&
				racer.globalBounds().left < wallBounds.left + wallBounds.width &&
				racer.globalBounds().left + racer.globalBounds().height > wallBounds.left)
			{
				racer.setVelocityY(0.f);
			}
			 
			//top collision
			else if (racer.globalBounds().top > wallBounds.top &&
				racer.globalBounds().top + racer.globalBounds().height > wallBounds.top + wallBounds.height &&
				racer.globalBounds().left < wallBounds.left + wallBounds.width &&
				racer.globalBounds().left + racer.globalBounds().height > wallBounds.left)
			{
				racer.setVelocityY(0.f);
			}

			//left collision
			else if (racer.globalBounds().left < wallBounds.left &&
				racer.globalBounds().left + racer.globalBounds().width < wallBounds.left + wallBounds.width &&
				racer.globalBounds().top < wallBounds.top + wallBounds.height &&
				racer.globalBounds().top + racer.globalBounds().height > wallBounds.top)
			{
				racer.setVelocityX(0.f);
			}

			//right collision
			else if (racer.globalBounds().left > wallBounds.left &&
				racer.globalBounds().left + racer.globalBounds().width > wallBounds.left + wallBounds.width &&
				racer.globalBounds().top < wallBounds.top + wallBounds.height &&
				racer.globalBounds().top + racer.globalBounds().height  > wallBounds.top)
			{
				racer.setVelocityX(0.f);
			}
		}
	}
}

sf::FloatRect Map::getStartLine()
{
	return this->startLine.getGlobalBounds();
}

sf::FloatRect Map::getCheckPoint1()
{
	return this->checkPoint1.getGlobalBounds();
}

sf::FloatRect Map::getCheckPoint2()
{
	return this->checkPoint2.getGlobalBounds();
}


//napraviti posebno travu i collision?



