#pragma once
#include "Sim.h"
#include <SFML\Graphics.hpp>

class Solenoid {
public:
	Solenoid();
	Solenoid(sf::Vector2f P, float theta, float n, float R, float l);
	sf::Vector2f fieldAt(sf::Vector2f Q);
	void setCurrent(float i);
	float getCurrent();
	void draw(sf::RenderWindow &window);
private:
	// Position vector
	sf::Vector2f P;
	// Rotation angle radians counterclockwise of x-axis
	float theta;
	// Turn density
	float n;
	// Radius
	float R;
	// Length
	float l;
	// Current through the solenoid
	float i;
	// Helper functions
	float getA(float x, float y);
	sf::Vector2f rotate(sf::Vector2f Q, float theta);
	sf::Vector2f translate(sf::Vector2f Q, sf::Vector2f P);
};