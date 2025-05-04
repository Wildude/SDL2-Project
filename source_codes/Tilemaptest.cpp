//g++ -I../src/Include -L../src/Lib -o ../Executables/ Tilemaptest.exe Tilemaptest.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
//
/*
* FINAL UPDATES
* - was able to rescale visible tiles to the camera
* - Need to fix center snapping issue (fixed)
* - Need to fix quick crashing issue (fixed)
* - Need to fix magnification misalignment issue (fixed)
* - Need to optimize the usage of render target (fixed)
* - Need to fix tile rotating feature (able to rotate only the map, but movement is still local)
*/
#include "../Headers/inclusions.hpp"
#include <map>
int main(int argn, char** args)
{
    WINDOW win("Tilemaptest");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    vector<vector<vector<int>>> Layers;
    Tileset tileset;
    tileset.parseALL("../Files/XML/16bit world.tmx", Layers, win.getren());
    // consider deleting doc by scoping out
    int mapWidth = tileset.tileWidth * tileset.width;
    int mapHeight = tileset.tileHeight * tileset.height;
    cout << mapWidth << " * " << mapHeight << endl;
    float speed = 10;
    SDL_Event event;
    TEXTURE man;
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 5, 8, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    man.surfcpy(surf, win.getren());
    man.queryF();
    man.magnify(2);
    surf = SDL_CreateRGBSurface(0, 2, win.geth(), 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    SDL_Surface* surfy = SDL_CreateRGBSurface(0, win.getw(), 2, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surfy, 0, 255, 0);
    TEXTURE midlinex(surf, win.getren());
    midlinex.queryF();
    midlinex.set_dstpos(win.getw()/2 - 1, 0);
    TEXTURE midliney(surfy, win.getren());
    midliney.queryF();
    midliney.set_dstpos(0, win.geth()/2 - 1);
    // free both surfaces from memory
    SDL_FreeSurface(surf);
    SDL_FreeSurface(surfy);
    //
    Vflt2 vel(0, 0);
    int layers = Layers.size(), rows = Layers[0].size(), columns = Layers[0][0].size();
    vector<int> flat;
    flatten(Layers, flat);
    int possize = tileset.pos.size();
    map<int, SDL_Texture*> tex_maps;
    //tileset.display();
    tex_maps[0] = IMG_LoadTexture(win.getren(), tileset.src.c_str());
    SDL_Color col = {200, 0, 0, 255};
    //
    /*
    FONT font("../Fonts/nyala.ttf", 8);
    
    for(int i = 0; i < possize; i++){
        string text = string("(" + to_string(tileset.pos[i].getx()) + "," + to_string(tileset.pos[i].gety()) + ")");
        SDL_Surface* surf = TTF_RenderText_Blended(font.getfont(), text.c_str(), col);
        if(!surf)cout << '\a';
        tex_maps[i] = SDL_CreateTextureFromSurface(win.getren(), surf);
        SDL_FreeSurface(surf);
    }
    */
    //
    ofstream file("../Files/logTilesize.txt");
    for(int i = 0; i < layers; i++)
        for(int j = 0; j < Layers[i].size(); j++){
            for(int k = 0; k < Layers[i][j].size(); k++)
                file << ' ' << Layers[i][j][k];
            file << endl;
        }
    //
    // cout << layers << ' ' << rows << ' ' << columns << endl;
    SDL_FRect camera = {0, 0, (float)win.getw(), (float)win.geth()};
    int FrameStarter = 0;
    man.set_cenpos(win.getw()/2, win.geth()/2);
    bool usescale = false;
    SDL_Texture* renderTarget = SDL_CreateTexture(
        win.getren(),
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        (int)camera.w,
        (int)camera.h
    );        
    TextList list;
    list.setxpos(0);
    list.add("", NULL, &col);
    list.add();
    list.add();
    list.add();
    list.add();
    double angle = 0;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        bool camscaled = false;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(event.type != SDL_KEYDOWN){
            int ticksnow = SDL_GetTicks() - FrameStarter;
            if(ticksnow > 100)vel = Vflt2_0;
        }
        //
        else{
            FrameStarter = SDL_GetTicks();
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Q]){
                angle--;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_E]){
                angle++;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){
                vel.getx() -= speed * physx::delta;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){
                vel.getx() += speed * physx::delta;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]){
                vel.gety() += speed * physx::delta;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]){
                vel.gety() -= speed * physx::delta;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W]){
                speed += (speed >= 100 ? 0 : 1);
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S]){
                speed -= (speed <= 0 ? 0 : 1);
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]){
                //vel = Vflt2_0;
                if(camera.w < win.getw() * 3)camera.w *= 2;
                if(camera.h < win.geth() * 3)camera.h *= 2;
                camscaled = true;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_MINUS]){
                if(camera.w > win.getw() / 10)camera.w -= 5;
                if(camera.h > win.geth() / 10)camera.h -= 5;
                camscaled = true;
                //camera.h--;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_EQUALS]){
                if(camera.w < win.getw() * 3)camera.w += 5;
                if(camera.h < win.geth() * 3)camera.h += 5;
                camscaled = true;
                //camera.h++;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_BACKSPACE]){
                //usescale = !usescale;
                if(camera.w > win.getw() / 10)camera.w /= 2;
                if(camera.h > win.getw() / 10)camera.h /= 2;
                camscaled = true;
            }
        }
        float scalex = camera.w / win.getw();
        float xoff = win.getw() * (1 - scalex) / 2;
        man.getdst().x += vel.getx();
        man.getdst().y -= vel.gety();
        camera.x = (man.get_cenpos().x <= camera.w / 2 ? 0 : 1) * (man.get_cenpos().x - camera.w/2);
        camera.x = std::max(0.0f, std::min(camera.x, (float)(mapWidth - camera.w)));
        camera.y = (man.get_cenpos().y <= camera.h / 2 ? 0 : 1) * (man.get_cenpos().y - camera.h/2);
        camera.y = std::max(0.0f, std::min(camera.y, (float)(mapHeight - camera.h)));
        if(camscaled){
            SDL_DestroyTexture(renderTarget);
            renderTarget = SDL_CreateTexture(
                win.getren(),
                SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_TARGET,
                (int)camera.w,
                (int)camera.h
            );        
        }
        SDL_SetRenderTarget(win.getren(), renderTarget);
        win.clr();
        int startX = max((int)(camera.x / tileset.tileWidth), 0);
        float decendX = (max(man.get_cenpos().x, camera.w/2) + camera.w/2) / tileset.tileWidth;
        int endX = min((int)(decendX == floor(decendX) ? decendX - 1 : decendX), columns - 1);
        int startY = std::max((int)(camera.y / tileset.tileHeight), 0);
        int endY = std::min((int)((camera.y + camera.h) / tileset.tileHeight), (int)(flat.size() / columns) - 1);
        float W = 0;
        // loop over visible tile grid
        for (int x = startX; x <= endX; ++x) {
            for (int y = startY; y <= endY; ++y) {
                // beginning tiles not clipped because of flicker issue
                // fix issue later
                int i = y * columns + x;  // flattened index of tile (x, y)

                if (flat[i] <= 0) continue; // skip empty tiles

                // Calculate the position of the tile
                float xpos = x * (float)tileset.tileWidth - camera.x;
                float ypos = y * (float)tileset.tileHeight - camera.y;

                SDL_FRect rect = SDL_FRect({
                    xpos, // x position on screen
                    ypos, // y position on screen
                    x != endX ? (float)tileset.tileWidth : (float)(camera.w - xpos), // width of the tile
                    y != endY ? (float)tileset.tileHeight : (float)(camera.h - ypos) // height of the tile
                });
                for(int j = 0; j < layers; j++){
                    SDL_Rect srcrect = SDL_Rect({
                        tileset.pos[flat[i + rows * columns * j] - 1].getx() * tileset.tileWidth,
                        tileset.pos[flat[i + rows * columns * j] - 1].gety() * tileset.tileHeight,
                        x != endX  ? (int)tileset.tileWidth : (int)(camera.w - xpos), // width of the tile
                        y != endY ? (int)tileset.tileHeight : (int)(camera.h - ypos)
                    });
                    SDL_RenderCopyExF(win.getren(), tex_maps[0], &srcrect, &rect, 0, NULL, SDL_FLIP_NONE);
                }
                // Render the tile if it's within the camera view
            }
        }
        //
        midlinex.drawC(win.getren());
        midliney.drawC(win.getren());
        //
        list.edit(string("camera.D/2(w,h): (" + to_string((int)camera.w / 2) + ", " + to_string((int)camera.h / 2) + ")").c_str(), 0);
        list.edit(string("man.getcenpos(x,y, w, h): (" + to_string((int)man.get_cenpos().x) + ", " + to_string((int)man.get_cenpos().y) + ", " + to_string((int)(man.getdst().w * (1 / scalex))) + ", " + to_string((int)(man.getdst().h * (1 / scalex))) + ")").c_str(), 1);
        list.edit(string("camera(x,y,w,h): (" + to_string((int)camera.x) + ", " + to_string((int)camera.y) + ", " + to_string((int)camera.w) + ", " + to_string((int)camera.h) + ")").c_str(), 2);
        list.edit(string("X(start, end): (" + to_string(startX) + ", " + to_string(endX) + ")").c_str(), 3);
        list.edit(string("Y(start, end): (" + to_string(startY) + ", " + to_string(endY) + ")").c_str(), 4);
        list.draw(win.getren());
        //
        SDL_RenderDrawLineF(win.getren(), win.getw()/4, 0, win.getw()/4, win.geth());
        SDL_RenderDrawLineF(win.getren(), win.getw() * 0.75, 0, win.getw() * 0.75, win.geth());
        SDL_RenderDrawLineF(win.getren(), 0, win.geth()/4, win.getw(), win.geth()/4);
        SDL_RenderDrawLineF(win.getren(), 0, win.geth() * 0.75, win.getw(), win.geth() * 0.75);
        //
        man.drawOF(win.getren(), &camera, 1, -angle);
        //
        SDL_SetRenderTarget(win.getren(), NULL);
        SDL_RenderCopyEx(win.getren(), renderTarget, NULL, NULL, angle, NULL, SDL_FLIP_NONE);
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
    return 0;
}