


#include "ChatRoom.hpp"
#include "Person.hpp"
int main()
{
    ChatRoom room;
    Person john{"John"};
    Person jane{"Jane"};

    room.join(&john);
    room.join(&jane);

    john.say("hi room");

    jane.say("Oh hey john");

    Person simon{"Simon"};
    room.join(&simon);
    simon.say("Hi everyone");

    jane.pm("Simon","glad you found us!");
    return 0;
}