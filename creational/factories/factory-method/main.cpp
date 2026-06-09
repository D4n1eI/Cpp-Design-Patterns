#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <memory>
#include <sstream>
#include <math.h>

using namespace std;

class Point
{
public:
    float x, y;

    static Point NewCartesian(float x , float y)
    {
        return Point { x, y };
    }

    static Point NewPolar(float r , float t)
    {
        return Point { r*cos(t),r*sin(t)};
    }

    friend ostream & operator <<(ostream &os, Point & p){
        os << "("<<p.x<<","<<p.y<<")";
        return os;
    }

private:
    Point(float a, float b) : x{a}, y{b}
    {
    }
};
int main()
{
    Point p1 = Point::NewPolar(5,4);
    Point p2 = Point::NewCartesian(2,4);
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;

    return 0;
}