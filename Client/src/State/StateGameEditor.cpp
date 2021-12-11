/*
#include "State/StateGameEditor.hpp"
#include "SharedContext.hpp"

StateGameEditor::StateGameEditor() : State("GameEditor"), eTime(0), worldEditor(this) {
    resetView();
}

StateGameEditor::~StateGameEditor() {
    SharedContext::getWindow()->getRenderWindow()->setTitle("Arikazike");
    //SharedContext::getWorld()->clearTilesets();
}

void StateGameEditor::onCreate() {

}

void StateGameEditor::onDestroy() {

}

void StateGameEditor::activate() {
    currentPath = "";
    SharedContext::getWindow()->getRenderWindow()->setTitle("Arikazike");
    SharedContext::getAudioManager()->stopAllSounds();
    SharedContext::getAudioManager()->stopMusic();

    auto menuBar = tgui::MenuBar::create();
    menuBar->addMenu("File");
    menuBar->addMenuItem("File", "Open");
    menuBar->addMenuItem("File", "New");
    menuBar->addMenuItem("File", "Save");
    menuBar->addMenuItem("File", "Save As");
    menuBar->addMenuItem("File", "Close");
    menuBar->addMenu("Tileset");
    menuBar->addMenuItem("Tileset", "Add");
    menuBar->addMenuItem("Tileset", "Remove");
    menuBar->addMenuItem("Tileset", "Show");
    menuBar->addMenu("World");
    menuBar->addMenuItem("World", "Resize");
    menuBar->addMenuItem("World", "Go To");
    gui->add(menuBar, "MenuBar");

    setMenuButtonsEnabled(false);

    menuBar->connectMenuItem("File", "Open", [this]() {
        this->clickMenuItem("File Open");
    });
    menuBar->connectMenuItem("File", "New", [this]() {
        this->clickMenuItem("File New");
    });
    menuBar->connectMenuItem("File", "Save", [this]() {
        this->clickMenuItem("File Save");
    });
    menuBar->connectMenuItem("File", "Save As", [this]() {
        this->clickMenuItem("File Save As");
    });
    menuBar->connectMenuItem("File", "Close", [this]() {
        this->clickMenuItem("File Close");
    });
    menuBar->connectMenuItem("Tileset", "Add", [this]() {
        worldEditor.showFileDialog(std::bind(&StateGameEditor::openTileset, this, std::placeholders::_1), "Open",
                                   "/data/img/tilesets/", true);
    });
    menuBar->connectMenuItem("Tileset", "Remove", [this]() {
        auto tileList = gui->get<tgui::Panel>("tileList");
        if (tileList) {
            gui->remove(tileList);
        } else {
            worldEditor.createTileList();
        }
    });
    menuBar->connectMenuItem("Tileset", "Show", [this]() {
        auto tilewindow = gui->get<tgui::ScrollablePanel>("Tilewindow");
        if (tilewindow) {
            gui->remove(tilewindow);
        } else {
            worldEditor.createTileWindow();
        }
    });
    menuBar->connectMenuItem("World", "Resize", [this]() {
        auto resizePanel = gui->get<tgui::Panel>("Panel");
        if (resizePanel) {
            gui->remove(resizePanel);
        } else {
            worldEditor.createWindow("Resize");
        }
    });
    menuBar->connectMenuItem("World", "Go To", [this]() {
        auto gotoPanel = gui->get<tgui::Panel>("Panel");
        if (gotoPanel) {
            gui->remove(gotoPanel);
        } else {
            worldEditor.createWindow("Go To");
        }
    });
}

void StateGameEditor::deactivate() {
    gui->removeAllWidgets();
    SharedContext::getWorld()->closeWorld();
}

void StateGameEditor::update(const float &dTime) {
    eTime += dTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { view.move(0, 256 * dTime); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { view.move(0, -256 * dTime); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { view.move(-256 * dTime, 0); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { view.move(256 * dTime, 0); }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { worldEditor.changeTile(); }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) { worldEditor.setLayer(0); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) { worldEditor.setLayer(1); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) { worldEditor.setLayer(2); }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { worldEditor.setMouseTileId(0); }
}

void StateGameEditor::draw() {
    SharedContext::getWorld()->drawHighlightedLayer(worldEditor.layer);
    worldEditor.draw();
}

void StateGameEditor::clickMenuItem(const std::string &option) {
    if (option == "File Open") {
        worldEditor.showFileDialog(
                std::bind(&StateGameEditor::openWorldFile, this, std::placeholders::_1), "Open", "/data/maps/", true);
    } else if (option == "File New") {
        worldEditor.showFileDialog(
                std::bind(&StateGameEditor::saveWorldFile, this, std::placeholders::_1), "Create", "/data/maps/",
                false);
        setMenuButtonsEnabled();
    } else if (option == "File Save") {
        saveWorldFile();
    } else if (option == "File Save As") {
        worldEditor.showFileDialog(
                std::bind(&StateGameEditor::saveWorldFile, this, std::placeholders::_1), "Save", "/data/maps/", false);
    } else if (option == "File Close") {
        worldEditor.showExitMenu();
    } else {
        std::cout << "Unknown option\n";
    }

}

void StateGameEditor::openWorldFile(const tgui::String filename) {
    worldEditor.hideTileList();
    currentPath = filename.toStdString();
    SharedContext::getWorld()->loadWorld(currentPath);

    sf::RenderWindow *window = SharedContext::getWindow()->getRenderWindow();

    setMenuButtonsEnabled();
    SharedContext::getWindow()->getRenderWindow()->setTitle("Arikazike - " + filename.toStdString());
    worldEditor.createTileWindow();
    resetView();
}

void StateGameEditor::saveWorldFile(const tgui::String filename) {
    SharedContext::getWorld()->saveWorld(filename.toStdString());
}

void StateGameEditor::openTileset(const tgui::String tilesetName) {
    SharedContext::getWorld()->addTileset(tilesetName.toStdString());
    auto tilewindow = gui->get<tgui::ScrollablePanel>("Tilewindow");
    if (tilewindow) {
        gui->remove(tilewindow);
    }
    worldEditor.createTileWindow();
}

void StateGameEditor::setMenuButtonsEnabled(const bool &b) {
    auto menuBar = gui->get<tgui::MenuBar>("MenuBar");
    menuBar->setMenuItemEnabled("File", "Save", b);
    menuBar->setMenuItemEnabled("File", "Save As", b);
    menuBar->setMenuEnabled("Tileset", b);
    menuBar->setMenuEnabled("World", b);
}

void StateGameEditor::resetView() {
    view = SharedContext::getWindow()->getRenderWindow()->getDefaultView();
    view.move(0, -20); // Menu offset
}
*/
