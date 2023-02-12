#include <stdlib.h>
#include <iostream>

#include <SFML/Graphics.hpp>

class Circle {
public:
	float radius;
	sf::Color color;
	sf::Vector2f position;
	sf::CircleShape circle;

	sf::Vector2f getPos() {
		return circle.getPosition() +sf::Vector2f(radius / 2.f, radius / 2.f); // For some reasong getPosition() returns the top right corner now
	}

	bool collision(Circle other) { // I'm sorry your eyes have to endure this
		float x1 = getPos().x;
		float y1 = getPos().y;
		float r1 = radius;

		float x2 = other.getPos().x;
		float y2 = other.getPos().y;
		float r2 = other.radius;

		double d = sqrt((x1 - x2) * (x1 - x2)
			+ (y1 - y2) * (y1 - y2));

		//return r1;

		//return (d < r1 + r2) || false;

		return (d <= r1 - r2) ||
			(d <= r2 - r1) ||
			(d <= r1 + r2);
	}
};

class Player : public Circle {
public:
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);

	Player(float radiusin, sf::Vector2f position, sf::Color color = sf::Color::White) {
		circle.setRadius(radiusin);
		circle.setPosition(position);
		circle.setFillColor(color);
		radius = radiusin;
	}

	void update(float drag, int w, int h) {
		velocity.x *= drag;
		velocity.y *= drag;

		circle.move(velocity);

		if (circle.getPosition().x > w || circle.getPosition().x < 0) {
			velocity.x = -velocity.x;
		}
		if (circle.getPosition().y > h || circle.getPosition().y < 0) {
			velocity.y = -velocity.y;
		}
	}

	void center(int w, int h) {
		circle.setPosition(sf::Vector2f(w / 2.f, h / 2.f));
	}
};

class Food : public Circle {
public:
	Food(float radiusin, sf::Color color = sf::Color::Red) {
		circle.setRadius(radiusin);
		circle.setFillColor(color);
		radius = radiusin;
	}

	void newPos(int w, int h) {
		rand(); rand(); rand();
		circle.setPosition(sf::Vector2f(
			rand() % w, 
			rand() % h
		));
	}
};