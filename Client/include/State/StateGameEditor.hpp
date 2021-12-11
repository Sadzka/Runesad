//
// Created by Sadza on 14.06.2021.
//
/*
#ifndef SADZA_STATEGAMEEDITOR_HPP
#define SADZA_STATEGAMEEDITOR_HPP

#include "State.hpp"
#include <functional>

class StateGameEditor : public State {
    friend class WorldEditor;

public:
    StateGameEditor();

    ~StateGameEditor();

    virtual void onCreate();

    virtual void onDestroy();

    virtual void activate();

    virtual void deactivate();

    virtual void update(const float &dTime);

    virtual void draw();

    void clickMenuItem(const std::string &option);

    void openWorldFile(const tgui::String filename);

    void saveWorldFile(const tgui::String filename = "");

    void openTileset(const tgui::String tilesetName);

    void setMenuButtonsEnabled(const bool &b = true);

    void resetView();

private:
    float eTime;
    std::string currentPath;
};

#endif //SADZA_STATEGAMEEDITOR_HPP
*/
