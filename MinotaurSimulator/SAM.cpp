#include "stdafx.h"
#include <iostream>
#include "SAM.h"
#include "Sim.h"


SAM::SAM(Items &items) 
	: items(items), P(sf::Vector2f(0, 0)), V(sf::Vector2f(0, 0)) {
}

void SAM::update(float dt) {
	sf::Vector2f B = items.fieldAt(P);
	V.x += B.x * dt;
	V.y += B.y * dt;
	P.x += V.x * dt;
	P.y += V.y * dt;
}

void SAM::draw(sf::RenderWindow &window) {
	sf::CircleShape robot(4);
	robot.setPosition(P.x - 4 + Sim::WIN.x / 2, Sim::WIN.y / 2 - P.y - 4);
	robot.setFillColor(sf::Color::Green);
	window.draw(robot);
}

void SAM::stop() {
	V.x = 0;
	V.y = 0;
}