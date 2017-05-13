#pragma once
#include "Arrow.h"
#include <SFML\Graphics.hpp>
#include "Boundary.h"
#include "Solenoid.h"

class Items {
public:
	Items();
	sf::Vector2f fieldAt(sf::Vector2f P);
	void draw(sf::RenderWindow &window);
	Solenoid &get(int i);
	Boundary &getBounds();
private:
	Solenoid solenoids[4];
	Boundary boundary;
};