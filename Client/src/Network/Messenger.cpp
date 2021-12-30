#include <State/base/StateManager.hpp>
#include <Base/SharedContext.hpp>
#include "Network/Messenger.hpp"

using namespace Msg;
std::string Messenger::mapFile;

void Messenger::handleMessage(Client *client, MessageId id, sf::Packet &packet)
{
    SysLog::Print(SysLog::Severity::Info, "Received message: 0x%x", id);
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

            std::cout << msg.mapFile;
            mapFile = msg.mapFile;

            std::fstream file;
            file.open("Data/maps/" + msg.mapFile + ".map", std::ios::out);
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
        case StartLobbyGame::id:
        {
            StartLobbyGame msg;
            packet >> msg;
            SysLog::Print(SysLog::Severity::Info, "Received StartLobbyGame");
            SysLog::Print(SysLog::Severity::Info, "mapfile [%s] \n", mapFile.c_str());
            SysLog::Print(SysLog::Severity::Info, "playerId [%d] \n", msg.playerId);

            SharedContext::getWorld()->loadWorld(mapFile);
            SharedContext::getStateManager()->switchTo(StateType::Game);
            sf::sleep(sf::seconds(0.20f));
            StateGame *state = static_cast<StateGame*>(SharedContext::getStateManager()->getCurrentState());
            state->setPlayerId(msg.playerId);
            break;
        }
        case UpdateUnitInd::id:
        {
            UpdateUnitInd ind;
            packet >> ind;
            SysLog::Print(SysLog::Severity::Info, "Received UpdateUnitInd: unitId %u", ind.unitId);

            EntityManger * em = SharedContext::getEntityManager();
            if (ind.destroy)
            {
                em->removeEntity(ind.unitId);
                break;
            }
            auto optEnt = em->getEntity(ind.unitId);
            if (!optEnt.has_value()) {

                ClientEntity entity;
                entity.init(ind.unitId, ind.direction, ind.position, static_cast<EntityType>(ind.type));
                em->addEntity(entity);
            }
            else {
                std::shared_ptr<ClientEntity> ent = optEnt.value();
                ent->position = ind.position;
                ent->direction = ind.direction;
            }

            break;
        }
        case MoveInd::id:
        {
            MoveInd ind;
            packet >> ind;
            SysLog::Print(SysLog::Severity::Info, "Received MoveInd: unitId %u, moving: %d, dir: %u", ind.unitId, ind.start, ind.direction);

            EntityManger *em = SharedContext::getEntityManager();
            auto optEnt = em->getEntity(ind.unitId);
            if (optEnt.has_value()) {
                if (static_cast<Direction>(ind.direction) != Direction::None)
                    optEnt.value()->direction = static_cast<Direction>(ind.direction);

                optEnt.value()->moving = ind.start;
                if (ind.start)
                    optEnt.value()->move(Direction(ind.direction));
                else
                    optEnt.value()->stop();
            }

            break;
        }
        case MsgType::DestroyInd:
        {
            DestroyInd ind;
            packet >> ind;
            SysLog::Print(SysLog::Severity::Info, "Received DestroyInd entity: %d", ind.entityId);

            EntityManger * em = SharedContext::getEntityManager();
            auto optEnt = em->getEntity(ind.entityId);
            if (optEnt.has_value()) {
                em->removeEntity(ind.entityId);
            }
            break;
        }
        case DestroyTileInd::id:
        {
            DestroyTileInd ind;
            packet >> ind;
            SysLog::Print(SysLog::Severity::Info, "Received DestroyTileInd: [%d, %d]", ind.position.x, ind.position.y);

            World *world = SharedContext::getWorld();
            world->destroyTile(ind.position);

            break;
        }
        case EndGameInd::id:
        {
            EndGameInd ind;
            packet >> ind;
            SysLog::Print(SysLog::Severity::Info, "Received EndGameInd: victory %u", ind.victory);

            auto endButton = SharedContext::getGui()->get<tgui::Button>("endButton");
            if (endButton) {
                endButton->setVisible(true);

                if (ind.victory) { endButton->setText("Victory!"); }
                else { endButton->setText("Defeat!"); }
            }
            sf::sleep(sf::seconds(1.0f));
            StateMain *state = (StateMain*)(SharedContext::getStateManager()->getCurrentState());
            SharedContext::getStateManager()->setLogged(true);

            break;
        }
        default:
        {
            break;
        }
    }
}