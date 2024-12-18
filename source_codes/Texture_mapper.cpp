//g++ -I../src/Include -L../src/Lib -o ../Executables/Texture_mapper.exe Texture_mapper.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win("Texture mapper");
    win.crtwin();
    win.crtren(NULL, -1, SDL_RENDERER_SOFTWARE);
    win.pstcol(255, 0, 255, 255);
    // Define the vertices of the trapezium
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 50, 50, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 255);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(win.getren(), surf);
    SDL_FreeSurface(surf);
    if (!texture) {
        cerr << "Error creating texture: " << SDL_GetError() << endl;
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Vertex vertices[4];
    SDL_Event event;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        // Top-left vertex
        vertices[0].position.x = win.getw()/2 - w/2;
        vertices[0].position.y = win.geth()/2 - h/2;
        vertices[0].tex_coord.x = 0.0;
        vertices[0].tex_coord.y = 0.0;
        // Top-right vertex
        vertices[1].position.x = win.getw()/2 + w/2;
        vertices[1].position.y = win.geth()/2 - h/2;
        vertices[1].tex_coord.x = 1.0;
        vertices[1].tex_coord.y = 0.0;
        // Bottom-right vertex
        vertices[2].position.x = win.getw()/2 + w/2;
        vertices[2].position.y = win.geth()/2 + h/2;
        vertices[2].tex_coord.x = 1.0;
        vertices[2].tex_coord.y = 1.0;
        // Bottom-left vertex
        vertices[3].position.x = win.getw()/2 - w/2;
        vertices[3].position.y = win.geth()/2 + h/2;
        vertices[3].tex_coord.x = 0.0;
        vertices[3].tex_coord.y = 1.0;
        // Define the indices for two triangles that make up the trapezium
        int indices[6] = {0, 1, 2, 2, 3, 0};
        SDL_Rect rect = {0, 0, w, h};
        // Render the geometry
        SDL_RenderCopy(win.getren(), texture, NULL, &rect);
        SDL_RenderGeometry(win.getren(), texture, vertices, 4, indices, 6);
        win.pst();
        win.clr();
        SDL_Delay(10);
        //SDL_RenderGeometry(renderer, texture, vertices, 4, indices, 6);
    }
}