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
        cout << "Deposited " << amount << " and balance is " << balance;
    }

    bool withdraw(int amount)
    {
        if (balance - amount >= overdraft_limit)
        {
            balance -= amount;

            cout << "Withdrew " << amount << " and balance is " << balance;
            return true;
        }
        return false;
    }

public:
    friend ostream &operator<<(ostream &os, BankAccount &ba)
    {
        os << "Bank account with " << ba.balance;
        return os;
    }
};

struct Command
{
    bool flag;
    virtual void call() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

struct BankAccountCommand : Command
{
    BankAccount &account;
    enum Action
    {
        deposit,
        withdraw
    } action;
    int amount;


    
    BankAccountCommand(BankAccount &account, Action action, int amount) : account{account}, action{action}, amount{amount}
    {
        flag = false;
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

        default:
            break;
        }
    }

    void undo() override{
        if (!flag) return;
        switch (action)
        {
        case deposit:
            account.withdraw(amount);
            break;
        case withdraw:
            account.deposit(amount);
            break;
        
        default:
            break;
        }
    }
};

int main()
{
    BankAccount ba;

    vector<BankAccountCommand> commands{BankAccountCommand{ba, BankAccountCommand::deposit, 100},
                                        BankAccountCommand{ba, BankAccountCommand::withdraw, 200}};

    cout << ba << endl;
    for (auto &cmd : commands)
    {
        cmd.call();
    }


    for (auto it = commands.rbegin();it!=commands.rend();it++){
        it->undo();
    }
    cout << ba << endl;

    return 0;
}