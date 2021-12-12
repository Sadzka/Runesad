#pragma  once

#ifndef SADZA_WORLDEDITOR_HPP
#define SADZA_WORLDEDITOR_HPP

#include <functional>
#include <TGUI/tgui.hpp>
#include "World/Tile.hpp"

#include "Utils/StringUtils.hpp"

class StateGameEditor;

class WorldEditor {
    friend class StateGameEditor;

public:
    WorldEditor(StateGameEditor *stateGameEditor);

    ~WorldEditor() = default;

    void showFileDialog(std::function<void(tgui::String)> callback, const std::string &text,
                        const std::string &location, const bool &fileMustExists = false,
                        const bool &multiSelect = false);

    void createTileWindow();

    void createTileList();

    void createWindow(const std::string &type);

    void changeTile() const;

    void draw();

    void setLayer(const int &layer);

    void setMouseTileId(unsigned short mouseTileId);

    void hideTileList();

    void hideTileWindow();

    void showExitMenu();

private:

    StateGameEditor *stateGameEditor;
    unsigned short mouseTileId;
    sf::RectangleShape mouseTileBorder;
    int layer;
    tgui::Group::Ptr gui;

};


#endif //SADZA_WORLDEDITOR_HPP
