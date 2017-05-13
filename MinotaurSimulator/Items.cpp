#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "Items.h"

Items::Items() {
	float fPI = (float)M_PI;
	solenoids[0] = Solenoid(sf::Vector2f(0, 400), fPI, 10, 5, 100); // Top
	solenoids[1] = Solenoid(sf::Vector2f(0, -400), 0, 10, 5, 100); // Bottom
	solenoids[2] = Solenoid(sf::Vector2f(-400, 0), -fPI / 2, 10, 5, 100); // Left
	solenoids[3] = Solenoid(sf::Vector2f(400, 0), fPI / 2, 10, 5, 100); // Right
}

sf::Vector2f Items::fieldAt(sf::Vector2f P) {
	sf::Vector2f Bt(0, 0);
	for (int i = 0; i < 4; i++) {
		sf::Vector2f B = solenoids[i].fieldAt(P);
		Bt.x += B.x;
		Bt.y += B.y;
	}
	return Bt;
}

Solenoid &Items::get(int i) {
	return solenoids[i];
}

void Items::draw(sf::RenderWindow &window) {
	boundary.draw(window);
	for (int i = 0; i < 4; i++) {
		solenoids[i].draw(window);
	}
}

Boundary &Items::getBounds() {
	return boundary;
}