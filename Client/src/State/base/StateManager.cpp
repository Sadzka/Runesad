//
// Created on 13.06.2021.
//

#include "State/base/StateManager.hpp"
#include "Base/SharedContext.hpp"

StateManager::StateManager() : currentState(nullptr) {
    registerState<StateMain>(StateType::Main);
    registerState<StateGame>(StateType::Game);
    registerState<StateGameEditor>(StateType::GameEditor);
}

StateManager::~StateManager() {
    for (auto itr : states) {
        itr.second->onDestroy();
        delete itr.second;
    }
}

void StateManager::draw() {
    if (states.empty()) { return; }

    SharedContext::getWindow()->getRenderWindow()->setView(currentState->getView());
    currentState->draw();
}

void StateManager::lateDraw() {
    if (states.empty()) { return; }

    SharedContext::getWindow()->getRenderWindow()->setView(currentState->getView());
    currentState->lateDraw();
}

void StateManager::update(const float &dTime) {
    currentState->update(dTime);
//    for (auto & state : states) {
//        state.second->update(dTime);
//    }
}

void StateManager::switchTo(const StateType &type) {
    auto newState = states.find(type);
    if (currentState) { currentState->deactivate(); }

    if (newState == states.end()) { currentState = createState(type); }
    else { currentState = newState->second; }

    currentStateType = type;
    currentState->activate();
}

void StateManager::switchToAndRemoveCurrent(const StateType &type) {
    if (currentStateType == type) { throw std::runtime_error("Can't switch to current state"); }
    switchTo(type);
    removeState(currentStateType);
}

State *StateManager::createState(const StateType &type) {
    auto createState = stateFactory.find(type);
    if (createState == stateFactory.end()) { throw std::runtime_error("state id not found."); }

    State *state = createState->second();

    state->getView() = SharedContext::getWindow()->getRenderWindow()->getDefaultView();

    states.insert(std::make_pair(type, state));
    state->onCreate();
    return state;
}

void StateManager::removeState(const StateType &type) {
    for (auto & itr : states) {
        if (itr.first == type) {
            itr.second->onDestroy();
            delete itr.second;
            states.erase(type);
            return;
        }
    }
}
