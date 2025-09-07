#pragma once
#include <SDL2/SDL_net.h>
#include <fstream>
//std::ofstream network_file("net.log");
class NetworkManager {
public:
    NetworkManager();

    ~NetworkManager();

    bool connectToHost(const std::string& host, Uint16 port);

    bool waitForConnection(Uint16 port);

    std::string getIP(TCPsocket sock);

    bool createUDP(Uint16 port);

    bool bindUDP(const std::string& host, Uint16 port);

    bool sendUDP(const void* data, int len);
    
    int receiveUDP(void* buffer, int maxlen);

private:
    TCPsocket socket;
    TCPsocket serverSocket;
    UDPsocket udpSocket;
    IPaddress udpIP;
};