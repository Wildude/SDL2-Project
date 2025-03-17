//g++ -I../src/Include -L../src/Lib -o ../Executables/Memory_Check.exe Memory_Check.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    cout << " size_of(SDL_Window*): " << sizeof(SDL_Window*) << endl;
    cout << " size_of(SDL_Renderer*): " << sizeof(SDL_Renderer*) << endl;
    cout << " size_of(SDL_Texture*): " << sizeof(SDL_Texture*) << endl;
    cout << " size_of(SDL_Surface*): " << sizeof(SDL_Surface*) << endl;
    cout << " size_of(SDL_Rect): " << sizeof(SDL_Rect) << endl;
    cout << " size_of(SDL_FRect): " << sizeof(SDL_FRect) << endl;
    cout << " size_of(SDL_FPoint): " << sizeof(SDL_FPoint) << endl;
    cout << " size_of(SDL_RendererFlip): " << sizeof(SDL_RendererFlip) << endl;

    cout << " size_of(Vector2<int>): " << sizeof(Vint2) << endl;
    cout << " size_of(Vector2<float>): " << sizeof(Vflt2) << endl;
    cout << " size_of(Vector2<double>): " << sizeof(Vdb2) << endl;

    cout << " size_of(WINDOW): " << sizeof(WINDOW) << endl;
    cout << " size_of(RENDERER): " << sizeof(RENDERER) << endl;
    cout << " size_of(TEXTURE): " << sizeof(TEXTURE) << endl;
    cout << " size_of(FONT): " << sizeof(FONT) << endl;
    cout << " size_of(TXT): " << sizeof(TXT) << endl;
    cout << " size_of(AUDIO): " << sizeof(AUDIO) << endl;
    cout << " size_of(physx): " << sizeof(physx) << endl;
    cout << " size_of(physx_body): " << sizeof(physx_body) << endl;
    cout << " size_of(physx_surface): " << sizeof(physx_surface) << endl;
    cout << " size_of(simpledoll): " << sizeof(simpledoll) << endl;
    cout << " size_of(doll): " << sizeof(doll) << endl;
}