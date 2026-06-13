#include <iostream>
#include <array>
#include <numeric>
#include <algorithm> 
// class Creature{
// private:
//     int strength;
//     int intelligence;
//     int agility;

// public:
//     int getStrength() const
//     {
//         return strength;
//     }

//     void setStrength(int value)
//     {
//         strength = value;
//     }

//     int getIntelligence() const
//     {
//         return intelligence;
//     }

//     void setIntelligence(int value)
//     {
//         intelligence = value;
//     }

//     int getAgility() const
//     {
//         return agility;
//     }

//     void setAgility(int value)
//     {
//         agility = value;
//     }

//     double sum()const{
//         return strength+agility+intelligence;
//     }

//     double avg()const{
//         return sum()/3.0;
//     }

//     int max() const{
//         std::max(std::max(strength,agility),intelligence);
//     }
// };


class Creature
{
public:
    enum Abilities
    {
        str,
        agl,
        intl,
        count
    };

private:
    std::array<int, count> abilities;

public:
    int get_strength() const { return abilities[str]; }

    void set_strength(int value) { abilities[str] = value; }

    int get_agility() const { return abilities[agl]; }

    void set_agility(int value) { abilities[agl] = value; }

    int get_intelligence() const { return abilities[intl]; }

    void set_intelligence(int value) { abilities[intl] = value; }

    int sum()const{
        return std::accumulate(abilities.begin(),abilities.end(),0);
    }

    double avg()const{
        return sum()/(double)count;
    }

    int max()const{
        return *std::max_element(abilities.begin(),abilities.end());
    }

};

int main(int ac, char *av[])
{   
    Creature orc{};
    orc.set_strength(16);
    orc.set_agility(11);
    orc.set_intelligence(3);
    std :: cout << "The orc has an average stat of "
                << orc.avg()
                << " and a maxium statistic of " 
                << orc.max()
                << std::endl;
    return 0;
}