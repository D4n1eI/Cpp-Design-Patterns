#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <memory>
#include <sstream>
#include <cmath>
#include <map>

#include <boost/lexical_cast/lexical_cast_old.hpp>

using namespace boost;

using namespace std;

class Database
{
public:
    virtual int get_population(const string &name) = 0;
};

class SingletonDatabase : public Database
{
private:
    map<string, int> capitals;

    SingletonDatabase()
    {
        cout << "Initializing Database\n";
        ifstream ifs("capitals.txt");
        string s, s2;
        while (getline(ifs, s))
        {
            getline(ifs, s2);
            int pop = lexical_cast<int>(s2);
            capitals[s] = pop;
        }
    }

public:
    SingletonDatabase(SingletonDatabase const &) = delete;
    void operator=(SingletonDatabase const &) = delete;

    static SingletonDatabase &get()
    {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const string &city) override
    {
        return capitals[city];
    }
};

class DummyDatabase : public Database
{
    map<string, int> capitals;

public:
    DummyDatabase()
    {
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }

    int get_population(const string &city) override
    {
        return capitals[city];
    }
};



struct ConfigurableRecordFinder{
    Database & db;
    ConfigurableRecordFinder(Database &db):db{db}{}

    int total_population(vector<string> names)
    {
        int result{0};
        for (auto &name : names)
        {
            result += db.get_population(name);
        }
        return result;
    }
};
struct SingletonRecordFinder
{
    int total_population(vector<string> names)
    {
        int result{0};
        for (auto &name : names)
        {
            result += SingletonDatabase::get().get_population(name);
        }
        return result;
    }
};

int main()
{
    string city = "Tokyo";
    cout << city << " has population " << SingletonDatabase::get().get_population(city) << endl;
    return 0;
}