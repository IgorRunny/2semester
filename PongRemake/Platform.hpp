#pragma once
#include <SFML/Graphics.hpp>
namespace ib
{

	struct PosRect

	{
		float x;
		float y;
	};

	class Rect

	{

	private:

		PosRect i_posRect;
		float i_speedRect;
		std::unique_ptr<sf::RectangleShape> rect;
		float i_width;
		float i_high;

	public:

		Rect(PosRect posR, float Speed, float width, float high);
		~Rect();
		void ChangeSpeed(float new_speed);
		void moveRect();
		float getPosX();
		sf::RectangleShape* Get();
	};

}