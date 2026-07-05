#include <iostream>
#include <string>
struct Creature
{
    std::string name;
    int attack, defense;

    Creature(const std::string &name, int attack, int defense)
        : name{name}, attack{attack}, defense{defense}
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const Creature &creature)
    {
        os << "name:" << creature.name << ","
           << "attack:" << creature.attack << ","
           << "defense:" << creature.defense;
    }
};

class CreatureModifier
{
    CreatureModifier *next{nullptr};

protected:
    Creature &creature;

public:
    CreatureModifier(Creature &creature) : creature{creature} {}

    void add(CreatureModifier *cm)
    {
        if (next)
            next->add(cm);
        else
            next = cm;
    }

    virtual void handle()
    {
        if (next)
            next->handle();
    }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
    DoubleAttackModifier(Creature &creature) : CreatureModifier{creature} {}
    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreasedDefenseModifier : public CreatureModifier
{
public:
    IncreasedDefenseModifier(Creature &creature) : CreatureModifier{creature} {}

    void handle() override
    {
        if (creature.attack <= 2)
        {
            creature.defense++;
        }
        CreatureModifier::handle();
    }
};

class NoBonuses : public CreatureModifier
{

public:
    NoBonuses(Creature &creature) : CreatureModifier{creature} {}

    void handle() override
    {
    }
};
int main()
{
    Creature goblin{"Goblin", 1, 1};
    CreatureModifier root{goblin};
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r1_2{goblin};

    NoBonuses curse{goblin};
    IncreasedDefenseModifier r2{goblin};

    root.add(&curse);
    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle();

    std::cout << goblin << std::endl;

    return 0;
}