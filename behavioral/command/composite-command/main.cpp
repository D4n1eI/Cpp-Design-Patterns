#include <iostream>
#include <vector>

using namespace std;

struct BankAccount
{
    int balance{0};
    int overdraft_limit{-500};

    void deposit(int amount)
    {
        balance += amount;
        cout << "Deposited " << amount
             << " and balance is " << balance << '\n';
    }

    bool withdraw(int amount)
    {
        if (balance - amount >= overdraft_limit)
        {
            balance -= amount;
            cout << "Withdrew " << amount
                 << " and balance is " << balance << '\n';
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const BankAccount& ba)
    {
        os << "Bank account with balance " << ba.balance;
        return os;
    }
};

struct Command
{
    bool flag{false};

    virtual void call() = 0;
    virtual void undo() = 0;

    virtual ~Command() = default;
};

struct BankAccountCommand : public Command
{
    BankAccount& account;

    enum Action
    {
        deposit,
        withdraw
    } action;

    int amount;

    BankAccountCommand(
        BankAccount& account,
        Action action,
        int amount)
        : account(account),
          action(action),
          amount(amount)
    {
    }

    void call() override
    {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            flag = true;
            break;

        case withdraw:
            flag = account.withdraw(amount);
            break;
        }
    }

    void undo() override
    {
        if (!flag)
            return;

        switch (action)
        {
        case deposit:
            account.withdraw(amount);
            break;

        case withdraw:
            account.deposit(amount);
            break;
        }
    }
};

struct CompositeBankAccountCommand
    : public vector<BankAccountCommand>,
      public Command
{
    CompositeBankAccountCommand(
        const initializer_list<BankAccountCommand>& items)
        : vector<BankAccountCommand>(items)
    {
    }

    void call() override
    {
        for (auto& cmd : *this)
            cmd.call();
    }

    void undo() override
    {
        for (auto it = rbegin(); it != rend(); ++it)
            it->undo();
    }
};

struct DependentCompositeBankAccountCommand
    : public CompositeBankAccountCommand
{
    DependentCompositeBankAccountCommand(
        const initializer_list<BankAccountCommand>& items)
        : CompositeBankAccountCommand(items)
    {
    }

    void call() override
    {
        bool ok = true;

        for (auto& cmd : *this)
        {
            if (ok)
            {
                cmd.call();
                ok = cmd.flag;
            }
            else
            {
                cmd.flag = false;
            }
        }

        flag = ok;
    }
};

struct MoneyTransferCommand
    : public DependentCompositeBankAccountCommand
{
    MoneyTransferCommand(
        BankAccount& from,
        BankAccount& to,
        int amount)
        : DependentCompositeBankAccountCommand(
              {
                  BankAccountCommand{
                      from,
                      BankAccountCommand::withdraw,
                      amount},
                  BankAccountCommand{
                      to,
                      BankAccountCommand::deposit,
                      amount},
              })
    {
    }
};

int main()
{
    BankAccount ba, ba2;

    ba.deposit(100);

    cout << ba << '\n';
    cout << ba2 << '\n';

    MoneyTransferCommand cmd{ba, ba2, 50};

    cmd.call();

    cout << ba << '\n';
    cout << ba2 << '\n';

    cmd.undo();

    cout << ba << '\n';
    cout << ba2 << '\n';

    return 0;
}