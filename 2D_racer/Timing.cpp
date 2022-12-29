#include "Timing.h"

//privatna funkcija
void Timing::initText(sf::RenderWindow& window)
{
	if (!font.loadFromFile("Fonts/Kvant-Trial-Bold.ttf")) {
		std::cout << "ERROR....TIMING COULD NOT LOAD FONT" << std::endl;
	}

	this->text.setFont(font);
	this->text.setCharacterSize(24);
	this->text.setPosition(4, 4);

	this->newRecordText.setFont(font);
	this->newRecordText.setCharacterSize(48);
	this->newRecordText.setString("NEW RECOR");
	//newRecordText.setOrigin(178, 0);
	this->newRecordText.setPosition(window.getSize().x/2 - this->newRecordText.getGlobalBounds().width/2, 100); 

	this->currentBestTime.setFont(font);
	this->currentBestTime.setCharacterSize(24);
	this->currentBestTime.setPosition(4, 34);

	this->lapN.setFont(font);
	this->lapN.setCharacterSize(24);
	//this->lapN.setPosition(window.getSize().x-30.f, 4);
}


Timing::Timing(sf::RenderWindow& window)
{
	this->initText(window);
}

Timing::~Timing()
{
}

void Timing::lapTime(Racer& racer, Map& map)
{
	//velocity da nemoze za nazad proci i zabiljeziti prolaz (kasnije rjeseno sa checkboxovima)
	//nekad startna linij ne registrira prolaz, potrebno rijestit
	if (map.getStartLine().intersects(racer.getMiddleCheckBox()) &&
		this->currentLapTime.getElapsedTime().asSeconds() > 0.5f &&
		racer.getVelocity().x < 0) {
		if (this->startLoop) {
			this->currentLapTime.restart();
			this->startLoop = 0;
			this->Lap++;
		}
		else if (!this->startLoop && this->checkPoint1 && this->checkPoint2) 
		{
			this->Lap++;
			this->time = this->currentLapTime.getElapsedTime().asSeconds();
			this->displayTimer.restart(); //timer za prikaz New Record teksta
			//std::cout << this->currentLapTime.getElapsedTime().asSeconds() << std::endl;
			this->currentLapTime.restart();
			this->checkPoint1 = this->checkPoint2 = 0;
		}
	}
}

void Timing::renderTime(sf::RenderTarget& target, Map& map)
{
	//kad se prodje start loop (od startne pozicije do start) onda pocinje brojanje vremena
	if (!this->startLoop) {
		this->text.setString(std::to_string(this->currentLapTime.getElapsedTime().asSeconds()));
		target.draw(this->text);
		this->lapN.setString("LAP: " + std::to_string(Lap));
		this->lapN.setPosition(target.getSize().x - this->lapN.getGlobalBounds().width-10.f, 4);
		target.draw(this->lapN);
		if (map.getBestTime() == 0.f) {
			this->currentBestTime.setString("BEST LAP TIME: ---" );
			target.draw(this->currentBestTime);
		}
		else {
			this->currentBestTime.setString("BEST LAP TIME: " + std::to_string(map.getBestTime()));
			target.draw(this->currentBestTime);
		}
	}

	//prikazuje "NEW RECORD" na 2s u slucaju da je postavljen novi rekord staze 
	if ((this->time <= map.getBestTime() || map.getBestTime() == 0.f) && 
		this->displayTimer.getElapsedTime().asSeconds() <= 2.f && !this->startLoop) {
		target.draw(this->newRecordText);
		map.setBestTime(this->time);
	}
	

}

void Timing::validation(Racer& racer, Map& map)
{
	if (map.getCheckPoint1().intersects(racer.globalBounds())){
		this->checkPoint1 = 1;
	}
	if (map.getCheckPoint2().intersects(racer.globalBounds())) {
		this->checkPoint2 = 1;
	}
}

float Timing::getTime()
{
	return this->time;
}

int Timing::getLap()
{
	return this->Lap;
}


