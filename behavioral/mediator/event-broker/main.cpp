

#include <boost/signals2.hpp>
#include <iostream>
#include <string>
#include <vector>

struct Player;
struct EventData
{
    virtual void print() const = 0;
};

struct PlayerScoreData : EventData
{
    std::string player_name;
    int goals_scored;

    PlayerScoreData(const std::string &player_name, const int goals_scored) : player_name{player_name}, goals_scored{goals_scored} {}

    void print() const override
    {
        std::cout << player_name << " has scored! (their " << goals_scored << " so far)\n";
    }
};

struct Game
{
    boost::signals2::signal<void(EventData *)> events;
};

struct Player
{
    std::string name;
    int goals_scored{0};
    Game &game;
    Player(const std::string &name, Game &game) : name{name}, game{game} {}

    void score()
    {
        goals_scored++;
        PlayerScoreData ps{name, goals_scored};
        game.events(&ps);
    }
};

struct Coach
{
    Game &game;

    Coach(Game &game) : game{game}
    {
        game.events.connect([](EventData *e) {
            PlayerScoreData * ps = dynamic_cast<PlayerScoreData*>(e);
            if (ps && ps->goals_scored<3){
                std::cout<<"coach says: well done, "<<ps->player_name<<"!\n";
            }
        });
    }
};

int main()
{  
    Game game;
    Player player{"Sam",game};
    Coach coach{game};
    player.score();
    player.score();
    player.score();

    return 0;
}