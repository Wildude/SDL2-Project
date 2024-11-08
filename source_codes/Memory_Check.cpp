//g++ -I../src/Include -L../src/Lib -o ../Executables/Memory_Check.exe Memory_Check.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    cout << " size_of(Vector2<int>): " << sizeof(Vint2) << endl;
    cout << " size_of(Vector2<float>): " << sizeof(Vflt2) << endl;
    cout << " size_of(Vector2<double>): " << sizeof(Vdb2) << endl;

    cout << " size_of(WINDOW): " << sizeof(WINDOW) << endl;
    cout << " size_of(RENDERER): " << sizeof(RENDERER) << endl;
    cout << " size_of(TEXTURE): " << sizeof(TEXTURE) << endl;
    cout << " size_of(FONT): " << sizeof(FONT) << endl;
    cout << " size_of(TXT): " << sizeof(TXT) << endl;
    cout << " size_of(AUDIO): " << sizeof(AUDIO) << endl;
}