#pragma once
#include "Delayer.h"
#include "Infos.h"
#include<unordered_map>
#include<chrono>
#include<random>

using namespace std::chrono_literals;
class State
{
public:
    //Attributes
    sf::RenderWindow* window;
    sf::RectangleShape* background;
    std::vector<sf::RectangleShape> bars;
    std::vector<Button*> btns;
    std::vector<Button*> algoBtns;
    std::vector<Infos*> data;
    Delayer* delayer;
    sf::Text* title;

    float width, height;
    //std::unordered_map<int, std::string> m;

    sf::Font* boldFont;
    sf::Font* regularFont;
    //Methods
    State();
    ~State();
    void initMainButtons();
    void initAlgoButtons();
    void initAlgoInfo();
    //void initMap();
    void initText();
    void initBars();
    std::string getAlgoName(int);
    void deleteButtons();
};


