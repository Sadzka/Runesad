#include <State/base/StateManager.hpp>
#include <Base/SharedContext.hpp>
#include "Network/Messenger.hpp"

using namespace Msg;

void Messenger::handleMessage(Client *client, MessageId id, sf::Packet &packet)
{
    SysLog::Print(SysLog::Severity::Info, "Received message: %u", id);
    switch (id) {
        case AuthenticateResp::id: {
            auto msg = Creator<AuthenticateResp::id>::Create(packet);
            SysLog::Print(SysLog::Severity::Info, "Received AuthenticateResp result: %u", msg.result);

            StateManager *sm = SharedContext::getStateManager();

            if (sm->getCurrentStateType() == StateType::Main)
            {
                auto *sMain = (StateMain*)(sm->getCurrentState());
                sMain->cancelAuthenticateInProgress(msg.result);
                client->sendGetLobbyList();
            }
            break;
        }
        case GetLobbyListResp::id:
        {
            auto msg = Creator<GetLobbyListResp::id>::Create(packet);
            SysLog::Print(SysLog::Severity::Info, "Received GetLobbyListResp");

            tgui::Gui *gui = SharedContext::getGui();

            auto listView = gui->get<tgui::ListView>("gameListComboList");
            for (auto &lobbie : msg.lobbies) {
                listView->addItem(lobbie);
            }
            break;
        }
        case JoinLobbyResp::id:
        {
            auto msg = Creator<JoinLobbyResp::id>::Create(packet);
            SysLog::Print(SysLog::Severity::Info, "Received JoinLobbyResp result: %u", msg.result);

            if (msg.result != MessageResult::Ok) break;

            auto *state = dynamic_cast<StateMain*>(SharedContext::getStateManager()->getCurrentState());
            auto *gui = SharedContext::getGui();

            state->screenAnimation.startAnimation(ScreenAnimation::Direction::Up, sf::seconds(2));
            gui->get<tgui::Button>("startButton")->setEnabled(false);
            gui->get<tgui::Button>("applyButton")->setEnabled(false);
            gui->get<tgui::ListView>("playerList")->setEnabled(false);
            for (int i = 0; i < 8; ++i) {
                auto btn = gui->get<tgui::Button>("gameUserControlButton" + std::to_string(i));
                btn->setEnabled(false);
                btn->setVisible(true);
            }

            std::fstream file;
            file.open("Data/maps/" + msg.mapName + ".map");
            if (!file.good()) throw std::runtime_error("Failed open file!");
            file << msg.mapFile;
            file.close();

            SharedContext::getGui()->get<tgui::Label>("mapNameLabel")->setText(msg.mapName);

            break;
        }
        case UpdateLobbyStatus::id:
        {
            auto msg = Creator<UpdateLobbyStatus::id>::Create(packet);
            SysLog::Print(SysLog::Severity::Info, "Received UpdateLobbyStatus");

            auto *gui = SharedContext::getGui();

            for (int i = 0; i < 8; ++i) {
                std::string slotStatus = msg.open[i] ? "Open" : "Closed";
                SysLog::Print(SysLog::Severity::Info, "\t [%s] [%s]", slotStatus.c_str(), msg.playerName[i].c_str());

                auto list = gui->get<tgui::ListView>("playerList");
                list->changeSubItem(i, 2, slotStatus);
                if (slotStatus == "Closed" && msg.playerName[i] != "")
                    list->changeSubItem(i, 2, msg.playerName[i]);

            }
            break;
        }
        case LeaveLobbyResp::id:
        {
            SysLog::Print(SysLog::Severity::Info, "Received LeaveLobbyResp");

            auto *state = dynamic_cast<StateMain*>(SharedContext::getStateManager()->getCurrentState());
            auto *gui = SharedContext::getGui();

            state->screenAnimation.startAnimation(ScreenAnimation::Direction::Down, sf::seconds(2));
            gui->get<tgui::Button>("startButton")->setEnabled(false);
            gui->get<tgui::EditBox>("gameNameEditBox")->setText("");
            gui->get<tgui::EditBox>("gameNameEditBox")->setEnabled(true);
            gui->get<tgui::Button>("applyButton")->setEnabled(true);
        }
        default:
        {
            break;
        }
    }
}