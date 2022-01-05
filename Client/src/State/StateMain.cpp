#include <State/StateMain.hpp>
#include "Base/SharedContext.hpp"

StateMain::StateMain() : State("Main"), eTime(0) {

}

StateMain::~StateMain() = default;

void StateMain::onCreate() {

}

void StateMain::onDestroy() {

}

void StateMain::activate() {
    tgui::Theme::setDefault("Data/UI/black.txt");

    auto backgroundImage1 = tgui::Picture::create("Data/UI/background1.png");
    backgroundImage1->setSize({"100%", "100%"});
    backgroundImage1->moveToBack();
    SharedContext::getGui()->add(backgroundImage1, "backgroundImage1");

    auto backgroundImage2 = tgui::Picture::create("Data/UI/background2.png");
    backgroundImage2->setSize({"100%", "100%"});
    backgroundImage2->setPosition({"0%", "100%"});
    backgroundImage2->moveToBack();
    SharedContext::getGui()->add(backgroundImage2, "backgroundImage2");

    auto backgroundImage3 = tgui::Picture::create("Data/UI/background3.png");
    backgroundImage3->setSize({"100%", "100%"});
    backgroundImage3->setPosition({"100%", "100%"});
    backgroundImage3->moveToBack();
    SharedContext::getGui()->add(backgroundImage3, "backgroundImage3");

    auto buttonWE = tgui::Button::create("World Edit");
    buttonWE->setSize({"200", "36"});
    buttonWE->setPosition({"50% - 100", "70"});
    SharedContext::getGui()->add(buttonWE);

    auto editBoxUsername = tgui::EditBox::create();
    editBoxUsername->setSize({"200", "36"});
    editBoxUsername->setPosition({"50% - 100", "50% - 63"});
    editBoxUsername->setDefaultText("Username");
    SharedContext::getGui()->add(editBoxUsername, "editBoxUsername");

    auto editBoxPassword = tgui::EditBox::create();
    editBoxPassword->setSize({"200", "36"});
    editBoxPassword->setPosition({"50% - 100", "50% - 21"});
    editBoxPassword->setPasswordCharacter('*');
    editBoxPassword->setDefaultText("Password");
    SharedContext::getGui()->add(editBoxPassword, "editBoxPassword");

    auto loginButton = tgui::Button::create("Login");
    loginButton->setSize({"200", "36"});
    loginButton->setPosition({"50% - 100", "50% + 21"});
    SharedContext::getGui()->add(loginButton, "loginButton");

    auto cancelAuthButton = tgui::Button::create("Cancel");
    cancelAuthButton->setSize({"200", "36"});
    cancelAuthButton->setPosition({"50% - 100", "50% + 110"});
    cancelAuthButton->setVisible(false);
    SharedContext::getGui()->add(cancelAuthButton, "cancelAuthButton");

    auto loginLabel = tgui::Label::create("");
    loginLabel->setSize(360, 40);
    loginLabel->setPosition({"50% - 180", "50% + 65"});
    loginLabel->getRenderer()->setBackgroundColor(tgui::Color::White);
    loginLabel->getRenderer()->setTextColor(tgui::Color::Black);
    // loginLabel->setTextSize(0);
    loginLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    loginLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
    loginLabel->setVisible(false);
    SharedContext::getGui()->add(loginLabel, "loginLabel");

    auto logoutButton = tgui::Button::create();
    logoutButton->setSize({"200", "36"});
    logoutButton->setPosition({"100% + 5", "100% - 41"});
    logoutButton->setText("Logout");
    SharedContext::getGui()->add(logoutButton);

    auto gameListComboList = tgui::ListView::create();
    gameListComboList->addColumn("Game Name", 325, tgui::ListView::ColumnAlignment::Left);
    gameListComboList->addColumn("Players", 75, tgui::ListView::ColumnAlignment::Center);
    gameListComboList->setSize({404, SharedContext::getWindow()->getWindowSize().y - 75});
    gameListComboList->setPosition({"150% - 202", "25"});
    SharedContext::getGui()->add(gameListComboList, "gameListComboList");

    auto createGameButton = tgui::Button::create("Create Game");
    createGameButton->setSize({"200", "36"});
    createGameButton->setPosition({"200% - 205", "100% - 41"});
    SharedContext::getGui()->add(createGameButton);

    auto joinGameButton = tgui::Button::create("Join Game");
    joinGameButton->setSize({"200", "36"});
    joinGameButton->setPosition({"150% - 200", "100% - 41"});
    SharedContext::getGui()->add(joinGameButton);

    auto refreshGameButton = tgui::Button::create("Refresh");
    refreshGameButton->setSize({"200", "36"});
    refreshGameButton->setPosition({"150%", "100% - 41"});
    SharedContext::getGui()->add(refreshGameButton);

    auto exitGameButton = tgui::Button::create("Exit Game");
    exitGameButton->setSize({"200", "36"});
    exitGameButton->setPosition({"100% - 225", "100% - 55"});
    SharedContext::getGui()->add(exitGameButton);

    // Creating Game
    auto gameNameEditBox = tgui::EditBox::create();
    gameNameEditBox->setSize({"200", "36"});
    gameNameEditBox->setPosition({"100% + 5", "200% - 41"});
    gameNameEditBox->setDefaultText("New Game Name");
    SharedContext::getGui()->add(gameNameEditBox, "gameNameEditBox");

    auto gameApplyButton = tgui::Button::create();
    gameApplyButton->setSize({"200", "36"});
    gameApplyButton->setPosition({"100% + 210", "200% - 41"});
    gameApplyButton->setText("Create");
    SharedContext::getGui()->add(gameApplyButton, "applyButton");

    auto selectMapButton = tgui::Button::create();
    selectMapButton->setSize({"200", "36"});
    selectMapButton->setPosition({"100% + 5", "200% - 82"});
    selectMapButton->setText("Select Map");
    SharedContext::getGui()->add(selectMapButton, "selectMapButton");

    auto gameCancelButton = tgui::Button::create();
    gameCancelButton->setSize({"200", "36"});
    gameCancelButton->setPosition({"200% - 410", "200% - 41"});
    gameCancelButton->setText("Cancel");
    SharedContext::getGui()->add(gameCancelButton);

    auto gameStartButton = tgui::Button::create();
    gameStartButton->setSize({"200", "36"});
    gameStartButton->setPosition({"200% - 205", "200% - 41"});
    gameStartButton->setText("Start");
    gameStartButton->setEnabled(false);
    SharedContext::getGui()->add(gameStartButton, "startButton");

    auto gamePlayerList = tgui::ListView::create();
    gamePlayerList->setEnabled(false);
    gamePlayerList->setPosition({"150% - 100", "150% - 190"});
    gamePlayerList->setSize({"200", "342"});
    gamePlayerList->setItemHeight(36);
    gamePlayerList->addColumn("No", 36);
    gamePlayerList->addColumn("", 36);
    gamePlayerList->addColumn("Username", 128);
    gamePlayerList->setShowHorizontalGridLines(true);
    gamePlayerList->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gamePlayerList->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    for (int i = 1; i <= 8; ++i) {
        gamePlayerList->addItem({std::to_string(i), "", "Closed 2"});
    }
    SharedContext::getGui()->add(gamePlayerList, "playerList");

    auto mapNameLabel = tgui::Label::create("");
    mapNameLabel->setSize({"200", "36"});
    mapNameLabel->setPosition({"100% + 5", "200% - 123"});
    SharedContext::getGui()->add(mapNameLabel, "mapNameLabel");

    tgui::Button::Ptr gameUserControlButton[8];
    for (int i = 0; i < 8; ++i) {
        tgui::String posY = std::to_string(i * 37);
        gameUserControlButton[i] = tgui::Button::create("o/c");
        gameUserControlButton[i]->setSize({36, 36});
        gameUserControlButton[i]->setPosition({"150% - 62", "150% - 144 + " + posY});
        SharedContext::getGui()->add(gameUserControlButton[i], "gameUserControlButton" + std::to_string(i));

        gameUserControlButton[i]->onPress([=]() {
            Client *client = SharedContext::getClient();
            client->sendCloseLobbySlot(i);
        });
    }

    loginButton->onPress([=]() {
        if (editBoxUsername->getText().length() < 3 || editBoxPassword->getText().length() < 3) return;

        Client *client = SharedContext::getClient();

        if (!client->isConnected())
            client->connect();

        editBoxUsername->setEnabled(false);
        editBoxPassword->setEnabled(false);
        loginButton->setEnabled(false);
        cancelAuthButton->setVisible(true);
        loginLabel->setVisible(true);

        if (client->isConnected()) {
            connectionStatus.endTime = eTime + 5;
            connectionStatus.inProgress = true;

            SharedContext::getClient()->sendAuthenticate(editBoxUsername->getText().toStdString(),
                                                         editBoxPassword->getText().toStdString());
            loginLabel->setText("Authenticating...");
            cancelAuthButton->setText("Cancel");
        } else {
            loginLabel->setText("Cannot connect to server");
            cancelAuthButton->setText("OK");
        }
    });

    selectMapButton->onPress([this]() {
        showFileDialog();
    });

    logoutButton->onPress([=]() {
        Client *client = SharedContext::getClient();
        client->sendLogout();
        client->disconnect();
        screenAnimation.startAnimation(ScreenAnimation::Direction::Right, sf::seconds(2));
    });

    exitGameButton->onPress([=]() {
        SharedContext::getWindow()->close();
    });

    joinGameButton->onPress([=]() {
        int index = gameListComboList->getSelectedItemIndex();
        if (index != -1)
        {
            Client *client = SharedContext::getClient();
            std::string gameName = gameListComboList->getItem(index).toStdString();
            client->sendJoinLobby(gameName);
        }
    });

    refreshGameButton->onPress([=]() {
        Client *client = SharedContext::getClient();
        client->sendGetLobbyList();
    });

    createGameButton->onPress([=]() {
        screenAnimation.startAnimation(ScreenAnimation::Direction::Up, sf::seconds(1));
        gameStartButton->setEnabled(false);
        gameApplyButton->setEnabled(false);
        gamePlayerList->setEnabled(true);
        selectMapButton->setEnabled(true);
        gamePlayerList->setVisible(false);
        gameUserControlButton[0]->setEnabled(false);
        gameUserControlButton[0]->setVisible(false);
        for (int i = 1; i < 8; ++i) {
            gameUserControlButton[i]->setVisible(false);
            gameUserControlButton[i]->setEnabled(true);
        }
    });

    gameApplyButton->onPress([=]() {

        Client *client = SharedContext::getClient();

        std::string gameName = gameNameEditBox->getText().toStdString();
        if (gameName == "") return;

        client->sendCreateLobby(gameName);

        gameNameEditBox->setEnabled(false);
        gameApplyButton->setEnabled(false);
        gameApplyButton->setEnabled(false);
        selectMapButton->setEnabled(false);
        gameStartButton->setEnabled(true);
        for (auto &button : gameUserControlButton) {
            button->setVisible(true);
        }

        gamePlayerList->setVisible(true);
    });

    gameStartButton->onPress([=]() {
        Client *client = SharedContext::getClient();

        client->sendStartLobbyGame();
    });

    gameCancelButton->onPress([=]() {

        Client *client = SharedContext::getClient();

        client->sendLeaveLobby();
    });

    cancelAuthButton->onPress([=]() {
        connectionStatus.inProgress = false;
        editBoxUsername->setEnabled(true);
        editBoxPassword->setEnabled(true);
        loginButton->setEnabled(true);
        cancelAuthButton->setVisible(false);
        loginLabel->setVisible(false);
        cancelAuthenticateInProgress();
    });

    buttonWE->onMousePress([=](){
        SharedContext::getStateManager()->switchTo(StateType::GameEditor);
    });
}

void StateMain::deactivate() {
    SharedContext::getGui()->removeAllWidgets();
    tgui::Gui *gui = SharedContext::getGui();
}

void StateMain::update(const float &dTime) {
    eTime += dTime;
    screenAnimation.update(sf::seconds(dTime));
    if (eTime > connectionStatus.endTime) {
        cancelAuthenticateInProgress();
    }
}

void StateMain::draw() {

}

void StateMain::lateDraw() {

}

void StateMain::cancelAuthenticateInProgress(MessageResult result) {
    tgui::EditBox::Ptr editBoxUsername = SharedContext::getGui()->get<tgui::EditBox>("editBoxUsername");
    tgui::EditBox::Ptr editBoxPassword = SharedContext::getGui()->get<tgui::EditBox>("editBoxPassword");
    tgui::Button::Ptr loginButton = SharedContext::getGui()->get<tgui::Button>("loginButton");
    tgui::Button::Ptr cancelAuthButton = SharedContext::getGui()->get<tgui::Button>("cancelAuthButton");
    tgui::Label::Ptr loginLabel = SharedContext::getGui()->get<tgui::Label>("loginLabel");

    cancelAuthButton->setText("OK");
    switch (result)
    {
        case MessageResult::Ok:
        {
            screenAnimation.startAnimation(ScreenAnimation::Direction::Left, sf::seconds(1));
            cancelAuthButton->setVisible(false);
            loginLabel->setVisible(false);

            editBoxUsername->setEnabled(true);
            editBoxPassword->setEnabled(true);
            loginButton->setEnabled(true);

            editBoxUsername->setText("");
            editBoxPassword->setText("");

            break;
        }
        case MessageResult::InvalidPassword:
        case MessageResult::InvalidUsername:
        case MessageResult::InvalidUsernameOrPassword:
        {
            loginLabel->setText("Invalid username or password");
            break;
        }
        case MessageResult::AlreadyLogged:
        {
            loginLabel->setText("You are already logged");
            break;
        }
        default:
        {
            loginLabel->setText("Can't connect to server");
            break;
        }
    }

    connectionStatus.inProgress = false;
}

void StateMain::showFileDialog() {
    auto fileDialog = tgui::FileDialog::create("Select Map");
    fileDialog->setFileMustExist(true);
    fileDialog->setPosition(SharedContext::getGui()->get<tgui::ListView>("playerList")->getPosition());
    fileDialog->setVisible(true);
    fileDialog->setPath(tgui::Filesystem::getCurrentWorkingDirectory().asString() + "/Data/maps/");
    fileDialog->setFileTypeFilters({{"Map file", {"*.map"}}});
    SharedContext::getGui()->add(fileDialog, "fileDialog");


    auto x = SharedContext::getGui()->get<tgui::FileDialog>("fileDialog");
    std::cout << x << std::endl;

    fileDialog->onFileSelect([=](const std::vector<tgui::Filesystem::Path> &selectedFiles) {
        for (const tgui::Filesystem::Path &path : selectedFiles) {

            SharedContext::getGui()->get<tgui::Label>("mapNameLabel")->setText(path.getFilename().toStdString());
            SharedContext::getGui()->get<tgui::Button>("applyButton")->setEnabled(true);
        }
    });
}

void StateMain::skipLogin() {
    screenAnimation.startAnimation(ScreenAnimation::Direction::Left, sf::seconds(0.1f));
    // clear
    SharedContext::getEntityManager()->clearAll();
    SharedContext::getWorld()->closeWorld();
}
