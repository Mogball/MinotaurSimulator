#pragma once
#include <SFML\Graphics.hpp>

class Arrow {
public:
	Arrow(sf::Vector2f P, sf::Vector2f B);
	void draw(sf::RenderWindow &window);
private:
	static const sf::Font font;
	sf::Vector2f P; // position
	sf::Vector2f B; // magnitude
	// Transform the point onto the graphics plane
	sf::Vector2f transform(sf::Vector2f P);
};