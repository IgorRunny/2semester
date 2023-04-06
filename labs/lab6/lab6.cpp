#include <iostream>
#include "Log.hpp"

int main()
{
    std::cout << "Hello World!\n";
    mrLogger::Log::Log(mrLogger::LogLevel::DEBUG);
    mrLogger::Log::Report(mrLogger::LogType::INFO, "test");
    mrLogger::Log::Report(mrLogger::LogType::DEBUG, "test");
    mrLogger::Log::Report(mrLogger::LogType::ERROR, "test");

}