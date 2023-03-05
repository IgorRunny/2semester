#include <SFML/Graphics.hpp>

class AnimatedText
{
private:
    std::string m_text;
    double m_DurPerSec;
    std::vector <std::string> m_arr;
    void SetArr()
    {
        for (int i = 0; i < m_text.size(); i++)
        {
            m_arr.push_back(m_text.substr(0, i));
        }
    }
public:
    AnimatedText(const std::string& text, int duration)
    {
        m_text = text;
        m_DurPerSec = (duration * 1000) / text.size();
        SetArr();
    }

    std::string Get()
    {
        std::string temp;
        if (m_arr.size() == 0)
        {
            return m_text;
        }
        temp = *m_arr.begin();
        m_arr.erase(m_arr.begin());
        return temp;
    }
    double GetDuration()
    {
        return m_DurPerSec;
    }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Lab 1");
    AnimatedText message("Hello world!", 2);
    std::string temp = message.Get();

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text text(temp, font, 50);
    text.setFillColor(sf::Color::White);


    sf::Clock timer;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (timer.getElapsedTime().asMilliseconds() >= message.GetDuration())
        {
            timer.restart();
            text.setString(message.Get());
        }
        window.draw(text);
        window.display();

        sf::sleep(sf::milliseconds(int(1000 / 60)));

    }

    return 0;
}