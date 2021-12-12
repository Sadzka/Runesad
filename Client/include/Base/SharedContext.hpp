#pragma once

#ifndef SADZA_SHAREDCONTEXT_HPP
#define SADZA_SHAREDCONTEXT_HPP

#include <string>
#include <memory>

#include <TGUI/TGUI.hpp>
#include "Base/Variables.hpp"
#include "Audio/AudioManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Base/Window.hpp"
#include "State/base/StateManager.hpp"
#include "Network/Client.hpp"
#include "World/World.hpp"

class SharedContext {
public:

    SharedContext() = delete;

    SharedContext(SharedContext &) = delete;

    void operator=(const SharedContext &) = delete;

    static Variables *getVariables() { return variables; }

    static TextureManager *getTextureManager() { return textureManager; }

    static AudioManager *getAudioManager() { return audioManager; }

    static tgui::Gui *getGui() { return gui; }

    static Window *getWindow() { return window; }

    static StateManager *getStateManager() { return stateManager; }

    static Client *getClient() { return client; }

    static World *getWorld() { return world; }

private:
    static Variables *variables;
    static TextureManager *textureManager;
    static AudioManager *audioManager;
    static tgui::Gui *gui;
    static Window *window;
    static StateManager *stateManager;
    static Client *client;
    static World *world;
};

#endif //SADZA_SHAREDCONTEXT_HPP
