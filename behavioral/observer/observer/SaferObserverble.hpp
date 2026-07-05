#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <mutex>

template <typename>
struct Observer;

template <typename T>
class SaferObservable
{
    std::vector<Observer<T> *> observers;
    typedef std::mutex mutex_t;
    mutex_t mtx;

public:
    void notify(T &source, const std::string &field_name)
    {
        std::scoped_lock<mutex_t> lock{mtx};
        for (auto observer : observers)
        if (observer)
            observer->field_changed(source, field_name);
    }

    void subscribe(Observer<T> &observer)
    {
        std::scoped_lock<mutex_t> lock{mtx};

        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T> &observer )
    {
        // std::scoped_lock<mutex_t> lock{mtx};

        // observers.erase(
        //     std::remove(observers.begin(),
        //                 observers.end(),
        //                 &observer),
        //     observers.end());

        auto it  = std::find(std::begin(observers),std::end(observers),&observer);
        if (it != std::end(observers))*it = nullptr;
    }
};