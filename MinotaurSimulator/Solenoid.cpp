#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "Solenoid.h"

const float MU = 5000;
const float WIDTH = 20;

Solenoid::Solenoid() 
	: P(sf::Vector2f(0, 0)), theta(0), n(0), R(0), l(0), i(0) {
}

Solenoid::Solenoid(sf::Vector2f P, float theta, float n, float R, float l) 
	: P(P), theta(theta), n(n), R(R), l(l), i(0) {
}

// Rotate a point, usually onto the solenoid plane
sf::Vector2f Solenoid::rotate(sf::Vector2f Q, float angle) {
	// Rotate the point into the correct orientation
	float Qpx = Q.x * cosf(angle) - Q.y * sinf(angle);
	float Qpy = Q.y * cosf(angle) + Q.x * sinf(angle);
	sf::Vector2f Qp(Qpx, Qpy);
	return Qp;
}

sf::Vector2f Solenoid::translate(sf::Vector2f Q, sf::Vector2f P) {
	return sf::Vector2f(Q.x - P.x, Q.y - P.y);
}

// Draw the solenoid
void Solenoid::draw(sf::RenderWindow &window) {
	// Get the coordinates
	float s = sinf(this->theta);
	float c = cosf(this->theta);
	float l2 = this->l / 2;
	float dx1 = l2 * s;
	float dy1 = l2 * c;
	float dx2 = WIDTH / 2 * c;
	float dy2 = WIDTH / 2 * s;
	sf::Vector2f north(P.x - dx1 + Sim::WIN.x/2, Sim::WIN.y/2 - P.y - dy1);
	sf::Vector2f south(P.x + dx1 + Sim::WIN.x/2, Sim::WIN.y/2 - P.y + dy1);
	sf::ConvexShape rect(4);
	rect.setPoint(0, sf::Vector2f(north.x - dx2, north.y + dy2));
	rect.setPoint(1, sf::Vector2f(north.x + dx2, north.y - dy2));
	rect.setPoint(2, sf::Vector2f(south.x + dx2, south.y - dy2));
	rect.setPoint(3, sf::Vector2f(south.x - dx2, south.y + dy2));
	rect.setFillColor(sf::Color::Magenta);
	window.draw(rect);
}

// Change the current in the solenoid
void Solenoid::setCurrent(float i) {
	this->i = i;
}

float Solenoid::getCurrent() {
	return this->i;
}

// Helper functions
float Solenoid::getA(float x, float y) {
	float a = (powf(x, 2) + powf(y, 2));
	a = powf(a, -1.5);
	return a;
}

// Get the magnetic field vector at a point
sf::Vector2f Solenoid::fieldAt(sf::Vector2f Q) {
	sf::Vector2f Qp = rotate(translate(Q, this->P), -this->theta);
	float k = MU * this->i * this->n * powf(this->R, 2) / 4.0f;
	float l2 = this->l / 2;
	float yp1 = Qp.y - l2;
	float yp2 = Qp.y + l2;
	float a1 = getA(Qp.x, yp1);
	float a2 = getA(Qp.x, yp2);
	float Bx = k * Qp.x * (a1 - a2);
	float By = k * (yp1 * a1 - yp2 * a2);
	sf::Vector2f B(Bx, By);
	sf::Vector2f Bp = rotate(B, this->theta);
	return Bp;
}