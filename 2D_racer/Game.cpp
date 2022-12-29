#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "2D Top-Down racer", sf::Style::Close | sf::Style::Titlebar); 

	//limitiramo frame rate na 60fps
	//this->window->setFramerateLimit(60);

	//iskljucimo vsync jer poremeti frame rate
	//this->window->setVerticalSyncEnabled(false);
}

void Game::initPlay(int map)
{
	this->play = new Play(*this->window, map);
}

void Game::initMenu()
{
	this->menu = new Menu(*this->window);
}

void Game::initMapMenu()
{
	this->mapMenu = new MapMenu(*this->window);
}


Game::Game()
{
	this->initWindow();
	this->initMenu();
}

Game::~Game()
{
	delete this->window;
	delete this->menu;
}

void Game::run()
{
	//pokrecemo igru dok je prozor otvoren
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		this->render();
	}
}

void Game::updatePollEvents()
{
	//utjecemo na evente 
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
		{
			switch (e.key.code)
			{
			case sf::Keyboard::Up:
				this->menu->up();
				break;
			case sf::Keyboard::Down:
				this->menu->down();
				break;
			case sf::Keyboard::Escape:
				this->window->close();
				break;
			case sf::Keyboard::Return:
				switch (this->menu->getSelectedItem())
				{
				case 0:
					//pokrecemo izbornik staza
					this->initMapMenu();
					do {
						this->mapMenu->run(*this->window);
					} while (!this->mapMenu->getExit()); 
					
					//pokrecemo play ako je odabrana neka staza
					if (this->mapMenu->getPlay()) {
						int map = this->mapMenu->getSelectedItem();
						delete this->mapMenu;
						this->initPlay(map);
						do {
							this->play->run(*this->window);
						} while (!this->play->getExit());
						delete this->play;
					}
					else {
						delete this->mapMenu;
					}
					break;
				case 1:
					this->window->close();
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
		case sf::Event::Closed:
			this->window->close();
			break;
		default:
			break;
		}
	}
}

void Game::render()
{
	this->window->clear();

	this->menu->render(*this->window);

	this->window->display();
}
