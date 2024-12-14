//g++ -I../src/Include -L../src/Lib -o ../Executables/NetworkTrial.exe NetworkTrial.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    try {
        NetworkManager netManager;

        // Example: Connect to a host
        if (netManager.connectToHost("192.168.1.2", 1234)) {
            std::cout << "Connected to the host!" << std::endl;
        }

        // Example: Wait for a client
        if (netManager.waitForConnection(1234)) {
            std::cout << "Client connected!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}