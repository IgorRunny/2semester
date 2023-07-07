#include "Button.hpp"


namespace ib
{
	Button::Button(PosButton pos_button, std::string str) {
		i_font.loadFromFile("arial.ttf");
		i_str = str;
		i_text_for_button.setFont(i_font);
		i_text_for_button.setString(str);
		i_text_for_button.setCharacterSize(40);
		i_text_for_button.setOrigin(55, 25);
		i_text_for_button.setPosition(pos_button.x + 150 / 2.0, pos_button.y + 50 / 2.0);

		i_pos_button = pos_button;
		i_button = std::make_unique<sf::RectangleShape>(sf::Vector2f(150, 50));
		i_button->setFillColor(sf::Color(170, 0, 0));
		i_button->setPosition(i_pos_button.x, i_pos_button.y);
	}

	sf::RectangleShape* Button::Get() {
		return i_button.get();
	}

	void Button::SetColorTextButton(int R, int G, int B) {
		i_text_for_button.setFillColor(sf::Color(R, G, B));
	}

	sf::Text Button::GetText() {
		return  i_text_for_button;
	}

}