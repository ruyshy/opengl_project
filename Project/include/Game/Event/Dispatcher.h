#pragma once

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <Game/Event/Event.h>

template<typename T>
class Dispatcher 
{
private:
    using SlotType = std::function<void(const Event<T>&)>;
    std::map<T, std::vector<SlotType>> _observers;

public:
    void subscribe(T type, const SlotType& funct) {
        _observers[type].push_back(funct);
    };

    void post(Event<T>& event) {
        if (_observers.find(event.type()) == _observers.end())
            return;

        for (auto&& observer : _observers.at(event.type())) {
            if (!event.isHandled()) observer(event);
        }
    };
private:
};

#endif // !DISPATCHER_H_

