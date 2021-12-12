#include <World/Tileset.hpp>
#include "WorldEditor/WorldEditor.hpp"
#include "Base/SharedContext.hpp"
#include "State/base/AllStates.hpp"

WorldEditor::WorldEditor(StateGameEditor *stateGameEditor) : stateGameEditor(stateGameEditor), mouseTileId(0),
                                                             layer(0) {
    mouseTileBorder.setSize(sf::Vector2f(32, 32));
    mouseTileBorder.setOutlineColor(sf::Color::Red);
    mouseTileBorder.setOutlineThickness(2);
    mouseTileBorder.setFillColor(sf::Color::Transparent);
    mouseTileBorder.setPosition(5, 5);

    gui = stateGameEditor->gui;
}

void WorldEditor::showFileDialog(std::function<void(tgui::String)> callback, const std::string &text,
                                 const std::string &location, const bool &fileMustExists, const bool &multiSelect) {
    auto fileDialog = tgui::FileDialog::create(text + " File");
    fileDialog->setConfirmButtonText(text);
    fileDialog->setFileMustExist(fileMustExists);
    fileDialog->setMultiSelect(multiSelect);
    fileDialog->setPath(tgui::Filesystem::getCurrentWorkingDirectory().asString() + location);


    fileDialog->onFileSelect([=](const std::vector<tgui::Filesystem::Path> &selectedFiles) {
        for (tgui::Filesystem::Path path : selectedFiles) {
            std::string stdStr = path.getFilename().toStdString();
            removeExtension(stdStr);
            callback(tgui::String(stdStr));
        }
    });
    gui->add(fileDialog);
}


void WorldEditor::createTileWindow() {

    //paleteWindow = tgui::ChildWindow::create("Tiles");
    std::shared_ptr<tgui::ScrollablePanel> paleteWindow = tgui::ScrollablePanel::create();
    paleteWindow->setSize({"428", "100%"});
    paleteWindow->setEnabled(true);
    paleteWindow->setPosition({"100%-428", "20"});
    gui->add(paleteWindow, "Tilewindow");

    const int padding = 2;
    const int tilesize = 32;
    const int margin = 5;
    const int maxTilesInWidth = (paleteWindow->getSize().x - margin * 2) / (padding + tilesize);
    int yOffset = 0;

    int total = 0;
    auto tilebase = tgui::BitmapButton::create();

    tilebase->setSize({tilesize, tilesize});
    for (Tileset &tileset : SharedContext::getWorld()->getTilesets()) {
        auto tile_label = tgui::Label::create();
        tile_label->setPosition({0, margin + yOffset});
        tile_label->setText("Tileset: " + tileset.getName());
        yOffset += tile_label->getSize().y;
        paleteWindow->add(tile_label);

        int nextTileId = tileset.getOffset();
        for (int i = 0; i < maxTilesInWidth && i < tileset.getSize().x; ++i) {
            for (int j = 0; j < tileset.getSize().y; ++j) {
                auto tile = tgui::BitmapButton::copy(tilebase);
                tile->setPosition(margin + i * (tilesize + padding), margin + j * (tilesize + padding) + yOffset);

                Tile *t = tileset.inRange(nextTileId++);
                if (t == nullptr) {
                    continue;
                }
                sf::IntRect rect = t->getTextureRect();
                tile->setUserData(t->getId());

                tgui::Texture texture = tgui::Texture(
                        *t->getTexture(),
                        tgui::UIntRect(rect.left, rect.top, rect.width, rect.height)
                );

                tile->setImage(texture);

                tile->onMouseEnter([=]() {
                    tile->setImageScaling(1.2);
                    tile->setMouseCursor(tgui::Cursor::Type::Hand);
                });
                tile->onMouseLeave([=]() {
                    tile->setImageScaling(1);
                    tile->setMouseCursor(tgui::Cursor::Type::Arrow);
                });
                tile->onMousePress([=]() {
                    setMouseTileId(tile->getUserData<int>());
                });

                //tile->setImage( *tileset.getTile(1)->getTexture());
                paleteWindow->add(tile);
                total++;
            }
        }
        yOffset += (tileset.getSize().y) * (tilesize + padding);
    }
}

void WorldEditor::createTileList() {
    auto tileList = tgui::ScrollablePanel::create({200, 500});
    tileList->setPosition({"50% - 100", "50% - 250"});
    tileList->getRenderer()->setBackgroundColor(tgui::Color(155, 155, 155));

    sf::Uint32 margin = 5;
    sf::Uint32 yOffset = 5;
    // button_base->setSize();

    for (Tileset &tileset : SharedContext::getWorld()->getTilesets()) {
        auto tile_label = tgui::Label::create();
        tile_label->setTextSize(20);
        tile_label->setPosition({margin, margin + yOffset});
        tile_label->setText("Tileset: " + tileset.getName());

        auto button = tgui::Button::create();
        button->setText("x");
        button->setTextSize(12);
        button->setSize(25, 25);
        button->setPosition(std::string("100% - width - " + std::to_string(margin)).c_str(),
                            yOffset + tile_label->getSize().y / 2 - button->getSize().y / 2);

        tileList->add(tile_label);
        tileList->add(button);
        button->onPress([=]() {
            SharedContext::getWorld()->removeTileset(tileset.getName());
            hideTileList();
            hideTileWindow();
            createTileWindow();
        });

        yOffset += tile_label->getSize().y + 5;
    }

    gui->add(tileList, "tileList");
    //panel->add(panel);
}

void WorldEditor::createWindow(const std::string &type) {

    auto panel = tgui::Panel::create({300, 160});
    panel->setPosition({"50% - 150", "50% - 80"});
    gui->add(panel, "Panel");

    auto editBoxWidth = tgui::EditBox::create();
    editBoxWidth->setSize({"66.67%", "17.5%"});
    editBoxWidth->setPosition({"16.67%", "16.67%"});
    editBoxWidth->setTextSize(20);
    editBoxWidth->setAlignment(tgui::EditBox::Alignment::Center);
    panel->add(editBoxWidth);

    auto editBoxHeight = tgui::EditBox::copy(editBoxWidth);
    editBoxHeight->setPosition({"16.67%", "41.6%"});
    panel->add(editBoxHeight);

    auto button = tgui::Button::create();
    button->setSize({"50%", "16.67%"});
    button->setPosition({"25%", "70%"});
    button->setTextSize(20);
    panel->add(button);

    if (type == "Resize") {
        button->setText("Resize");
        sf::Vector2i size = SharedContext::getWorld()->getSize();
        editBoxWidth->setDefaultText(std::to_string(size.x));
        editBoxHeight->setDefaultText(std::to_string(size.y));
        button->onPress([=]() {
            sf::Vector2i newSize = sf::Vector2i(editBoxWidth->getText().toUInt(), editBoxHeight->getText().toUInt());
            if (newSize != sf::Vector2i(0, 0)) {
                SharedContext::getWorld()->resize(sf::Vector2i(newSize));
            }
            gui->remove(panel);
        });
    } else if (type == "Go To") {
        button->setText("Go To Tile");
        editBoxWidth->setDefaultText("0");
        editBoxHeight->setDefaultText("0");
        button->onPress([=]() {
            stateGameEditor->view.setCenter(sf::Vector2f(editBoxWidth->getText().toFloat() * 32,
                                                         editBoxHeight->getText().toFloat() * 32));
            gui->remove(panel);
        });
    }
}

void WorldEditor::draw() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*SharedContext::getWindow()->getRenderWindow());
    sf::Vector2f worldMousePos = SharedContext::getWindow()->getRenderWindow()->mapPixelToCoords(mousePos);

    sf::FloatRect allowed(0, 0,
                          SharedContext::getWorld()->getSize().x * 32,
                          SharedContext::getWorld()->getSize().y * 32);
    if (!allowed.contains(worldMousePos)) {
        return;
    }

    for (auto &tileset : SharedContext::getWorld()->getTilesets()) {
        Tile *tile = tileset.inRange(mouseTileId);
        if (tile) {
            sf::Vector2i worldTilePos(worldMousePos.x / 32, worldMousePos.y / 32);

            tile = tileset.getTile(mouseTileId);
            tile->draw(worldTilePos.x, worldTilePos.y);

            mouseTileBorder.setPosition(worldTilePos.x * 32, worldTilePos.y * 32);
            SharedContext::getWindow()->getRenderWindow()->draw(mouseTileBorder);
            continue;
        }
    }
}

void WorldEditor::changeTile() const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*SharedContext::getWindow()->getRenderWindow());
    sf::Vector2f worldMousePos = SharedContext::getWindow()->getRenderWindow()->mapPixelToCoords(mousePos);

    sf::FloatRect allowed(0, 0,
                          SharedContext::getWorld()->getSize().x * 32,
                          SharedContext::getWorld()->getSize().y * 32);
    if (!allowed.contains(worldMousePos)) {
        return;
    }
    SharedContext::getWorld()->world[layer][worldMousePos.x / 32][worldMousePos.y / 32] = mouseTileId;
}

void WorldEditor::setLayer(const int &layer) {
    this->layer = layer;
}

void WorldEditor::setMouseTileId(unsigned short mouseTileId) {
    WorldEditor::mouseTileId = mouseTileId;
}

void WorldEditor::hideTileList() {
    auto tileList = gui->get("tileList");
    if (tileList) { gui->remove(tileList); }
}

void WorldEditor::hideTileWindow() {
    auto tileWindow = gui->get<tgui::ScrollablePanel>("Tilewindow");
    if (tileWindow) { gui->remove(tileWindow); }
}

void WorldEditor::showExitMenu() {

    auto panel = tgui::Panel::create({300, 80});
    panel->setPosition({"50% - 150", "50% - 40"});

    auto label = tgui::Label::create("Save changes?");
    label->setTextSize(16);
    label->setPosition({"50% - width / 2", 10});

    auto buttonSave = tgui::Button::create();
    buttonSave->setSize(80, 30);
    buttonSave->setTextSize(12);
    buttonSave->setPosition(5, "100% - height - 5");
    buttonSave->setText("Save");

    auto buttonDontSave = tgui::Button::create();
    buttonDontSave->setSize(80, 30);
    buttonDontSave->setTextSize(12);
    buttonDontSave->setPosition("50% - width / 2", "100% - height - 5");
    buttonDontSave->setText("Don't Save");

    auto buttonCancel = tgui::Button::create();
    buttonCancel->setSize(80, 30);
    buttonCancel->setTextSize(12);
    buttonCancel->setPosition("100% - width - 5", "100% - height - 5");
    buttonCancel->setText("Cancel");

    gui->add(panel, "ExitMenu");
    panel->add(label);
    panel->add(buttonSave);
    panel->add(buttonDontSave);
    panel->add(buttonCancel);

    buttonCancel->onClick([=](){
        gui->remove(panel);
    });
    buttonDontSave->onClick([=](){
        SharedContext::getStateManager()->switchTo(StateType::Main);
    });
    buttonSave->onClick([=](){
        if (stateGameEditor->currentPath != "") {
            SharedContext::getWorld()->saveWorld(stateGameEditor->currentPath);
        }
        SharedContext::getStateManager()->switchTo(StateType::Main);
    });
}
