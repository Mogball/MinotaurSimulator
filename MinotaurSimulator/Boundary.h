#pragma once
#include "SFML\Graphics.hpp"

class Boundary {
public:
	Boundary();
	sf::Vector2f &getP();
	sf::Vector2f &getD();
	void draw(sf::RenderWindow &window);
private:
	sf::Vector2f center; // location of the center point (usually origin)
	sf::Vector2f dim; // base and height of the boundary
};

