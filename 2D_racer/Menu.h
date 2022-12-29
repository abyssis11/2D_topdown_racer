#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

//bolje const
#define maxItems 2

class Menu
{
public:
	Menu(sf::RenderWindow& window);
	~Menu();

	void render(sf::RenderWindow& target);
	void up();
	void down();
	int getSelectedItem();
private:
	int selectedItem=0;
	sf::Font font;
	sf::Text text[maxItems];
	sf::RectangleShape background;
	sf::Texture texture;

};

