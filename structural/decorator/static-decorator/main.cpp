#include <iostream>
#include <sstream>
#include <type_traits>
#include <utility>

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

    Square(float side) : side{side} {}

    Square() {}

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

template <typename T>
struct ColoredShape2 : T
{
    std::string color;

    ColoredShape2() {}
    template <typename... Args>
    ColoredShape2(const std::string &color, Args... args) : T(std::forward<Args>(args)...), color{color}
    {
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << T::str() << "has the color " << color;
        return oss.str();
    }
};
template <typename T>
struct TransparentShape2 : T
{
    float transparency;

    TransparentShape2() {}
    template <typename... Args>
    TransparentShape2(const float &transparency, Args... args) : T(std::forward<Args>(args)...), transparency{transparency}
    {
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << T::str() << "has the transparency " << transparency;
        return oss.str();
    }
};


int main()
{
    ColoredShape2<Circle> green_circle{"green", 5};
    std::cout << green_circle.str() << std::endl;
    TransparentShape2<ColoredShape2<Square>> bis{0,"blue",10};
    bis.color = "light blue";
    bis.side = 21;
    std::cout << bis.str() << std::endl;

}