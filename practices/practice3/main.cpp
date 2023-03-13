#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

auto Pi = std::acos(-1);

//class AnimatedText
//{
//private:
//    std::string m_text;
//    double m_DurPerSec;
//    std::vector <std::string> m_arr;
//    void SetArr()
//    {
//        for (int i = 0; i < m_text.size(); i++)
//        {
//            m_arr.push_back(m_text.substr(0, i));
//        }
//    }
//public:
//    AnimatedText(const std::string& text, int duration)
//    {
//        m_text = text;
//        m_DurPerSec = (duration * 1000) / text.size();
//        SetArr();
//    }
//
//    std::string Get()
//    {
//        std::string temp;
//        if (m_arr.size() == 0)
//        {
//            return m_text;
//        }
//        temp = *m_arr.begin();
//        m_arr.erase(m_arr.begin());
//        return temp;
//    }
//    double GetDuration()
//    {
//        return m_DurPerSec;
//    }
//
//};

class KinematicSolver
{
private:
    double i_alpha = 0;
    double i_beta = 0;
    sf::RectangleShape i_shoulder;
    sf::RectangleShape i_forearm;
    sf::Vector2f i_A;
    sf::Vector2f i_B;

public:
    KinematicSolver()
    {
        i_A = sf::Vector2f(500.f, 500.f);

        i_shoulder.setPosition(i_A);
        i_shoulder.setSize(sf::Vector2f(100.f, 5.f));
        i_shoulder.setFillColor(sf::Color::White);
        i_shoulder.setRotation(i_alpha);

        i_B = i_A + i_shoulder.getSize();

        i_forearm.setPosition(i_B);
        i_forearm.setSize(sf::Vector2f(100.f, 3.f));
        i_forearm.setFillColor(sf::Color::White);
        i_forearm.setRotation(i_beta);
    }

    void ChangeSizeShoulder(const sf::Vector2f& size)
    {
        i_shoulder.setSize(size);
    }

    void ChangeSizeForearm(const sf::Vector2f& size)
    {
        i_forearm.setSize(size);
    }

    double GetAlpha()
    {
        return i_alpha;
    }

    double GetBeta()
    {
        return i_beta;
    }

    void Solve(const sf::Vector2f C)
    {
        double a = std::sqrt(std::pow(C.x - i_B.x, 2) + std::pow(C.y - i_B.y, 2));
        std::cout << a << "\t";
        double b = std::sqrt(std::pow(C.x - i_A.x, 2) + std::pow(C.y - i_A.y, 2));
        double c = std::sqrt(std::pow(i_A.x - i_B.x, 2) + std::pow(i_A.y - i_B.y, 2));
        std::cout << c << "\n";
        i_alpha = acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c)) + atan((C.y - i_A.y) / (C.x - i_A.x)); // question about expression in atan function
        i_beta = Pi - acos((pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c)) + i_alpha;

    }

    void Draw(sf::RenderWindow& window)
    {
        i_shoulder.setRotation(i_alpha * 180 / Pi);
        /*double x = i_A.x + (i_shoulder.getSize().x * std::cos(i_alpha * 180 / Pi));
        std::cout << x << "\t";
        double y = i_A.y + (i_shoulder.getSize().x * std::sin(i_alpha * 180 / Pi));
        std::cout << y << "\n";*/
        i_B = i_A + i_shoulder.getSize();

        i_forearm.setPosition(i_B);
        //i_forearm.setRotation(i_beta * 180 / Pi);

        window.draw(i_shoulder);
        window.draw(i_forearm);

    }

    ~KinematicSolver() = default;

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "manipulator");

    KinematicSolver manipulator;
    sf::CircleShape circle(10.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(-10, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            circle.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
            manipulator.Solve(circle.getPosition());
        }

        window.clear();


        window.draw(circle);
        manipulator.Draw(window);
        window.display();

        sf::sleep(sf::milliseconds(int(1000 / 60)));

    }

    return 0;
}