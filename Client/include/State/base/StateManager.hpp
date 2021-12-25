//
// Created by Sadza on 13.06.2021.
//

#pragma once

#ifndef SADZA_STATEMANAGER_HPP
#define SADZA_STATEMANAGER_HPP

#include <unordered_map>
#include <functional>
#include "AllStates.hpp"

class StateManager {
public:

    StateManager();

    ~StateManager();

    void draw();

    void lateDraw();

    void update(const float &dTime);

    void removeState(const StateType &type);

    void switchTo(const StateType &type);

    void switchToAndRemoveCurrent(const StateType &type);

    StateType getCurrentStateType() { return currentStateType; }
    State *getCurrentState() { return currentState; }

private:
    State * createState(const StateType &type);

    std::unordered_map<StateType, State *> states;
    std::unordered_map<StateType, std::function<State *()> > stateFactory;

    template<class T>
    void registerState(const StateType &type) {
        stateFactory[type] = [this]() -> State * {
            return new T();
        };
    }

    StateType currentStateType;
    State *currentState;

    StateType switchQueue = StateType::Unknown;
    sf::Mutex mutex;
};

#endif //SADZA_STATEMANAGER_HPP
