#include "Play.h"

//privatne funkcije
void Play::initView(float x, float y)
{
	mv.setSize(x, y);
}

void Play::initRacer(int map)
{
	//novi igrac(autic)
	this->racer = new Racer(map);
	this->ghostRacer = new Racer(sf::Color(128, 128, 128, 130));
}

void Play::initMapGrobnik()
{
	this->map = new MapGrobnik();
}

void Play::initMapNurburgring()
{
	this->map = new MapNurburgring();
}

void Play::initTiming(sf::RenderWindow& window)
{
	this->timing = new Timing(window);
	
}

//konstruktor
Play::Play(sf::RenderWindow& window, int map)
{
	//limitiramo frame rate na 60fps
	window.setFramerateLimit(60);

	//iskljucimo vsync jer poremeti frame rate
	//dodatno testirat
	window.setVerticalSyncEnabled(false);

	this->initView(window.getSize().x, window.getSize().y); // postavljanje main viewa koji prati autio
	this->initRacer(map);
	if (map == 0) {
		this->initMapGrobnik();
	}else if(map==1){
		this->initMapNurburgring();
	}
	this->initTiming(window);
}

//destruktor
Play::~Play()
{
	//dealociramo
	delete this->racer;
	delete this->ghostRacer;
	delete this->map;
	delete this->timing;
}

//funkcije
void Play::run(sf::RenderWindow& window)
{
	while (!this->exit)
	{
		//std::cout << std::to_string(dt_clock.getElapsedTime().asSeconds()) << std::endl;
		//kasnije moze sluziti da bude framerate indenpendent
		//kad bi stavili fps na 144 dt bi bio puno manji te kad bi velocity pomnožili sa time dobili bi isti osjecaj  
		//odnoso auto bi se isto pomakao u jednoj skundi istu udaljenost neovisno o fps
		dt = dt_clock.restart().asSeconds();
		this->update(window);
		this->render(window);
	}
}

void Play::updatePollEvents(sf::RenderWindow& window)
{
	//utjecemo na evente 
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
			this->exit=1;
		}
	}
}

void Play::update(sf::RenderWindow& window)
{
	this->updatePollEvents(window);

	//pokreti autica
	this->racer->movment(dt);

	//kamera prati auto
	mv.setCenter(this->racer->getPos());

	//dodatno napraviti da kamera ne prati auto izvan staze
	//odnosno da se ne vidi crni dio (di nema mape)
	
	//usporiti kad je na travi
	this->map->checkGrass(*this->racer); 
	
	//udar s ogradom
	this->map->checkWall(*this->racer);

	//vrijeme
	this->timing->validation(*this->racer, *this->map);
	this->timing->lapTime(*this->racer, *this->map); 

	//ghost
	this->currentLap.push_back(this->racer->getVelocity());
	this->currentLapRacerAngle.push_back(this->racer->getAngle());

	this->newBestLap = 0;
	if (this->map->getStartLine().intersects(this->racer->getMiddleCheckBox())) { //popraviti jos za nazad 
		//ako je trenutni krug najbolji onda pokrete auta u njemu kopiramo u vektor iz kojeg ghost "vuce" pokrete
		if (this->timing->getTime() < this->map->getBestTime() || (this->timing->getLap()==2)) {
			this->racerStartPosition = this->racer->getPos(); //izmjena tetirat
			this->bestLap = this->currentLap;
			this->BestLapRacerAngle = this->currentLapRacerAngle; 
			this->ghostRacer->setPos(this->racerStartPosition.x, this->racerStartPosition.y);
			//std::cout << "Novi najbolji krug" << std::endl; //za debug
			this->newBestLap = 1;
		}
		//this->racerStartPosition = this->racer->getPos(); //testirat izmjenu
		//std::cout << "resetrirano" << std::endl; //za debug
		//praznimo vektor jer pocinje novi krug
		this->currentLap.clear(); 
		this->currentLapRacerAngle.clear();
	}
}

void Play::render(sf::RenderWindow& window)
{
	//cistimo prethodno na ekranu
	window.clear();

	//tu crtamo
	//view koji prati auto
	window.setView(mv);

	//mapa
	this->map->render(window); 
	this->map->renderWall(window); 

	//auto
	//ghost
	if (!this->bestLap.empty() && !this->BestLapRacerAngle.empty()){
		if (this->newBestLap) {
			this->currentMove = 0;
		}
		if (this->currentMove == 0 && !this->map->getStartLine().intersects(this->racer->getMiddleCheckBox())) {
			this->ghostRacer->render(window);
			this->ghostRacer->setPos(this->racerStartPosition.x, this->racerStartPosition.y);
			//std::cout << "Cekamo nooba" << std::endl; //za debug
		}
		else {
			this->ghostRacer->render(window);
			this->ghostRacer->move(this->bestLap[this->currentMove]);
			this->ghostRacer->setRot(this->BestLapRacerAngle[this->currentMove]);
			currentMove++;
			//std::cout << currentMove << std::endl; //za debug
			if (currentMove == this->bestLap.size()) {
				//std::cout << "brojac resetriran" << std::endl; //za debug
				this->currentMove = 0;
			}
		}
	}
	this->racer->render(window);
	this->racer->move(this->racer->getVelocity());
	this->racer->setRot(this->racer->getAngle());

	//ui elementi
	//view je drugaciji jer su oni uvijek na istom mjestu
	window.setView(window.getDefaultView());
	this->timing->renderTime(window, *this->map);

	//prikazujemo nacrtamo
	window.display();
}

bool Play::getExit()
{
	return this->exit;
}

