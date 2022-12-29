#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#define maxItems 3

class MapMenu
{
public:
	MapMenu(sf::RenderWindow& window);
	~MapMenu();

	void run(sf::RenderWindow& window);
	void updatePollEvents(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	bool getExit();

	void left();
	void right();
	int getSelectedItem();
	bool getPlay();
private:
	int selectedItem = 0;
	sf::Font font;
	sf::Text text[maxItems];
	bool exit = 0;
	bool play = 0;
	sf::RectangleShape background;
	sf::Texture textureBackground, textureGrobnik, textureNurburgring; 
	sf::Sprite miniMapGrobnik, miniMapNurburgring; //nije array jer neradi kako treba
	void initItems(sf::RenderWindow& window);
};

