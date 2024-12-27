//g++ -I../src/Include -L../src/Lib -o ../Executables/Texture_mapper.exe Texture_mapper.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    cout << " Welcome to the texture mapper: \n";
    cout << " You have got the foolowing graphics drivers: \n";
    int numDrivers = SDL_GetNumRenderDrivers();
    if (numDrivers < 1) {
        std::cerr << "No render drivers available." << std::endl;
        return -1;
    }
    SDL_RendererInfo rendererInfo;
    for (int i = 0; i < numDrivers; ++i) {
        if (SDL_GetRenderDriverInfo(i, &rendererInfo) == 0) {
            std::cout << "Driver " << i << ": " << rendererInfo.name << std::endl;
        } else {
            std::cerr << "SDL_GetRenderDriverInfo Error: " << SDL_GetError() << std::endl;
        }
    }
    int chosenDriver;
    cout << " Enter a number to choose a driver (-1 - 5) (-1 for default): ";
    cin >> chosenDriver;
    system("cls");
    int rendermode;
    cout << " SDL_RENDERER_TARGETTEXTURE - 8\n";
    cout << " SDL_RENDERER_SOFTWARE - 1\n";
    cout << " SDL_RENDERER_PRESENTVSYNC - 4\n";
    cout << " SDL_RENDERER_ACCELERATED - 2\n";
    cout << " Choose out of the following rendering modes: ";
    cin >> rendermode;
    system("cls");
    int blendmode;
    cout << " SDL_BLENDMODE_NONE - 0\n";
    cout << " SDL_BLENDMODE_BLEND - 1\n";
    cout << " SDL_BLENDMODE_ADD - 2\n";
    cout << " SDL_BLENDMODE_MOD - 4\n";
    cout << " SDL_BLENDMODE_MUL - 8\n";
    cout << " SDL_BLENDMODE_INVALID - 9\n";
    cout << " Choose blendmode: ";
    cin >> blendmode;
    system("cls");
    blendmode = (blendmode >= 9 || blendmode < 0 ? (int)SDL_BLENDMODE_INVALID : blendmode);
    WINDOW win("Texture mapper");
    win.crtwin();
    win.crtren(NULL, chosenDriver, rendermode);
    win.pstcol(255, 255, 255, 255);
    // Define the vertices of the trapezium
    SDL_Vertex vertices[5];
    // Top-left vertex
    SDL_Event event;
    SDL_GetRenderDriverInfo(chosenDriver, &rendererInfo);
    Uint8 r = 255, g = 0, b = 255;
    Vflt2 center(win.getw()/2, win.geth()/2);
    double angle = 45;
    float distance = 200;
    SDL_Texture* texture = IMG_LoadTexture(win.getren(), "../Images/AAU.png");
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    int x = win.getw() - w, y = 0;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])y--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])y++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])x--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])x++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]){x = win.getw() - w; y = 0;}
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])h++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])if(h > 50)h--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])if(w > 50)w--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])w++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Z])r--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_X])r++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_C])g--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_V])g++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_B])b--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_N])b++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Q])angle--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_E])angle++;
        if(event.button.button == 1){SDL_GetMouseState(&x, &y);}
        TXT driverName(rendererInfo.name, win.getren());
        driverName.board.set_dstpos(0, 0);
        driverName.board.drawC();
        if (!texture) {
            cerr << "Error creating texture: " << SDL_GetError() << endl;
        }
        SDL_SetTextureBlendMode(texture, (SDL_BlendMode)blendmode);
        // Top-left vertex
        vertices[0].position.x = center.getx() - w/2;
        vertices[0].position.y = center.gety() - h/2;
        vertices[0].tex_coord.x = 0.0;
        vertices[0].tex_coord.y = 0.0;
        // Top-right vertex
        vertices[1].position.x = center.getx() + w/2;
        vertices[1].position.y = center.gety() - h/2;
        vertices[1].tex_coord.x = 1.0;
        vertices[1].tex_coord.y = 0.0;
        // Bottom-right vertex
        vertices[2].position.x = center.getx() + w/2;
        vertices[2].position.y = center.gety() + h/2;
        vertices[2].tex_coord.x = 1.0;
        vertices[2].tex_coord.y = 1.0;
        // Bottom-left vertex
        vertices[3].position.x = center.getx() - w/2;
        vertices[3].position.y = center.gety() + h/2;
        vertices[3].tex_coord.x = 0.0;
        vertices[3].tex_coord.y = 1.0;
        // Center vertex
        vertices[4].position.x = center.getx();
        vertices[4].position.y = center.gety();
        vertices[4].tex_coord.x = 0.5;
        vertices[4].tex_coord.y = 0.5;
        SDL_Vertex vertices2[5];
        for(int i = 0; i < 5; i++){
            float z = (vertices[i].position.x - center.getx()) * sin(torad(angle));
            float scale = distance / (distance - z);
            vertices2[i].tex_coord = vertices[i].tex_coord;
            vertices2[i].position.x = (vertices[i].position.x - center.getx()) * cos(torad(angle)) + center.getx();
            vertices2[i].position.y = (vertices[i].position.y - center.gety()) * scale + center.gety();
        }
        // Define the indices for two triangles that make up the trapezium
        int indices[12] = {0, 4, 3, 0, 4, 1, 1, 4, 2, 2, 4, 3};
        SDL_Rect rect = {x, y, w, h};
        // Render the geometry
        SDL_RenderCopy(win.getren(), texture, NULL, &rect);
        SDL_RenderGeometry(win.getren(), texture, vertices2, 5, indices, 12);
        win.pst();
        win.clr();
        SDL_Delay(10);
        //SDL_RenderGeometry(renderer, texture, vertices, 4, indices, 6);
    }
}