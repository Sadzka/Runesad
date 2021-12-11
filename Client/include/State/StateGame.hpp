//
// Created by Sadza on 13.06.2021.
//

#pragma once

#ifndef SADZA_STATEGAME_HPP
#define SADZA_STATEGAME_HPP

#include "State/base/State.hpp"

class StateGame : public State
{
private:
    float eTime;    //elapsedTime
    float dTime;    //deltaTime
public:
    StateGame();
    ~StateGame();
    virtual void onCreate();
    virtual void onDestroy();
    virtual void activate();
    virtual void deactivate();
    virtual void update(const float & dTime);

    virtual void draw();
};


#endif //SADZA_STATEGAME_HPP
