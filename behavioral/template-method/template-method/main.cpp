
#include <iostream>
class Game
{
public:
    void run()
    {
        start();
        while (!have_winner())
        {
            take_turn();
        }
        std::cout << "Player " << get_winner() << " wins\n";
    }

protected:
    int number_of_players;
    int current_player;

    Game(int number_of_players) : number_of_players{number_of_players}
    {
    }

    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;
};

class Chess : public Game
{
    Chess(int number_players) : Game(2)
    {
    }

protected:
    void start() override
    {
        std::cout << "Starting a game of chess with 2 players";
    }

    bool have_winner()
    {
        return turn == max_turns;
    }


    void take_turn(){
        std::cout<<"Turn "<<turn<< " taken by player "<<current_player<<"\n";
        ++turn;
        current_player= (current_player+1)%number_of_players;
    }

private:
    int turn{0},
        max_turns{10};
};
int main() {
    
    return 0;
}