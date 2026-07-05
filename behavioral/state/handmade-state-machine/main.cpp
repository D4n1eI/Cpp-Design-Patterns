#include <iostream>
#include <iostream>
#include <vector>
#include <map>
enum class State
{
    offhook,
    connecting,
    connected,
    onhold,
    onhook,
};

inline std::ostream &operator<<(std::ostream &os, const State &s)
{
    switch (s)
    {
    case State::offhook:
        os << "off the hook";
        break;
    case State::connecting:
        os << "connecting";
        break;

    case State::connected:
        os << "connected";
        break;

    case State::onhold:
        os << "on hold";
        break;
    case State::onhook:
        os << "on hook";
        break;
    default:
        break;
    }
    return os;
}

enum class Trigger
{
    calldialed,
    hungup,
    callconnected,
    placedonhold,
    takenoffhold,
    leaveamessage,
    stopusingphone
};

inline std::ostream &operator<<(std::ostream &os, const Trigger &s)
{
    switch (s)
    {
    case Trigger::calldialed:
        os << "call dialed";
        break;
    case Trigger::hungup:
        os << "hung up";
        break;

    case Trigger::callconnected:
        os << "call connected";
        break;

    case Trigger::placedonhold:
        os << "placed on hold";
        break;
    case Trigger::takenoffhold:
        os << "taken off hold";
        break;
    case Trigger::leaveamessage:
        os << "leave a message";
        break;

    case Trigger::stopusingphone:
        os << "stop using phone";
        break;
    default:
        break;
    }
    return os;
}

int main()
{
    std::map<State, std::vector<std::pair<Trigger, State>>> rules;
    rules[State::offhook] = {
        {Trigger::calldialed, State::connecting},
        {Trigger::stopusingphone, State::onhook}};

    rules[State::connecting] = {
        {Trigger::hungup, State::offhook},
        {Trigger::callconnected, State::connected}};

    rules[State::connected] = {
        {Trigger::leaveamessage, State::offhook},
        {Trigger::hungup, State::offhook},
        {Trigger::placedonhold, State::onhold}};

    rules[State::onhold] = {
        {Trigger::takenoffhold, State::connected},
        {Trigger::hungup, State::offhook}};

    State currentState{State::offhook},
        exitState{State::onhook};

    while (true)
    {
        std::cout << "The phone is currently " << currentState << "\n";
    select_trigger:
        std::cout << "Select a trigger:\n";
        int i = 0;
        for (auto item : rules[currentState])
        {
            std::cout << i++ << ". " << item.first << "\n";
        }

        int input;
        std::cin >> input;

        if (input < 0 || (input + 1) > rules[currentState].size())
        {
            std::cout << "Incorrect option. Please try again.\n";
            goto select_trigger;
        }

        currentState = rules[currentState][input].second;
        if (currentState==exitState)break;

    }
    std::cout<<"We're done using the phone.";
    return 0;
}