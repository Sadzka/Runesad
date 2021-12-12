#include <iostream>
#include "Base/Game.hpp"
#include <Sys/SysLog.hpp>

int main() {

    SysLog logger;
    try {
        Game game;

        while (!game.getWindow()->isClosed()) {
            game.update();
            game.render();
            game.lateUpdate();
        }
    }
    catch (const tgui::Exception &e) {
        std::cout << "[tgui Exception] " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
