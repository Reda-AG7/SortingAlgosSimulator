#include "State.h"

State::State()
{
	width = 800;
	height = 600;
	//initMap();
	// //vectors (data)
	btns = std::vector<Button*>(6);
	data = std::vector<Infos*>(2);
	algoBtns = std::vector<Button*>(2);
	bars = std::vector<sf::RectangleShape>(160);
	//window
	window = new sf::RenderWindow(sf::VideoMode(width,height),"Sorting Algorithms");
	window->setFramerateLimit(120);
	window->setVerticalSyncEnabled(false);

	//background
	background = new sf::RectangleShape(sf::Vector2f(width, height));
	background->setFillColor(sf::Color(178, 190, 181));

	//delayer
	delayer = new Delayer(400.0f, 200.0f);

	//Buttons
	initMainButtons();
	initAlgoButtons();

	//data
	initAlgoInfo();

	//fonts
	boldFont = new sf::Font();
	boldFont->loadFromFile("Dosis-Bold.ttf");
	
	regularFont = new sf::Font();
	regularFont->loadFromFile("Dosis-Regular.ttf");

	//bars
	initBars();
	
	
}

State::~State()
{
	delete window;
	delete background;
	delete boldFont;
	delete regularFont;
	deleteButtons();
}

void State::initMainButtons()
{
	btns[0] = new Button(30.0f, 100.0f, 200.0f, 50.0f, "Insertion Sort");
	btns[1] = new Button(30.0f, 160.0f, 200.0f, 50.0f, "Selection Sort");
	btns[2] = new Button(30.0f, 220.0f, 200.0f, 50.0f, "Bubble Sort");
	btns[3] = new Button(30.0f, 280.0f, 200.0f, 50.0f, "Merge Sort"); 
	btns[4] = new Button(30.0f, 340.0f, 200.0f, 50.0f, "Heap Sort"); 
	btns[5] = new Button(30.0f, 400.0f, 200.0f, 50.0f, "Quick Sort"); 
}
void State::initAlgoButtons() {
	algoBtns[0] = new Button(10.0f, 10.0f, 100.0f, 50.0f, "Back");
	algoBtns[1] = new Button(690.0f, 10.0f, 100.0f, 50.0f, "Pause");
}
void State::initAlgoInfo() {
	data[0] = new Infos(20.0f, 120.0f, 0u, 20u);
	data[1] = new Infos(20.0f, 160.0f, 0ms, 20u);
}
void State::initBars()
{
	
}



void State::deleteButtons()
{
	for (auto btn : btns)
		delete btn;
	for (auto btn : algoBtns)
		delete btn;
}





