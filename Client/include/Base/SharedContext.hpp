//
// Created by Sadza on 13.06.2021.
//

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

private:
    static Variables *variables;
    static TextureManager *textureManager;
    static AudioManager *audioManager;
    static tgui::Gui *gui;
    static Window *window;
    static StateManager *stateManager;
    static Client *client;
};

#endif //SADZA_SHAREDCONTEXT_HPP
