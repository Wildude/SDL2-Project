#include "../include/networkManager.hpp"
std::ofstream network_file("net.log");
NetworkManager::NetworkManager() {
    if (SDLNet_Init() < 0) {
        network_file << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
        //throw runtime_error("Failed to initialize SDL_net");
    }
}

NetworkManager::~NetworkManager() {
    SDLNet_Quit();
}

bool NetworkManager::connectToHost(const std::string& host, Uint16 port) {
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, host.c_str(), port) < 0) {
        network_file << "Failed to resolve host: " << SDLNet_GetError() << std::endl;
        return false;
    }
    socket = SDLNet_TCP_Open(&ip);
    if (!socket) {
        network_file << "Failed to open socket: " << SDLNet_GetError() << std::endl;
        return false;
    }
    return true;
}

bool NetworkManager::waitForConnection(Uint16 port) {
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, NULL, port) < 0) {
        network_file << "Failed to resolve host for server: " << SDLNet_GetError() << std::endl;
        return false;
    }
    serverSocket = SDLNet_TCP_Open(&ip);
    if (!serverSocket) {
        network_file << "Failed to open server socket: " << SDLNet_GetError() << std::endl;
        return false;
    }
    network_file << "Waiting for client connection..." << std::endl;
    socket = SDLNet_TCP_Accept(serverSocket);
    if (!socket) {
        network_file << "No client connected." << std::endl;
        return false;
    }
    return true;
}

std::string NetworkManager::getIP(TCPsocket sock) {
    IPaddress* remoteIP = SDLNet_TCP_GetPeerAddress(sock);
    if (!remoteIP) {
        network_file << "Failed to get peer address: " << SDLNet_GetError() << std::endl;
        return "";
    }
    Uint32 ip = SDL_SwapBE32(remoteIP->host);
    return std::to_string((ip >> 24) & 0xFF) + "." +
            std::to_string((ip >> 16) & 0xFF) + "." +
            std::to_string((ip >> 8) & 0xFF) + "." +
            std::to_string(ip & 0xFF);
}

bool NetworkManager::createUDP(Uint16 port) {
    udpSocket = SDLNet_UDP_Open(port);
    if (!udpSocket) {
        network_file << "Failed to open UDP socket: " << SDLNet_GetError() << std::endl;
        return false;
    }
    return true;
}

bool NetworkManager::bindUDP(const std::string& host, Uint16 port) {
    if (SDLNet_ResolveHost(&udpIP, host.c_str(), port) < 0) {
        network_file << "Failed to resolve UDP host: " << SDLNet_GetError() << std::endl;
        return false;
    }
    return true;
}

bool NetworkManager::sendUDP(const void* data, int len) {
    UDPpacket packet;
    packet.data = (Uint8*)data;
    packet.len = len;
    packet.address = udpIP;
    if (SDLNet_UDP_Send(udpSocket, -1, &packet) == 0) {
        network_file << "Failed to send UDP packet: " << SDLNet_GetError() << std::endl;
        return false;
    }
    return true;
}

int NetworkManager::receiveUDP(void* buffer, int maxlen) {
    UDPpacket packet;
    packet.data = (Uint8*)buffer;
    packet.maxlen = maxlen;
    if (SDLNet_UDP_Recv(udpSocket, &packet) == 0) {
        network_file << "No UDP packet received." << std::endl;
        return 0;
    }
    return packet.len;
}
