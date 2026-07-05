#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/signals2/signal.hpp>
#include "SaferObserverble.hpp"

template <typename T>
struct Observer
{
    virtual void field_changed(T &source, const std::string &field_name) = 0;
    virtual ~Observer() = default;
};

template <typename T>
class Observable
{
    std::vector<Observer<T> *> observers;

public:
    void notify(T &source, const std::string &field_name)
    {
        for (auto observer : observers)
        {
            observer->field_changed(source, field_name);
        }
    }

    void subscribe(Observer<T> &observer)
    {
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T> &observer)
    {
        observers.erase(
            std::remove(observers.begin(), observers.end(), &observer),
            observers.end());
    }
};

class Person : public Observable<Person>
{
    int age;

public:
    Person(int age) : age(age) {}

    int get_age() const
    {
        return age;
    }

    void set_age(int age)
    {
        if (this->age == age)
            return;

        this->age = age;
        notify(*this, "age");
    }
};

struct ConsolePersonObserver : Observer<Person>
{
    void field_changed(Person &source, const std::string &field_name) override
    {
        std::cout << "Person's " << field_name << " has changed to ";

        if (field_name == "age")
            std::cout << source.get_age();

        std::cout << '\n';
    }
};

template <typename T>
struct Observable2
{
    boost::signals2::signal<void(T &, const std::string &)> field_changed;
};

class Person2 : public Observable2<Person2>
{
    int age{0};

public:
    int get_age() const
    {
        return age;
    }

    bool get_can_vote() const
    {
        return age >= 16;
    }

    void set_age(int age)
    {
        if (this->age == age)
            return;

        auto old_can_vote = get_can_vote();
        this->age = age;

        if (old_can_vote != get_can_vote())
        {
            field_changed(*this, "can_vote");
        }
    }
};

struct TrafficAdministration : Observer<Person>
{
    void field_changed(Person &source, const std::string &field_name) override
    {
        if (field_name == "age")
        {
            if (source.get_age() < 17)
                std::cout << "Not old enough to drive\n";
            else
            {
                std::cout << "We no longer care\n";
                source.unsubscribe(*this);
            }
        }
    }
};
int main()
{
    Person p{0};
    ConsolePersonObserver cpo;

    p.subscribe(cpo);
    p.set_age(15);
    p.set_age(16);

    Person2 p2;

    auto conn = p2.field_changed.connect(
        [](Person2 &, const std::string &field_name)
        {
            std::cout << field_name << " has changed.\n";
        });

    p2.set_age(20);

    conn.disconnect();
    TrafficAdministration ta;
    p.subscribe(ta);
    p.set_age(15);
    p.set_age(16);
    try
    {
        p.set_age(17);
    }catch (const std::exception & e){
        std::cout << e.what() << "\n";
    }

    return 0;
}