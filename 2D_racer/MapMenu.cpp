#include "MapMenu.h"

void MapMenu::initItems(sf::RenderWindow& window)
{
	if (!font.loadFromFile("Fonts/Kvant-Trial-Bold.ttf")) {
		std::cout << "ERROR....MENU COULD NOT LOAD FONT" << std::endl;
	}
	if (!textureBackground.loadFromFile("Textures/mapMenuBackground.jpg")) {
		std::cout << "ERROR....MENU COULD NOT LOAD BACKGROUND" << std::endl;
	}

	if (!textureGrobnik.loadFromFile("Textures/GrobnikMiniMap.png")) {
		std::cout << "ERROR....MENU COULD NOT LOAD GROBNIK MINI MAP" << std::endl;
	}

	if (!textureNurburgring.loadFromFile("Textures/NurburgringMiniMap.png")) {
		std::cout << "ERROR....MENU COULD NOT LOAD NURBURGRING MINI MAP" << std::endl;
	}

	this->background.setTexture(&textureBackground);
	this->background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	
	this->miniMapGrobnik.setTexture(this->textureGrobnik);
	this->miniMapGrobnik.setPosition(window.getSize().x / maxItems - this->miniMapGrobnik.getGlobalBounds().width / 2, window.getSize().y / 2 - this->miniMapGrobnik.getGlobalBounds().height);
	this->miniMapGrobnik.setColor(sf::Color::Red);

	this->miniMapNurburgring.setTexture(this->textureNurburgring);
	this->miniMapNurburgring.setPosition(window.getSize().x / maxItems*2 - this->miniMapNurburgring.getGlobalBounds().width / 2, window.getSize().y / 2 - this->miniMapNurburgring.getGlobalBounds().height);
	this->miniMapNurburgring.setColor(sf::Color(62, 62, 63));

	this->text[0].setFont(this->font);
	this->text[0].setString("GROBNIK");
	this->text[0].setFillColor(sf::Color::Red);
	this->text[0].setCharacterSize(48);
	this->text[0].setLetterSpacing(3);
	this->text[0].setPosition(window.getSize().x /maxItems - this->text[0].getGlobalBounds().width / 2, window.getSize().y / 2 + this->text[0].getGlobalBounds().height);

	this->text[1].setFont(this->font);
	this->text[1].setString("NURBURGRING");
	this->text[1].setFillColor(sf::Color::White);
	this->text[1].setCharacterSize(48);
	this->text[1].setLetterSpacing(3);
	this->text[1].setPosition(window.getSize().x /maxItems*2 - this->text[1].getGlobalBounds().width / 2, window.getSize().y / 2 + this->text[1].getGlobalBounds().height);

	this->text[2].setFont(this->font);
	this->text[2].setString("EXIT");
	this->text[2].setFillColor(sf::Color::White);
	this->text[2].setCharacterSize(36);
	this->text[2].setLetterSpacing(3);
	this->text[2].setPosition(window.getSize().x / 2 - this->text[2].getGlobalBounds().width / 2, window.getSize().y / 1.2); //(maxItems) * 2

	this->selectedItem = 0;
}


MapMenu::MapMenu(sf::RenderWindow& window)
{
	this->initItems(window);
}

MapMenu::~MapMenu()
{
}

void MapMenu::run(sf::RenderWindow& window)
{
	while (!this->exit)
	{
		this->updatePollEvents(window);
		this->render(window);
	}
}

void MapMenu::updatePollEvents(sf::RenderWindow& window)
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
		{
			switch (e.key.code)
			{
			case sf::Keyboard::Left:
				this->left();
				break;
			case sf::Keyboard::Right:
				this->right();
				break;
			case sf::Keyboard::Escape:
				//s esc mozemo vratiti na pocetni menu
				this->exit = 1;
				break;
			case sf::Keyboard::Return:
				switch (this->selectedItem)
				{
				case 0:
					//gasimo ovaj menu i pokrecemo igru
					this->play = 1;
					this->exit = 1;
					break;
				case 1:
					this->play = 1;
					this->exit = 1;
					break;
				case 2:
					this->exit = 1;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		}
		}
		
	}
}

void MapMenu::render(sf::RenderWindow& window)  //sf::RenderTarget& target
{
	window.clear();
	window.draw(this->background);
	window.draw(this->miniMapGrobnik);
	window.draw(this->miniMapNurburgring);
	for (int i = 0; i < maxItems; i++) {
		window.draw(this->text[i]);
	}
	window.display();
}

//za pomicanje po menu i mjenanje boja odabranih stavki
void MapMenu::left()
{
	//MOZE BOLJE 
	if (this->selectedItem - 1 >= 0) {
		this->text[selectedItem].setFillColor(sf::Color::White);
		if (this->selectedItem == 1) {
		this->miniMapNurburgring.setColor(sf::Color(62, 62, 63));
		}
		selectedItem--;
		this->text[selectedItem].setFillColor(sf::Color::Red);
		if (this->selectedItem == 0) {
			this->miniMapGrobnik.setColor(sf::Color::Red);
		}
		else if (this->selectedItem == 1) {
			this->miniMapNurburgring.setColor(sf::Color::Red);
		}
	}
}

void MapMenu::right()
{
	if (this->selectedItem + 1 < maxItems) {
		this->text[selectedItem].setFillColor(sf::Color::White);
		if (this->selectedItem == 0) {
			this->miniMapGrobnik.setColor(sf::Color(62, 62, 63));
		}else if (this->selectedItem == 1) {
			this->miniMapNurburgring.setColor(sf::Color(62, 62, 63));
		}
		selectedItem++;
		this->text[selectedItem].setFillColor(sf::Color::Red);
		if (this->selectedItem == 0) {
			this->miniMapGrobnik.setColor(sf::Color::Red);
		}
		else if (this->selectedItem == 1) {
			this->miniMapNurburgring.setColor(sf::Color::Red);
		}
	}
}

int MapMenu::getSelectedItem()
{
	return this->selectedItem;
}

bool MapMenu::getPlay()
{
	return this->play;
}

bool MapMenu::getExit()
{
	return this->exit;
}
