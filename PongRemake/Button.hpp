#pragma once
#include <SFML/Graphics.hpp>
#include "Log.hpp"

namespace ib {
	struct PosButton
	{
		float x;
		float y;
	};
	class Button
	{

	private:

		PosButton i_pos_button;
		std::unique_ptr<sf::RectangleShape> i_button;
		sf::Font i_font;
		std::string i_str = "";
		sf::Text i_text_for_button;

	public:

		Button(PosButton pos_button, std::string str);
		sf::RectangleShape* Get();
		void SetColorTextButton(int R, int G, int B);
		sf::Text GetText();

	};
}