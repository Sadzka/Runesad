//
// Created by Sadza on 13.06.2021.
//

#pragma once

#ifndef SADZA_STATE_HPP
#define SADZA_STATE_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class State {
public:
    State(const std::string & guiName);

    virtual ~State() {}

    virtual void onCreate() = 0;

    virtual void onDestroy() = 0;

    virtual void activate() = 0;

    virtual void deactivate() = 0;

    virtual void update(const float &dTime) = 0;

    virtual void draw() = 0;

    virtual void lateDraw() = 0;

    sf::View &getView() { return view; }

    bool isTranscendent() const { return transcendent; }

protected:

    sf::View view;
    bool transcendent;
    tgui::Group::Ptr gui;
};


#endif //SADZA_STATE_HPP
