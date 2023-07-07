#include "Ball.hpp"
#include <iostream>
#include "Log.hpp"

namespace ib
{
	Ball::Ball(PosCircle posCir, SpeedCircle speedCir, float radius) {
		i_posCir = posCir;
		i_speedCir = speedCir;
		i_radius = radius;
		i_circle = std::make_unique<sf::CircleShape>(i_radius);
		i_circle->setOrigin(i_radius, i_radius);
		i_circle->setFillColor(sf::Color::Blue);
	}

	void Ball::move() {
		i_posCir.x += i_speedCir.x;
		i_posCir.y += i_speedCir.y;
		i_circle->setPosition(i_posCir.x, i_posCir.y);
	}

	unsigned int& Ball::GetCounter() {
		return i_counter;
	}

	bool& Ball::GetCanPlay() {
		return CanPlay;
	}

	void Ball::collision(float x) {
		if ((i_posCir.x + i_radius) >= 600)
			i_speedCir.x = -i_speedCir.x;

		if (i_posCir.x - i_radius <= 0)
			i_speedCir.x = -i_speedCir.x;

		if ((i_posCir.y - i_radius) < 0)
			i_speedCir.y = -i_speedCir.y;

		if ((i_posCir.y + i_radius >= 750) && (i_posCir.x >= x) && (i_posCir.x <= x + 120)) {
			i_counter++;
			i_speedCir.y = -i_speedCir.y;
		}

		if (i_posCir.y + i_radius >= 800) {
			i_speedCir.x = 0;
			i_speedCir.y = 0;
			CanPlay = 0;
		}
	}

	sf::CircleShape* Ball::Get() {
		return i_circle.get();
	}
	Ball::~Ball() {

	}

}