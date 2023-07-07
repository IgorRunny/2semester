#include "Game.hpp"



int main()
{
    mrLogger::Log::Log(mrLogger::LogLevel::RELEASE);

    ib::Menu menu;
    menu.setResolution(600, 800);
    menu.setCaption("Game Menu");
    menu.setup();
    menu.runMenu();

    return 0;
}