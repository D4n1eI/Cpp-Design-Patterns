#include <iostream>

#include <boost/lexical_cast/lexical_cast_old.hpp>
#include <memory>
#include "di.hpp"

using namespace boost;

struct IFoo
{
    virtual std::string name() = 0;
};

struct Foo : public IFoo
{
    static int id;
    Foo() { ++id; };
    std::string name() override
    {
        return "foo" + lexical_cast<std::string>(id);
    }
};

int Foo::id = 0;

struct Bar
{
    std::shared_ptr<IFoo> foo;
};

int main()
{
    auto injector = di::make_injector(
        di::bind<IFoo>().to<Foo>().in(di::singleton));

    auto bar1 = injector.create<std::shared_ptr<Bar>>();
    auto bar2 = injector.create<std::shared_ptr<Bar>>();

    std::cout << bar1->foo->name() << std::endl;
    std::cout << bar2->foo->name() << std::endl;

}