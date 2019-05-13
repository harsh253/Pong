#include "stdafx.h"
#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {

	int windowWidth = 780;
	int windowHeight = 568;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

	int lives = 3;
	int score = 0;
	bool flag = 0;

	Bat bat(windowWidth / 2, windowHeight - 20);
	Ball ball(windowWidth / 2 + 20, windowHeight-30, flag);

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
			ball.resetPosition(windowWidth / 2 + 20, windowHeight - 30);
			lives--;
			flag = 0;
			bat.resetPosition(windowWidth / 2, windowHeight - 20);

			if (lives < 1) {
				score = 0;
				lives = 3;
			}
		}

		if (ball.getPosition().top < 0) {
			ball.reboundBatOrTop();
			flag = 1;
			score++;
		}

		if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth) {
			ball.reboundSides();
			flag = 1;
		}

		if (ball.getPosition().intersects(bat.getPosition())) {
			ball.reboundBatOrTop();
			flag = 1;
		}

		if (!flag) {
			if (Keyboard::isKeyPressed(Keyboard::Left) && bat.getPosition().left >= 1) {
				bat.moveLeft();
				ball.moveLeft();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right) && bat.getPosition().left + 50 <= windowWidth - 1) {
				bat.moveRight();
				ball.moveRight();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space) && bat.getPosition().left + 50 <= windowWidth - 1) {
				flag = 1;
			}
		}

		ball.update(flag);
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