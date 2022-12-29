#pragma once
#include "Play.h"
#include "Menu.h"
#include "MapMenu.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void run();
	void updatePollEvents();
	void render();

private:
	sf::RenderWindow* window;
	Play* play;
	Menu* menu;
	MapMenu* mapMenu;

	void initWindow();
	void initPlay(int map);
	void initMenu();
	void initMapMenu();
};

