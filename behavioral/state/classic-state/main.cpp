#include <iostream>

struct LightSwitch;

struct State
{
    virtual ~State() = default;

    virtual void on(LightSwitch* ls)
    {
        std::cout << "Light is already on.\n";
    }

    virtual void off(LightSwitch* ls)
    {
        std::cout << "Light is already off.\n";
    }
};

struct OnState;

struct OffState : State
{
    OffState()
    {
        std::cout << "Light is turned off.\n";
    }

    void on(LightSwitch* ls) override;
};

struct OnState : State
{
    OnState()
    {
        std::cout << "Light is turned on.\n";
    }

    void off(LightSwitch* ls) override;
};

struct LightSwitch
{
    State* state;

    LightSwitch()
    {
        state = new OffState();
    }

    void set_state(State* s)
    {
        state = s;
    }

    void on()
    {
        state->on(this);
    }

    void off()
    {
        state->off(this);
    }
};

void OffState::on(LightSwitch* ls)
{
    std::cout << "Switching light on...\n";
    ls->set_state(new OnState());
    delete this;
}

void OnState::off(LightSwitch* ls)
{
    std::cout << "Switching light off...\n";
    ls->set_state(new OffState());
    delete this;
}

int main()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();
}