#include "Base/SharedContext.hpp"

Variables *SharedContext::variables = new Variables();
TextureManager *SharedContext::textureManager = new TextureManager();
AudioManager *SharedContext::audioManager = new AudioManager();
tgui::Gui *SharedContext::gui = new tgui::Gui();
Window *SharedContext::window = new Window();
StateManager *SharedContext::stateManager = new StateManager();
Client *SharedContext::client = new Client();