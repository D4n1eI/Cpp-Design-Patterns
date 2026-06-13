#include <iostream>
#include <string>
#include <vector>
struct GraphicObject
{
    virtual void draw() = 0;
};

struct Circle : GraphicObject
{
    virtual void draw() override
    {

        std::cout << "This is a circle.";
    }
};

struct Group : GraphicObject
{
    std::string name;
    std::vector<GraphicObject *> objects;
    Group(std::string name) : name{name}
    {
    }

    virtual void draw() override
    {
        std::cout << "Group " << name.c_str() << " contains " << std::endl;
        for (auto &&o : objects){
            o->draw();
        }
    }
};


int main(){

    Group root("root");
    Circle c1,c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);
    root.objects.push_back(&subgroup);

    root.draw(); 
}