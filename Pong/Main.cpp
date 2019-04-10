#include "stdafx.h"
#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {

	int windowWidth = 1024;
	int windowHeight = 568;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

	int lives = 3;
	int score = 0;

	Bat bat(windowWidth / 2, windowHeight - 20);
	Ball ball(windowWidth / 2, 1);

	Text hud;

	Font font;
	font.loadFromFile("DS-DIGIT.ttf");

	hud.setFont(font);
	hud.setCharacterSize(55);
	hud.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && bat.getPosition().left >= 1) {
			bat.moveLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && bat.getPosition().left + 50 <= windowWidth - 1 ) {
			bat.moveRight();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (ball.getPosition().top > windowHeight) {
			ball.hitBottom();
			lives--;

			if (lives < 1) {
				score = 0;
				lives = 3;
			}
		}

		if (ball.getPosition().top < 0) {
			ball.reboundBatOrTop();
			score++;
		}

		if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth) {
			ball.reboundSides();
		}

		if (ball.getPosition().intersects(bat.getPosition())) {
			ball.reboundBatOrTop();
		}

		ball.update();
		bat.update();

		std::stringstream ss;
		ss << "Score:" << score << "    Lives:" << lives;
		hud.setString(ss.str());

	    window.clear(Color(26, 128, 182, 255));

		window.draw(bat.getShape());

		window.draw(ball.getShape());

		window.draw(hud);

		window.display();
	};
	return 0;
}