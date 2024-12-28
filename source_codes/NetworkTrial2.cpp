//g++ -I../src/Include -L../src/Lib -o ../Executables/ NetworkTrial.exe NetworkTrial.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
//
void sendData(const char* message, const char* ipAddress, int port) {
    // Initialize SDL_net
    if (SDL_Init(0) == -1 || SDLNet_Init() == -1) {
        std::cerr << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Open a UDP socket
    UDPsocket socket = SDLNet_UDP_Open(0); // 0 lets SDL choose the port
    if (!socket) {
        std::cerr << "SDLNet_UDP_Open failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Set up the destination address (receiver's address and port)
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, ipAddress, port) == -1) {
        std::cerr << "SDLNet_ResolveHost failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Create a packet to send
    UDPpacket* packet = SDLNet_AllocPacket(512);  // 512 bytes max
    if (!packet) {
        std::cerr << "SDLNet_AllocPacket failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Copy the message into the packet
    std::strncpy(reinterpret_cast<char*>(packet->data), message, 512);
    packet->len = std::strlen(message) + 1;

    // Send the packet
    if (SDLNet_UDP_Send(socket, -1, packet) == 0) {
        std::cerr << "SDLNet_UDP_Send failed: " << SDLNet_GetError() << std::endl;
    } else {
        std::cout << "Message sent: " << message << std::endl;
    }

    // Clean up
    SDLNet_FreePacket(packet);
    SDLNet_UDP_Close(socket);
    SDLNet_Quit();
    SDL_Quit();
}
void receiveData(int port) {
    // Initialize SDL_net
    if (SDL_Init(0) == -1 || SDLNet_Init() == -1) {
        std::cerr << "SDLNet_Init failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Open a UDP socket on the specified port
    UDPsocket socket = SDLNet_UDP_Open(port);
    if (!socket) {
        std::cerr << "SDLNet_UDP_Open failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Create a packet to receive
    UDPpacket* packet = SDLNet_AllocPacket(512);  // 512 bytes max
    if (!packet) {
        std::cerr << "SDLNet_AllocPacket failed: " << SDLNet_GetError() << std::endl;
        return;
    }

    // Wait for and receive a packet
    while (true) {
        if (SDLNet_UDP_Recv(socket, packet)) {
            system("cls");
            std::cout << "Received message: " << reinterpret_cast<char*>(packet->data) << std::endl;
            return;
        } else {
            std::cerr << "No packet received: " << SDLNet_GetError() << std::endl;
        }
    }

    // Clean up
    SDLNet_FreePacket(packet);
    SDLNet_UDP_Close(socket);
    SDLNet_Quit();
    SDL_Quit();
}
//
int main(int argn, char** args)
{
    receiveData(12345);
}