#pragma once

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <Game/Event/Event.h>


template<typename T>
class Dispatcher 
{
private:
    using SlotType = function<void(const Event<T>&)>;
    map<T, vector<SlotType>> _observers;
public:

    /**
     * Subscribe an observer
     * @param type  The type of the function to listen to.
     * @param funct function of the observer
     */
    void subscribe(T type, const SlotType& funct) 
    {
        _observers[type].push_back(funct);
    };

    /**
     * Send the event to all the observers
     * @param event event to post
     */
    void post(Event<T>& event) 
    {
        if (_observers.find(event.type()) == _observers.end())
            return;

        //Loop though all observers. If the event is not handled yet we continue to process it.
        for (auto&& observer : _observers.at(event.type())) 
        {
            if (!event.isHandled()) 
                observer(event);
        }
    };
private:
};

#endif // !DISPATCHER_H_

