#pragma once
#include "Platform.hpp"
#include <SFML/Graphics.hpp>
namespace ib
{
	struct PosCircle
	{
		float x;
		float y;
	};
	struct SpeedCircle
	{
		float x;
		float y;
	};
	class Ball
	{
	private:
		PosCircle i_posCir;
		SpeedCircle i_speedCir;
		float i_radius;

		std::unique_ptr<sf::CircleShape> i_circle;
		unsigned int i_counter = 0;
		bool CanPlay = 1;

	public:

		Ball(PosCircle posCir, SpeedCircle speedCir, float radius);
		bool& GetCanPlay();
		void move();
		void collision(float x);
		unsigned int& GetCounter();
		sf::CircleShape* Get();
		~Ball();

	};
}