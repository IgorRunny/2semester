#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Ball.hpp"
#include "Platform.hpp"
#include <chrono>
#include <thread>
#include "Log.hpp"
#include <memory>

namespace ib

{
	class Window
	{
	private:
		int i_width = 0, i_high = 0;
		std::string i_caption = "";

	protected:
		bool i_error = 0;
		sf::Font i_font;
		std::string i_str = "";
		sf::Text i_text;
		std::unique_ptr<sf::RenderWindow> i_window;   // smart pointer
		sf::Vector2i mousePos;

	public:

		Window();

		virtual void setText(std::string str, float x, float y, int size);

		virtual bool getError();

		void setCaption(const std::string& caption);

		void setResolution(int width, int high);

		void setup();

		virtual ~Window();

	};

	class Game : public Window
	{
	private:
		int i_count = 0;
		ib::Button i_button_back_to_menu{ {225,300}, "Menu" };

	public:

		Game();

		void runGame();

		void setText(std::string str, float x, float y, int size);

		~Game();

	};

	class Info : public Window
	{
	private:
		std::ifstream i_file;
		sf::Text tmp_text;                                                         // for file 
		sf::Font font_for_tmp;                                                     //
		std::string tmp_str = "";                                                  //
		int high = 60;	                                                           //
		int number_of_strs = 0;                                                      //

		std::unique_ptr<sf::Text[]> strings = std::make_unique<sf::Text[]>(24);    // smart pointer

		ib::Button i_button_back{ {30,720}, "Back" };

	public:

		Info();

		void runInfo();

		~Info();

	};

	class Menu : public Window
	{
	private:
		ib::Button i_button_game{ {225,200}, "Play" };
		ib::Button i_button_info{ {225,300}, "Info" };
		ib::Button i_button_exit{ {225,600}, "Exit" };

	public:

		Menu();

		void runMenu();

		~Menu();

	};

}