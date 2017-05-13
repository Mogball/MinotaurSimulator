#include "stdafx.h"
#include "Arrow.h"
#include "Sim.h"
#include <SFML\Graphics.hpp>
#include <cmath>

const float LEN = 25;
const float ARR_X = 3;
const float ARR_Y = 9;

Arrow::Arrow(sf::Vector2f P, sf::Vector2f B) 
	: P(P), B(B) {
	this->P = transform(this->P);
	this->B.y = -this->B.y;
}

sf::Vector2f Arrow::transform(sf::Vector2f P) {
	float Ppx = Sim::WIN.x / 2 + P.x;
	float Ppy = Sim::WIN.y / 2 - P.y;
	sf::Vector2f Pp(Ppx, Ppy);
	return Pp;
}

void Arrow::draw(sf::RenderWindow &window) {
	float a = sqrtf(powf(this->B.x, 2) + powf(this->B.y, 2));
	float x = LEN * this->B.x / a;
	float y = LEN * this->B.y / a;
	sf::Vector2f end(this->P.x + x / 2, this->P.y + y / 2);
	sf::Vector2f start(this->P.x - x / 2, this->P.y - y / 2);
	sf::Vertex line[] = { end, start };
	sf::ConvexShape head(3);
	float xHat = x / LEN;
	float yHat = y / LEN;
	sf::Vector2f t(end.x - ARR_Y * xHat, end.y - ARR_Y * yHat);
	sf::Vector2f t1(t.x + ARR_X * yHat, t.y - ARR_X * xHat);
	sf::Vector2f t2(t.x - ARR_X * yHat, t.y + ARR_X * xHat);
	head.setPoint(0, end);
	head.setPoint(1, t1);
	head.setPoint(2, t2);
	window.draw(line, 2, sf::Lines);
	window.draw(head);
}
