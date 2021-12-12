#ifndef SADZA_STATEGAMEEDITOR_HPP
#define SADZA_STATEGAMEEDITOR_HPP

#include "base/State.hpp"
#include <functional>
#include <WorldEditor/WorldEditor.hpp>

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
    WorldEditor worldEditor;
};

#endif //SADZA_STATEGAMEEDITOR_HPP
