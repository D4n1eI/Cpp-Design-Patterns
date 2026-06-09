#pragma once

#include "hot-drink-factory.hpp"

#include "hot-drink.hpp"
#include "coffee-factory.hpp"
#include <map>
#include "tea-factory.hpp"
#include <functional>

class DrinkFactory
{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory()
    {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string &name)
    {
        auto drink = hot_factories[name]->make();
        return drink;
    }
};

class DrinkWithVolumeFactory
{
    std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;

public:
    DrinkWithVolumeFactory()
    {
        factories["tea"] = []()
        {
            auto tea = std::make_unique<Tea>();
            tea->prepare(100);
            return tea;
        };
    }

    std::unique_ptr<HotDrink> make_drink(const std::string & name){
        return factories[name]();
    }
};