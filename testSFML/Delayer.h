#pragma once
#include "Button.h"
class Delayer
{
private:
	Button* add;
	Button* sub;
	sf::Text* value;
	sf::Font font;
	unsigned delayTime;
	unsigned buttonWidth;
	float pos_x, pos_y;
	sf::Text* title;
public:
	Delayer(float, float);
	~Delayer();
	void update(const sf::Vector2f&);
	void render(sf::RenderTarget&);
	unsigned getDelayTime() const;
	void setDelayTime(unsigned);
};

