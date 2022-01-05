#include <SFML/System/Sleep.hpp>
#include "ClientStub.hpp"

int main()
{
    sf::sleep(sf::seconds(1.0f)); // Wait for server to run

    ClientStub client1;
    ClientStub client2;
    ClientStub client3;

    client1.sendAuthenticate("qwe", "qwe");
    client2.sendAuthenticate("asd", "qwe");
    client3.sendAuthenticate("zxc", "zxc");
    WAIT_FOR_SERVER;
    client1.receiveAuthenticate(MessageResult::Ok);
    client2.receiveAuthenticate(MessageResult::Ok);
    client3.receiveAuthenticate(MessageResult::InvalidUsernameOrPassword);

    return 0;
}

