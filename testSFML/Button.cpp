#include "Button.h"

Button::Button(){}
Button::Button(float pos_x, float pos_y, float width, float height, const std::string& title)
{
	isPressed = false;
	this->title = title;
	idleColor = sf::Color(240, 237, 212);
	hoverColor = sf::Color::Green;
	textColor = sf::Color::Black;
	activeColor = sf::Color::Red;

	rec = sf::RectangleShape(sf::Vector2f(width, height));
	rec.setPosition(sf::Vector2f(pos_x, pos_y));
	rec.setFillColor(idleColor);
	
	font = sf::Font();
	font.loadFromFile("Dosis-Regular.ttf");

	text = sf::Text();
	text.setString(title);
	text.setFillColor(textColor);
	text.setFont(font);
	text.setCharacterSize(18u);

	sf::FloatRect textRec = text.getLocalBounds();
	text.setOrigin(textRec.left + textRec.width / 2.0f, textRec.top + textRec.height / 2.0f);
	text.setPosition(sf::Vector2f(pos_x + width / 2.0f , pos_y + height / 2.0f ));
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f& position)
{
	rec.setFillColor(idleColor);
	isPressed = false;
	if (rec.getGlobalBounds().contains(position)) {
		rec.setFillColor(hoverColor);
		isPressed = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			rec.setFillColor(activeColor);
			isPressed = true;
		}
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(rec);
	target.draw(text);
}
bool Button::buttonPressed() {
	return isPressed;
}
const std::string& Button::getTitle() const{
	return title;
}