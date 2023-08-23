#ifndef _INFOS_H__
#define _INFOS_H__

#include "SFML\Graphics.hpp"
#include <chrono>
class Infos
{
	private:
		sf::Text data;
		sf::Font font;
		unsigned int numberComparisons;
		std::chrono::milliseconds ms;
		unsigned int characterSize;
	public:
		Infos(float, float, unsigned int, unsigned int);
		Infos(float, float, std::chrono::milliseconds, unsigned int);
		~Infos();
		void update(unsigned int);
		void update(std::chrono::milliseconds&, unsigned&);
		void render(sf::RenderTarget&);
};


#endif

