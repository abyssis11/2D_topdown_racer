#include "Menu.h"

Menu::Menu(sf::RenderWindow& window)
{
	if (!font.loadFromFile("Fonts/Kvant-Trial-Bold.ttf")) {
		std::cout << "ERROR....MENU COULD NOT LOAD FONT" << std::endl;
	}
	if (!texture.loadFromFile("Textures/backgroundConcept.jpg")) {
		std::cout << "ERROR....MENU COULD NOT LOAD BACKGROUND" << std::endl;
	}

	this->background.setTexture(&texture);
	this->background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	this->text[0].setFont(this->font);
	this->text[0].setString("RACE");
	this->text[0].setFillColor(sf::Color::Red);
	this->text[0].setCharacterSize(100);
	this->text[0].setLetterSpacing(3);
	this->text[0].setPosition(window.getSize().x / 5 - this->text[0].getGlobalBounds().width/2, window.getSize().y/1.7);

	this->text[1].setFont(this->font);
	this->text[1].setString("EXIT");
	this->text[1].setFillColor(sf::Color::White);
	this->text[1].setCharacterSize(36);
	this->text[1].setLetterSpacing(3);
	this->text[1].setPosition(window.getSize().x / 5 - this->text[1].getGlobalBounds().width / 2, window.getSize().y / 1.2);

	this->selectedItem = 0;
}

Menu::~Menu()
{
}

void Menu::render(sf::RenderWindow& target)
{
	target.draw(this->background);
	for (int i = 0; i < maxItems; i++) {
		target.draw(this->text[i]);
	}
}

//pomicanje po menu i mjenanje boje odabrnaih elementa
void Menu::up()
{
	//MOZE BOLJE moze samo > 0
	if (this->selectedItem - 1 >= 0) {
		this->text[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		this->text[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::down()
{
	if (this->selectedItem + 1 < maxItems) {
		this->text[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		this->text[selectedItem].setFillColor(sf::Color::Red);
	}
}

int Menu::getSelectedItem()
{
	return this->selectedItem;
}
