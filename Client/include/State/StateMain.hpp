#ifndef SADZA_STATEMAIN_HPP
#define SADZA_STATEMAIN_HPP

#pragma once

#include <State/base/ScreenAnimation.hpp>
#include <Network/Messages/Base/MessageResult.hpp>
#include "State/base/State.hpp"

class StateMain : public State {
    friend class Messenger;
public:
    StateMain();

    ~StateMain();

    virtual void onCreate();

    virtual void onDestroy();

    virtual void activate();

    virtual void deactivate();

    virtual void update(const float &dTime);

    virtual void draw();

    virtual void lateDraw();

    void cancelAuthenticateInProgress(MessageResult result = MessageResult::UnknownStatus);

private:
    std::string mapName;
    struct ConnectionStatus {
        bool inProgress = false;
        float endTime;
    };
    float eTime;    //elapsedTime
    ScreenAnimation screenAnimation;
    ConnectionStatus connectionStatus;

    static void showFileDialog();
};


#endif //SADZA_STATEMAIN_HPP
