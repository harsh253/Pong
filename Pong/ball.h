#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
private:
	Vector2f position;
	RectangleShape ballShape;

	bool state;

	float xVelocity = 0.2f;
	float yVelocity = 0.2f;

	float ballSpeed = .6f;

public:
	Ball(float startX, float startY, bool flag);

	FloatRect getPosition();

	RectangleShape getShape();

	float getXVelocity();

	void reboundSides();

	void reboundBatOrTop();

	void moveLeft();

	void moveRight();

	void resetPosition(float xPos, float yPos);

	void update(bool flag);

};

