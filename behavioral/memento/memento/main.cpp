#include <string>

#include <iostream>
#include <ostream>

#include <vector>

#include <memory>

class Memento
{
    int balance;

public:
    Memento(int balance) : balance{balance} {}
    friend class BankAccount;
    friend class BankAccount2;
};

class BankAccount
{
    int balance{0};

public:
    BankAccount(int balance) : balance(balance) {}

    Memento deposit(int amount)
    {
        balance += amount;
        return Memento{balance};
    }

    void restore(Memento &memento)
    {
        balance = memento.balance;
    }

    friend std::ostream &operator<<(std::ostream &os, const BankAccount &account)
    {
        os << "balance " << account.balance;
        return os;
    }
};

class BankAccount2
{
    int balance{0};
    std::vector<std::shared_ptr<Memento>> changes;
    int current;

public:
    BankAccount2(int balance) : balance{balance}
    {
        changes.emplace_back(std::make_shared<Memento>(balance));
        current = 0;
    }

    std::shared_ptr<Memento> deposit(int amount)
    {
        balance += amount;
        auto m = std::make_shared<Memento>(balance);
        changes.push_back(m);
        ++current;
        return m;
    }

    void restore(const std::shared_ptr<Memento> &m)
    {
        if (m)
        {
            balance = m->balance;
            changes.push_back(m);
            current = changes.size() - 1;
        }
    }

    std::shared_ptr<Memento> undo()
    {
        if (current > 0)
        {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    std::shared_ptr<Memento> redo()
    {
        if (current + 1 < changes.size())
        {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    friend std::ostream &operator<<(std::ostream &os, const BankAccount2 &account)
    {
        os << "balance " << account.balance;
        return os;
    }
};

int main()
{

    // BankAccount ba{100};
    // auto m1 = ba.deposit(50);
    // auto m2 = ba.deposit(25);

    // std::cout<<ba<<"\n";

    // ba.restore(m1);

    // std::cout<<"Back to m1\n";

    // ba.restore(m2);

    // std::cout<<"Back to m2\n";


    BankAccount2 ba{100};
    ba.deposit(50);
    ba.deposit(25);
    std::cout<<ba<<"\n";

    ba.undo();
    std::cout <<"Undo 1 "<<ba<<"\n";
    ba.undo();
    std::cout <<"Undo 2 "<<ba<<"\n";

    ba.redo();
    std::cout <<"Redo "<<ba<<"\n";


    return 0;
}