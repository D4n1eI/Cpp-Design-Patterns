#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Rectangle
{
protected:
    int width;
    int height;

public:
    Rectangle(int width, int height) : width{width}, height{height} {}

    int get_width()
    {
        return width;
    }

    int get_height()
    {
        return height;
    }

    virtual void set_width(int width)
    {
        this->width = width;
    }

    virtual void set_height(int height)
    {
        this->height = height;
    }

    int area()
    {
        return width * height;
    }
};

void process(Rectangle &r)
{
    int w = r.get_width();
    r.set_height(10);
    cout << "expected area = " << (w * 10)
         << ", got "
         << r.area()
         << "\n";
}

class Square : public Rectangle
{

public:
    Square(int size) : Rectangle(size,size) {}
    virtual void set_width(int width) override{
        this->width = this->height = width;
    }

    virtual void set_height(int height) override{
        this->height = this->width = height;
    }
};


struct RectangleFactory{
    static Rectangle create_rectangle(int w,int h);
    static Rectangle create_square(int size);
};

int main()
{
    Rectangle r{3, 4};
    process(r);

    Square s{5};
    process(s);
    return 0;
}