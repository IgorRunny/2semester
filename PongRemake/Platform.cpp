#include "Platform.hpp"

namespace ib
{
	Rect::Rect(PosRect posR, float Speed, float width, float high) {
		i_posRect = posR;
		i_speedRect = Speed;
		i_width = width;
		i_high = high;
		rect = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, high));
		rect->setPosition(i_posRect.x, i_posRect.y);
		rect->setFillColor(sf::Color::Red);
	}

	Rect::~Rect() {

	}

	void Rect::ChangeSpeed(float new_speed) {
		i_speedRect = new_speed;
	}

	void Rect::moveRect() {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (i_posRect.x > 0)) {
			i_posRect.x -= i_speedRect;
			rect->setPosition(i_posRect.x, i_posRect.y);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (i_posRect.x < 480)) {
			i_posRect.x += i_speedRect;
			rect->setPosition(i_posRect.x, i_posRect.y);
		}
	}

	float Rect::getPosX() {
		return i_posRect.x;
	}

	sf::RectangleShape* Rect::Get() {
		return rect.get();
	}

}