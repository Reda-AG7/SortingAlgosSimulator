#include "Delayer.h"

Delayer::Delayer(float pos_x, float pos_y)
{
	buttonWidth = 30;
	delayTime = 1;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	float buttonWidth = 30.0f;
	add = new Button(pos_x + 3* buttonWidth, pos_y, buttonWidth, buttonWidth, "+");
	sub = new Button(pos_x, pos_y, buttonWidth, buttonWidth, "-");
	value = new sf::Text();
	title = new sf::Text();
	font.loadFromFile("Dosis-Regular.ttf");
	title->setString("Delay Time (ms)");
	title->setFont(font);
	title->setCharacterSize(18u);
	sf::FloatRect titleRec = title->getLocalBounds();
	title->setOrigin(titleRec.left + titleRec.width / 2.0f, titleRec.top + titleRec.height / 2.0f);
	title->setPosition(sf::Vector2f(pos_x + 60.0f, pos_y - 10.0f));


	value->setString(std::to_string(delayTime));
	value->setFont(font);
	value->setCharacterSize(18u);
	sf::FloatRect valueRec = value->getLocalBounds();
	value->setOrigin(valueRec.left + valueRec.width/2.0f, valueRec.top + valueRec.height / 2.0f);
	value->setPosition(sf::Vector2f(pos_x+60.0f, pos_y+ buttonWidth /2.0f));
}

Delayer::~Delayer(){
	delete add;
	delete sub;
	delete value;
	delete title;
}

void Delayer::update(const sf::Vector2f& position) {
	add->update(position);
	if (add->buttonPressed()) delayTime++;
	sub->update(position);
	if (sub->buttonPressed()) delayTime--;
	if (delayTime <= 1) delayTime = 1;

	value->setString(std::to_string(delayTime));
	sf::FloatRect valueRec = value->getLocalBounds();
	value->setOrigin(valueRec.left + valueRec.width / 2.0f, valueRec.top + valueRec.height / 2.0f);
	value->setPosition(sf::Vector2f(pos_x + 60.0f, pos_y + buttonWidth / 2.0f));
}

void Delayer::render(sf::RenderTarget& target) {
	add->render(target);
	sub->render(target);
	target.draw(*value);
	target.draw(*title);
}

unsigned Delayer::getDelayTime() const
{
	return delayTime;
}
void Delayer::setDelayTime(unsigned delayTime) {
	this->delayTime = delayTime;
}