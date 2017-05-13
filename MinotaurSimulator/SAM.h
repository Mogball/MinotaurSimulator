#pragma once
#include <SFML/Graphics.hpp>
#include "Items.h"

class SAM {
public:
	SAM(Items &items);
	void draw(sf::RenderWindow &window);
	void update(float dt);
	void stop();
private:
	Items &items;
	sf::Vector2f P;
	sf::Vector2f V;
};

