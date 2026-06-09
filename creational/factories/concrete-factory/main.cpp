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

    friend ostream &operator<<(ostream &os, Point &p)
    {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

// private: If you keep it public you should be able to access these fields in the Factory class,
// Alternatively, you can use the friend keyword to conceed the private constructor to the Factory class
    Point(float a, float b) : x{a}, y{b}
    {
    }
};

struct PointFactory
{
    
    static Point NewCartesian(float x, float y)
    {
        return Point{x, y};
    }

    static Point NewPolar(float r, float t)
    {
        return Point{r * cos(t), r * sin(t)};
    }
};
int main()
{   
    Point p1 = PointFactory::NewCartesian(2,3);
    Point p2 = PointFactory::NewPolar(2,3);

    std::cout << p1 << "|" << p2 << std::endl;


    return 0;
}