#pragma once
#include "SFML\Graphics.hpp"
#include<iostream>
#include <string>
class Button
{
private:
	sf::RectangleShape rec;
	sf::Text text;
	sf::Font font;
	sf::Color textColor, idleColor, hoverColor, activeColor;
	std::string title;
	bool isPressed;

public:
	Button();
	Button(float, float, float, float, const std::string&);
	~Button();
	void update(const sf::Vector2f&);
	void render(sf::RenderTarget&);
	bool buttonPressed();
	const std::string& getTitle() const;
};

