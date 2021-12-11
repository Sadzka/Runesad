#include "Network/Messages/Base/MsgCreator.hpp"

namespace Msg {
    int GetId(sf::Packet &packet) {
        int ret = 0;
        packet >> ret;
        return ret;
    }
}
