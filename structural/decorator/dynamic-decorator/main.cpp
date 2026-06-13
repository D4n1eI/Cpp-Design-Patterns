#include <iostream>
#include <sstream>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    Circle(float radius) : radius{radius}
    {
    }
    Circle() {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }

    void resize(float factor)
    {
        radius *= factor;
    }
};

struct Square : Shape
{
    float side;

    Square() {}

    Square() : side{side} {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

struct ColoredShape : Shape
{
    Shape &shape;
    std::string color;

    ColoredShape(Shape &shape, std::string color) : shape{shape}, color{color} {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has the color of " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape &shape;
    u_int8_t transparency;
    TransparentShape(Shape &shape, u_int8_t transparency) : shape{shape}, transparency{transparency}
    {
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

int main()
{
    Square square{};
    ColoredShape red_square{square, "red"};

    TransparentShape my_square(red_square, 51);

    std::cout << square.str() << std::endl
              << red_square.str() << my_square.str() << std::endl;
}