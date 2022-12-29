#include "Racer.h"

//privatne funkcije
void Racer::initTexture()
{
	//ucitati sliku
	if (!this->texture.loadFromFile("Textures/Autic.png"))
	{
		std::cout << "ERROR....TEXTURE COULD NOT LOAD...RACER" << std::endl;
	}

	//za anmiaciju skida
	if (!this->textureSheet.loadFromFile("Textures/skidmark_sheet.png"))
	{
		std::cout << "ERROR....TEXTURE COULD NOT LOAD...SKID" << std::endl;
	}
}

void Racer::initSprite()
{
	//postaviti sliku na sprite
	this->sprite.setTexture(this->texture);
	//potaviti tocku prema kojoj se sve transformacije nad objektom desavaju (inace je u gonjem lijevom kutu, odnosno tocka (0,0))
	this->sprite.setOrigin(26/2, 70/2);
	
	//checkbox u sredini auta, služi za detekciju prolaska kroz strat/cilj
	this->middleCheckBox.setSize(sf::Vector2f(8.f, 1.f));
	this->middleCheckBox.setOrigin(4.f, 0.5f);

}

void Racer::initSkidMarks()
{
	this->skid.setTexture(this->textureSheet);
	//postavljanje poèetnog frama na prvu sliku u sheetu, kasnije se taj okvire pomice
	this->currentSkidFrame = sf::IntRect(0, 0, 78, 82);
	this->skid.setTextureRect(this->currentSkidFrame);
	this->skid.setOrigin(78 / 2, 0);
	this->skid.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
	//kako bi se animacija postavila u rocan kut pri prikazu
	this->skid.setRotation(this->sprite.getRotation()-90.f);
}



//konstruktor
Racer::Racer(int map)
{
	this->initTexture();
	this->initSprite();

	//ovisno o mapi, auto se postavlja na odredjenu poziciju
	if(map == 0){
		this->sprite.setPosition(7140.f, 2672.f);
		this->middleCheckBox.setPosition(this->sprite.getPosition());
	}
	else if (map == 1) {
		this->sprite.setPosition(9706.f, 2825.f);
		this->middleCheckBox.setPosition(this->sprite.getPosition());
	}
	this->initSkidMarks();
}

Racer::Racer(sf::Color c)
{
	this->initTexture();
	this->initSprite();

	this->initSkidMarks();
	//uglavnom za ghosta, postavlja se na transparentnu boju
	this->sprite.setColor(c);
}

//destruktor
Racer::~Racer()
{
}

//funkcije
void Racer::render(sf::RenderTarget& target)
{
	//za crtanje auta i skid markova na ekran
	target.draw(this->skid);
	target.draw(this->sprite);
}

void Racer::setPos(float x, float y) 
{
	//pozicija na mapi
	this->sprite.setPosition(x, y);
}

void Racer::setRot(double a) 
{
	this->sprite.setRotation(a * 180/ 3.141592);
}

void Racer::SkidAnimation(char state)
{
	//postavljanje animacija za lijevu i desnu stranu
	this->skid.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
	this->skid.setRotation(this->sprite.getRotation());
	if (state == 'R')
	{
		this->skid.setScale(1.f, 1.8f);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentSkidFrame.left += 78.f;
			if (this->currentSkidFrame.left >= 390.f) {
				this->currentSkidFrame.left = 234.f;
			}
			if (this->animationTimer2.getElapsedTime().asSeconds() >= 2.f) {
				this->currentSkidFrame.left = 0.f;
				this->animationTimer2.restart();
			}
			this->animationTimer.restart();
			this->skid.setTextureRect(this->currentSkidFrame);
		}
	}
	else if (state == 'L')
	{
		this->skid.setScale(-1.f, 1.8f); // zaokrenemo sheet
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentSkidFrame.left += 78.f;
			if (this->currentSkidFrame.left >= 390.f) {
				this->currentSkidFrame.left = 234.f;
			}
			if (this->animationTimer2.getElapsedTime().asSeconds() >= 2.f) {
				this->currentSkidFrame.left = 0.f;
				this->animationTimer2.restart();
			}
			this->animationTimer.restart();
			this->skid.setTextureRect(this->currentSkidFrame);
		}
	}
}

void Racer::movment(float dt)
{
	//pokreti
	bool Up = 0, Right = 0, Down = 0, Left = 0, Handbreak=0;
	this->velocity.y = 0.f;
	this->velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		Left = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		Right = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
		Up = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		Down = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		Handbreak = 1;

	if (Up && this->speed < this->maxSpeed){
		if (this->speed < 0) this->speed += this->dec; //tu je dec
		else this->speed += this->acc;
	}

	if (Down && this->speed > -this->maxSpeed){
		if (this->speed > 0) this->speed -= this->dec;
		else this->speed -= this->acc;
	}

	//Kao protu sila
	if (!Up && !Down) {
		if (this->speed - this->dec > 0) this->speed -= this->dec;
		else if (this->speed + this->dec < 0) this->speed += this->dec;
	}

	if (Right && this->speed != 0 ) {
		this->angle += this->turnSpeed * this->speed / this->maxSpeed;
	}
	if (Left && this->speed != 0) {
		this->angle -= this->turnSpeed * this->speed / this->maxSpeed;
	}
	if (Handbreak && Right) {
		this->angle += (this->turnSpeed * this->speed / this->maxSpeed) * 0.8;
		this->speed -= this->dec*0.3f;
		this->SkidAnimation('R');
	}

	if (Handbreak && Left) {
		this->angle -= (this->turnSpeed * this->speed / this->maxSpeed) * 0.8;
		this->speed -= this->dec*0.3f;
		this->SkidAnimation('L');
	}
	
	//dt da pokreti budu ne ovisni o fps-u
	this->velocity.x += sin(this->angle) * this->speed  * dt;
	this->velocity.y -= cos(this->angle) * this->speed * dt;

	this->middleCheckBox.setPosition(this->sprite.getPosition());
}


void Racer::lowerSpeed(float s)
{
	this->speed -= s;
}

float Racer::getSpeed()
{
	return this->speed;
}

sf::FloatRect Racer::globalBounds()
{
	return this->sprite.getGlobalBounds();
}

sf::FloatRect Racer::getNextPos()
{
	//pretpostavljamo slijedecu poziciju auta
	//sluzi za detektiranje udara u zid
	sf::FloatRect racerBounds = this->sprite.getGlobalBounds();
	this->nextPos = racerBounds;
	this->nextPos.left += this->velocity.x;
	this->nextPos.top += this->velocity.y;
	return this->nextPos;
}

void Racer::setVelocityX(float vx)
{
	this->velocity.x = vx;
}

void Racer::setVelocityY(float vy)
{
	this->velocity.y = vy;
}

double Racer::getAngle()
{
	return this->angle;
}

sf::FloatRect Racer::getMiddleCheckBox()
{
	return this->middleCheckBox.getGlobalBounds();
}

void Racer::move(sf::Vector2f v)
{
		this->sprite.move(v);
}

sf::Vector2f Racer::getVelocity()
{
	return this->velocity;
}

sf::Vector2f Racer::getPos()
{
	return this->sprite.getPosition();
}



