#include <iostream>
#include <vector>
#include "math.h"

const double PI = acos(-1.0);

enum class Color
{
    WHITE,
    RED,
    GREEN,
    BLUE,
    BLACK
};

struct Coords
{
    int x;
    int y;
};

class Form
{
private:
    Color i_color;
protected:
    bool flag = true;
    std::vector<Coords> i_coords;
    std::vector<int> i_Sizes;
public:
    Form(Color color, std::vector<Coords> coords, std::vector<int> Sizes) : i_color(color), i_coords(coords), i_Sizes(Sizes)
    {

    }

    virtual void Area() = 0;

    ~Form(){}
};

class Rectangle : public Form
{
public:

    Rectangle(Color color, std::vector<Coords> coords, std::vector<int> Sizes) : Form(color, coords, Sizes)
    {
        if (Sizes.size() != 2 || coords.size() != 4)
        {
            std::cout << "ERROR";
            flag = false;
        }
    }

    void Area() override
    {
        if (flag == true)
        {
            int tmp = i_Sizes[0] * i_Sizes[1];
            std::cout << tmp << "\n";
        }
    }

    virtual ~Rectangle()
    {

    }
};

class Circle : public Form
{
public:

    Circle(Color color, std::vector<Coords> coords, std::vector<int> Sizes) : Form(color, coords, Sizes)
    {
        if (Sizes.size() != 1 || coords.size() != 1)
        {
            std::cout << "ERROR";
            flag = false;
        }
    }

    virtual void Area() override
    {
        if (flag == true)
        {
            std::cout << 2 * PI * i_Sizes[0] << "\n";
        }
    }

    virtual ~Circle()
    {

    }
};

class Triangle : public Form
{
public:

    Triangle(Color color, std::vector<Coords> coords, std::vector<int> Sizes) : Form(color, coords, Sizes)
    {
        if (Sizes.size() != 3 || coords.size() != 3)
        {
            std::cout << "ERROR";
            flag = false;
        }
    }

    virtual void Area() override
    {
        if (flag == true)
        {
            Coords Vector1;
            Coords Vector2;
            Vector1.x = i_coords[1].x - i_coords[0].x;
            Vector1.y = i_coords[1].y - i_coords[0].y;
            Vector2.x = i_coords[2].x - i_coords[0].x;
            Vector2.y = i_coords[1].y - i_coords[0].y;
            double tmp = acos((Vector1.x * Vector2.x + Vector1.y * Vector2.y) / (i_Sizes[0] * i_Sizes[0]));
            std::cout << tmp << "\n";
            std::cout << i_Sizes[0] * i_Sizes[0] * tmp / 2 << "\n";
        }
    }

    virtual ~Triangle()
    {

    }
};

int main()
{
    std::vector<Coords> coords = { {0,0}, {0,1}, {1,1}, {1,0} };
    std::vector<int> Sizes = { 1, 1 };
    Rectangle rect(Color::GREEN, coords, Sizes);
    rect.Area();
    std::vector<Coords> coords1 = { {0,0} };
    std::vector<int> Sizes1 = { 1 };
    Circle circle(Color::GREEN, coords1, Sizes1);
    circle.Area();
    std::vector<Coords> coords2 = { {0,0}, {0,3}, {4,0} };
    std::vector<int> Sizes2 = { 3, 4, 5 };
    Triangle tri(Color::GREEN, coords2, Sizes2);
    tri.Area();
}
