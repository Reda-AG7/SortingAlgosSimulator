#include "Infos.h"

Infos::Infos(float pos_x, float pos_y, unsigned int n, unsigned characterSize)
{
	numberComparisons = n;
	this->characterSize = characterSize;
	data = sf::Text();
	std::string s = "Number of Comparisons : " + std::to_string(numberComparisons);
	font = sf::Font();
	font.loadFromFile("Dosis-Regular.ttf");
	data.setCharacterSize(characterSize);
	data.setString(s);
	data.setFont(font);
	data.setPosition(sf::Vector2f(pos_x,pos_y));
}

Infos::Infos(float pos_x, float pos_y, std::chrono::milliseconds ms, unsigned int charachterSize)
{
	this->characterSize = charachterSize;
	this->ms = ms;
	data = sf::Text();
	std::string s = "Time (ms) : " + std::to_string(ms.count());
	data.setString(s);
	data.setCharacterSize(charachterSize);
	font.loadFromFile("Dosis-Regular.ttf");
	data.setFont(font);
	data.setPosition(sf::Vector2f(pos_x ,pos_y));
}

Infos:: ~Infos() {}

void Infos::update(unsigned int nbComp) {
	numberComparisons = nbComp;
	data.setString("Number of Comparisons : " + std::to_string(numberComparisons));
}
void Infos::update(std::chrono::milliseconds& ms, unsigned& renderDelay)
{
	this->ms = ms;
	data.setString("Time (ms) : " + std::to_string(ms.count()/renderDelay));
}
void Infos::render(sf::RenderTarget& target) {
	target.draw(data);
}