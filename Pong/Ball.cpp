#include "stdafx.h"
#include "ball.h"

using namespace sf;

Ball::Ball(float startX, float startY, bool flag) {

	position.x = startX;
	position.y = startY;

	state = flag;

	ballShape.setSize(Vector2f(10, 10));
	ballShape.setPosition(position);
}

FloatRect Ball::getPosition() {
	return ballShape.getGlobalBounds();
}

RectangleShape Ball::getShape() {
	return ballShape;
}

float Ball::getXVelocity() {
	return xVelocity;
}

void Ball::reboundSides() {
	xVelocity = -xVelocity;
}

void Ball::reboundBatOrTop() {
	position.y -= (yVelocity * 30);
	yVelocity = -yVelocity;
}

void Ball::moveLeft() {
	position.x -= ballSpeed;
}

void Ball::moveRight() {
	position.x += ballSpeed;
}

void Ball::resetPosition(float xPos, float yPos) {
	position.y = yPos;
	position.x = xPos;
}

void Ball::update(bool state) {
	if (state) {
		position.x += xVelocity;
		position.y += yVelocity;
		ballShape.setPosition(position);
	}
	else {
		ballShape.setPosition(position);
	}
}