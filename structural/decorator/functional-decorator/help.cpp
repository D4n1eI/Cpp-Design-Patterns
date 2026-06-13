#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Flower
{
protected:
    vector<string> colors;
    friend struct RedFlower;
    friend struct BlueFlower;
public:
    ~Flower()=default;
    virtual string str() = 0;

};

struct Rose : Flower
{

    string str() override
    {
        if (colors.empty())
        {
            return "A rose";
        }
        std::ostringstream oss;
        oss << "A rose that is ";
        for (size_t i = 0; i < colors.size(); i++)
        {
            if (i == 0)
            {
                oss << colors[i];
            }
            else
            {
                oss << " and " << colors[i];
            }
        }
        return oss.str();
    }
};

struct RedFlower : Flower
{
    RedFlower(const Flower& flower)
    {
        colors = flower.colors;
        bool has_red = false;
        for (const auto& color : colors)
        {
            if (color == "red")
            {
                has_red = true;
                break;
            }
        }
        if (!has_red)
        {
            colors.push_back("red");
        }
    }

    string str() override
    {
        std::ostringstream oss;
        oss << "A rose that is ";
        for (size_t i = 0; i < colors.size(); i++)
        {
            if (i > 0)
            {
                oss << " and ";
            }
            oss << colors[i];
        }
        return oss.str();
    }
};

struct BlueFlower : Flower
{
    BlueFlower(const Flower& flower)
    {
        colors = flower.colors;
        bool has_blue = false;
        for (const auto& color : colors)
        {
            if (color == "blue")
            {
                has_blue = true;
                break;
            }
        }
        if (!has_blue)
        {
            colors.push_back("blue");
        }
    }

    string str() override
    {
        std::ostringstream oss;
        oss << "A rose that is ";
        for (size_t i = 0; i < colors.size(); i++)
        {
            if (i > 0)
            {
                oss << " and ";
            }
            oss << colors[i];
        }
        return oss.str();
    }
};