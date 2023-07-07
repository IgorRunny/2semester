#include "Game.hpp"
#include "Platform.hpp"
#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <string>


namespace ib
{
	Window::Window() {}

	void Window::setText(std::string str, float x, float y, int size) {
		i_font.loadFromFile("arial.ttf");
		i_str = str;
		i_text.setFont(i_font);
		i_text.setString(str);
		i_text.setCharacterSize(size);
		i_text.setPosition(x, y);
	}

	bool Window::getError() {
		return i_error;
	}

	void Window::setCaption(const std::string& caption) {
		i_caption = caption;
	}

	void Window::setResolution(int width, int high) {
		i_width = width;
		i_high = high;
	}
	void Window::setup() {
		i_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(i_width, i_high), i_caption);
	}

	Window::~Window() {

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Game::Game() {}

	void Game::runGame() {

		ib::Ball ball({ 240,350 }, { 3,-3 }, 15);
		ib::Rect rect({ 240,750 }, 3, 120, 25);

		while (i_window->isOpen())
		{

			sf::Event event;

			ball.move();
			ball.collision(rect.getPosX());
			rect.moveRect();


			while (i_window->pollEvent(event))
			{
				i_count = ball.GetCounter();
				setText("Score ", 10, 10, 30);

				if (!ball.GetCanPlay()) {
					rect.ChangeSpeed(0);

				}

				mousePos = sf::Mouse::getPosition(*i_window.get());
				i_button_back_to_menu.Get()->setFillColor(sf::Color(170, 0, 0));
				i_button_back_to_menu.SetColorTextButton(128, 140, 17);

				if (i_button_back_to_menu.Get()->getGlobalBounds().contains(mousePos.x, mousePos.y)) {

					i_button_back_to_menu.Get()->setFillColor(sf::Color(90, 0, 0));
					i_button_back_to_menu.SetColorTextButton(128, 50, 17);

					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.key.code == sf::Mouse::Left) {
							mrLogger::Log::Report(mrLogger::LogType::INFO, "Your Score is " + std::to_string(i_count));
							i_window->close();
						}
					}
				}

				if (event.type == sf::Event::Closed) {
					mrLogger::Log::Report(mrLogger::LogType::INFO, "Your Score is " + std::to_string(i_count));
					i_window->close();
				}


			}
			i_window->clear();
			i_window->draw(i_text);
			i_window->draw(*rect.Get());
			i_window->draw(*ball.Get());
			if (!ball.GetCanPlay()) {
				i_window->draw(*i_button_back_to_menu.Get());
				i_window->draw(i_button_back_to_menu.GetText());
			}
			i_window->display();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void Game::setText(std::string str, float x, float y, int size) {

		i_font.loadFromFile("arial.ttf");
		i_str = str + std::to_string(i_count);
		i_text.setFont(i_font);
		i_text.setString(i_str);
		i_text.setCharacterSize(size);
		i_text.setPosition(x, y);

	}

	Game::~Game() {}

	////////////////////////////////////////////////////////////////////////////////////////////

	Info::Info() {}

	void Info::runInfo() {
		font_for_tmp.loadFromFile("arial.ttf");
		tmp_text.setFont(i_font);
		tmp_text.setCharacterSize(24);

		i_file.open("log.txt");

		while (getline(i_file, tmp_str)) {
			if (tmp_str.find("[INFO]", 0) != -1) {
				tmp_text.setString(tmp_str);
				tmp_text.setPosition(20, high);
				high += 30;
				try
				{
					if (number_of_strs >= 24) {
						i_error = 1;
						throw std::overflow_error("error, no memory for Info");
					}

					strings[number_of_strs++] = tmp_text;
				}
				catch (const std::overflow_error& ex)
				{
					mrLogger::Log::Report(mrLogger::LogType::ERROR, ex.what());
					break;
				}
				tmp_str = "";
			}
		}

		while (i_window->isOpen())
		{
			setText("Information", 180, 10, 40);
			sf::Event event;
			mousePos = sf::Mouse::getPosition(*i_window.get());
			while (i_window->pollEvent(event))
			{

				if (event.type == sf::Event::Closed) {
					i_window->close();
				}

				i_button_back.Get()->setFillColor(sf::Color(170, 0, 0));
				i_button_back.SetColorTextButton(128, 140, 17);

				if (i_button_back.Get()->getGlobalBounds().contains(mousePos.x, mousePos.y)) {

					i_button_back.Get()->setFillColor(sf::Color(90, 0, 0));
					i_button_back.SetColorTextButton(128, 50, 17);

					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.key.code == sf::Mouse::Left) {
							i_window->close();
						}
					}
				}

			}

			i_window->clear();
			i_window->draw(i_text);
			for (int i = 0; i < number_of_strs; i++) {
				i_window->draw(strings[i]);
			}
			i_window->draw(*i_button_back.Get());
			i_window->draw(i_button_back.GetText());
			i_window->display();

		}

	}

	Info::~Info() {
		i_file.close();
	}

	//////////////////////////////////////////////////////////

	Menu::Menu() {}

	void Menu::runMenu() {
		i_button_game.SetColorTextButton(128, 140, 17);
		i_button_info.SetColorTextButton(128, 140, 17);

		while (i_window->isOpen())
		{

			sf::Event event;
			mousePos = sf::Mouse::getPosition(*i_window.get());

			while (i_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					if (!getError()) {
						mrLogger::Log::Report(mrLogger::LogType::ERROR, "No errors");
					}
					i_window->close();
				}

				i_button_game.Get()->setFillColor(sf::Color(170, 0, 0));
				i_button_game.SetColorTextButton(128, 140, 17);


				if (i_button_game.Get()->getGlobalBounds().contains(mousePos.x, mousePos.y)) {

					i_button_game.SetColorTextButton(128, 50, 17);
					i_button_game.Get()->setFillColor(sf::Color(90, 0, 0));


					if (event.type == sf::Event::MouseButtonPressed) {

						if (event.key.code == sf::Mouse::Left) {
							ib::Game game;
							game.setResolution(600, 800);
							game.setCaption("Pong");
							game.setup();
							game.runGame();
						}
					}
				}

				i_button_info.Get()->setFillColor(sf::Color(170, 0, 0));
				i_button_info.SetColorTextButton(128, 140, 17);

				if (i_button_info.Get()->getGlobalBounds().contains(mousePos.x, mousePos.y)) {

					i_button_info.Get()->setFillColor(sf::Color(90, 0, 0));
					i_button_info.SetColorTextButton(128, 50, 17);

					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.key.code == sf::Mouse::Left) {
							ib::Info info;
							info.setResolution(600, 800);
							info.setCaption("Information");
							info.setup();
							info.runInfo();
						}
					}
				}

				i_button_exit.Get()->setFillColor(sf::Color(170, 0, 0));
				i_button_exit.SetColorTextButton(128, 140, 17);

				if (i_button_exit.Get()->getGlobalBounds().contains(mousePos.x, mousePos.y)) {

					i_button_exit.Get()->setFillColor(sf::Color(90, 0, 0));
					i_button_exit.SetColorTextButton(128, 50, 17);

					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.key.code == sf::Mouse::Left) {
							if (!getError()) {
								mrLogger::Log::Report(mrLogger::LogType::ERROR, "No errors");
							}
							i_window->close();
						}
					}
				}
			}
			i_window->clear();
			i_window->draw(*i_button_game.Get());
			i_window->draw(*i_button_info.Get());
			i_window->draw(*i_button_exit.Get());
			i_window->draw(i_button_game.GetText());
			i_window->draw(i_button_info.GetText());
			i_window->draw(i_button_exit.GetText());
			i_window->display();
		}
	}

	Menu::~Menu() {}
}