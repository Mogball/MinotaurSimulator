#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Solenoid.h"
#include "Arrow.h"
#include "Sim.h"
#include "Boundary.h"
#include "Items.h"
#include "SAM.h"
#include <SFML\Window\Keyboard.hpp>

void traceMovement(sf::RenderWindow &window, Items items, int n) {
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	sf::Vector2f P((float)mouse.x, (float)mouse.y);
	sf::VertexArray trace(sf::LinesStrip, n + 1);
	trace[0].position = sf::Vector2f(P.x, P.y);
	const float STEP = 1;
	for (int i = 1; i <= n; i++) {
		sf::Vector2f Pp(P.x - Sim::WIN.x / 2, Sim::WIN.y / 2 - P.y);
		sf::Vector2f B = items.fieldAt(Pp);
		P.x += STEP * B.x;
		P.y -= STEP * B.y;
		trace[i].position = sf::Vector2f(P.x, P.y);
	}
	window.draw(trace);
}

// Run the simulation
int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(Sim::WIN.x, Sim::WIN.y), 
		"Minotaur Simulator", sf::Style::Close | sf::Style::Titlebar, settings);

	Items items;
	SAM sam(items);

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			items.get(0).setCurrent(50);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			items.get(0).setCurrent(-50);
		}
		else {
			items.get(0).setCurrent(0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			items.get(1).setCurrent(50);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			items.get(1).setCurrent(-50);
		}
		else {
			items.get(1).setCurrent(0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			items.get(2).setCurrent(50);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			items.get(2).setCurrent(-50);
		}
		else {
			items.get(2).setCurrent(0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			items.get(3).setCurrent(50);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			items.get(3).setCurrent(-50);
		}
		else {
			items.get(3).setCurrent(0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			sam.stop();
		}

		// Start update
		float dt = clock.restart().asSeconds();
		sam.update(dt);

		/*sf::Vector2i mouse = sf::Mouse::getPosition(window);
		sf::Vector2f BB = items.fieldAt(sf::Vector2f(mouse.x - Sim::WIN.x/2, 
			Sim::WIN.y/2 - mouse.y));
		std::cout << BB.x << " : " << BB.y << std::endl;*/
		// End update

		// Start draw
		window.clear();
		items.draw(window);
		for (int x = -300; x <= 300; x += 30) {
			for (int y = -300; y <= 300; y += 30) {
				sf::Vector2f P((float)x, (float)y);
				sf::Vector2f B = items.fieldAt(P);
				Arrow arr(P, B);
				arr.draw(window);
			}
		}
		sam.draw(window);
		//traceMovement(window, items, 1000);
		window.display();
		// End draw
	}

	return 0;
}
