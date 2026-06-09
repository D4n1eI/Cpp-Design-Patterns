#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum class Color
{
    Red,
    Green,
    Blue
};
enum class Size
{
    Small,
    Medium,
    Large
};

struct Product
{
    string name;
    Color color;
    Size size;
};

struct ProductFilter
{
    vector<Product *> by_color(vector<Product *> items, Color color)
    {
        vector<Product *> result;
        for (auto &i : items)
        {
            if (i->color == color)
            {
                result.push_back(i);
            }
        }
        return result;
    }

    vector<Product *> by_size(vector<Product *> items, Size size)
    {
        vector<Product *> result;
        for (auto &i : items)
        {
            if (i->size == size)
            {
                result.push_back(i);
            }
        }
        return result;
    }
};

template <typename T>
struct AndSpecification;

template <typename T>
struct Specification
{
    virtual bool is_satisfied(T *item) = 0;

    AndSpecification<T> operator&&(Specification<T> &other)
    {
        return AndSpecification<T>(*this, other);
    }
};

template <typename T>
struct AndSpecification : Specification<T>
{
    Specification<T> &first;
    Specification<T> &second;

    AndSpecification(Specification<T> &first, Specification<T> &second) : first{first}, second{second} {}

    virtual bool is_satisfied(T *item) override
    {
        if (first.is_satisfied(item) && second.is_satisfied(item))
        {
            return true;
        }
        return false;
    }
};

template <typename T>
struct Filter
{
    virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product>
{
    virtual vector<Product *> filter(vector<Product *> items,
                                     Specification<Product> &spec) override
    {
        vector<Product *> result;
        for (auto &item : items)
        {
            if (spec.is_satisfied(item))
            {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;

    ColorSpecification(Color color) : color{color} {}

    virtual bool is_satisfied(Product *item)
    {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;

    SizeSpecification(Size size) : size{size} {}

    virtual bool is_satisfied(Product *item)
    {
        return item->size == size;
    }
};

int main()
{
    Product apple{"Apple", Color::Green, Size::Small};
    Product tree{"Tree", Color::Green, Size::Large};
    Product house{"House", Color::Blue, Size::Large};

    vector<Product *> items{&apple, &tree, &house};
    ProductFilter pf;
    auto green_things = pf.by_color(items, Color::Green);
    for (auto &item : green_things)
    {
        cout << item->name << " is green\n";
    }
    cout << "=========================\n";

    BetterFilter bf;
    ColorSpecification green(Color::Green);

    for (auto &item : bf.filter(items, green))
    {
        cout << item->name << " is green\n";
    }

    cout << "=========================\n";

    ColorSpecification greenSpec(Color::Green);
    SizeSpecification largeSpec(Size::Large);

    auto spec = greenSpec && largeSpec;

    for (auto &item : bf.filter(items, spec))
    {
        cout << item->name << " is green and large\n";
    }

    return 0;
}