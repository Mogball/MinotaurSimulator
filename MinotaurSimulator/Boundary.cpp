#include "stdafx.h"
#include "Boundary.h"
#include "Sim.h"

const float T = 20; // thickness of the drawing walls

Boundary::Boundary() 
	: center(sf::Vector2f(0, 0)), dim(sf::Vector2f(300, 300)) {
}

sf::Vector2f &Boundary::getP() {
	return this->center;
}

sf::Vector2f &Boundary::getD() {
	return this->dim;
}

void Boundary::draw(sf::RenderWindow &window) {
	sf::RectangleShape left(sf::Vector2f(T, 2 * T + dim.y));
	sf::Vector2f pos(center.x - dim.x / 2 - T + Sim::WIN.x / 2,
		center.y - dim.y / 2 - T + Sim::WIN.y / 2);
	left.setPosition(pos);
	left.setFillColor(sf::Color::Blue);
	window.draw(left);
	pos.x += T + dim.x;
	left.setPosition(pos);
	window.draw(left);
	sf::RectangleShape top(sf::Vector2f(dim.x, T));
	pos.x -= dim.x;
	top.setPosition(pos);
	top.setFillColor(sf::Color::Blue);
	window.draw(top);
	pos.y += T + dim.y;
	top.setPosition(pos);
	window.draw(top);
}