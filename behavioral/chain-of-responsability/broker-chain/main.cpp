#include "boost/signals2.hpp"
#include "boost/flyweight.hpp"
#include "boost/bimap.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"
#include <iostream>

using namespace boost;
using namespace boost::signals2;

struct Query
{
    std::string creature_name;
    enum Argument
    {
        attack,
        defense
    } argument;
    int result;

    Query(const std::string &creature_name, const Argument &argument, const int result)
        : creature_name{creature_name}, argument{argument}, result{result}
    {
    }
};

struct Game
{
    signal<void(Query &)> queries;
};

struct Creature
{
    Game &game;
    int attack, defense;
    std::string name;

public:
    Creature(Game &game, const int attack, const int defense, const std::string &name)
        : game{game}, attack{attack}, defense{defense}, name{name}
    {
    }

    int get_attack() const
    {
        Query q{name, Query::Argument::attack, attack};
        game.queries(q);
        return q.result;
    }
    friend std::ostream &operator<<(std::ostream &os, const Creature &creature)
    {
        os << "name:" << creature.name << ","
           << "attack:" << creature.get_attack();
    }
};

class CreatureModifier
{
public:
    Game &game;
    Creature &creature;

    CreatureModifier(Game &game, Creature &creature)
        : game{game}, creature{creature}
    {
    }

    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier
{

public:
    connection conn;

    DoubleAttackModifier(Game &game, Creature &creature) : CreatureModifier(game, creature)
    {
        conn = game.queries.connect([&](Query &q)
                                    {
            if (q.creature_name==creature.name && q.argument==Query::Argument::attack){
                q.result*=2;
            } });
    }

    ~DoubleAttackModifier()
    {
        conn.disconnect();
    }
};
int main()
{
    Game game;
    Creature goblin(game, 2, 2, "Strong goblin");

    std::cout << goblin << std::endl;

    {
        DoubleAttackModifier dam{game, goblin};
        std::cout << goblin << std::endl;
    }

    std::cout << goblin << std::endl;
}