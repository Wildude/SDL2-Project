//g++ -I../src/Include -L../src/Lib -o ../Executables/ Tilemaptest.exe Tilemaptest.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
//
/*
* FINAL UPDATES
* - was able to rescale visible tiles to the camera
* - Need to fix center snapping issue (fixed)
* - Need to fix quick crashing issue (fixed)
* - Need to fix magnification misalignment issue (fixed)
* - Need to optimize the usage of render target (fixed)
*/
#include "../Headers/inclusions.hpp"
#include <map>
int main(int argn, char** args)
{
    vector<vector<vector<int>>> Layers;
    Tileset tileset;
    {
        XMLDocument doc;
        doc.LoadFile("../Files/XML/StageX.tmx");
        tileset.setTileParams(doc, Layers);
    }
    // consider deleting doc by scoping out
    tileset.display();
    int mapWidth = tileset.tileWidth * tileset.width;
    WINDOW win("Tilemaptest");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    float speed = 10;
    SDL_Event event;
    TEXTURE man;
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 10, 30, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    man.surfcpy(surf, win.getren());
    man.queryF();
    man.magnify(2);
    surf = SDL_CreateRGBSurface(0, 2, win.geth(), 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    //
    Vflt2 vel(0, 0);
    int layers = Layers.size(), rows = Layers[0].size(), columns = Layers[0][0].size();
    vector<int> flat;
    flatten(Layers, flat);
    map<int, SDL_Texture*> tex_maps;
    for(int i = 0; i < tileset.tiles.size(); i++){
        tex_maps[i] = IMG_LoadTexture(win.getren(), tileset.tiles[i].c_str());
    }
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
    SDL_Color green = {0, 255, 0, 255};
    list.add(string("camera.w/2: " + to_string(camera.w/2)).c_str(), NULL, &green);
    list.add(string("man.getcenpos.x: " + to_string(man.get_cenpos().x)));
    list.add(string("camera.x: " + to_string(camera.x)));
    list.add();
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
                camscaled = true;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_MINUS]){
                if(camera.w > win.getw() / 10)camera.w-=5;
                camscaled = true;
                //camera.h--;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_EQUALS]){
                if(camera.w < win.getw() * 3)camera.w+=5;
                camscaled = true;
                //camera.h++;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_BACKSPACE]){
                //usescale = !usescale;
                if(camera.w > win.getw() / 10)camera.w /= 2;
                camscaled = true;
            }
        }
        float scalex = camera.w / win.getw();
        float xoff = win.getw() * (1 - scalex) / 2;
        man.getdst().x += vel.getx();
        man.getdst().y -= vel.gety();
        camera.x = (man.get_cenpos().x <= camera.w / 2 ? 0 : 1) * (man.get_cenpos().x - camera.w/2);
        camera.x = std::max(0.0f, std::min(camera.x, (float)(mapWidth - camera.w)));
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
                SDL_FRect rect = SDL_FRect({
                    xpos, // x position on screen
                    y * (float)tileset.tileHeight - camera.y, // y position on screen
                    x != endX ? (float)tileset.tileWidth : (float)(camera.w - xpos), // width of the tile
                    (float)tileset.tileHeight                 // height of the tile
                });
                SDL_Rect srcrect = SDL_Rect({
                    0,
                    0,
                    x != endX  ? (int)tileset.tileWidth : (int)(camera.w - xpos), // width of the tile
                    (int)tileset.tileHeight
                });
                // Render the tile if it's within the camera view
                SDL_RenderCopyF(win.getren(), tex_maps[flat[i] - 1], &srcrect, &rect);
            }
        }
        //SDL_SetRenderDrawColor(win.getren(), 0, 150, 100, 255);
        //SDL_RenderDrawLineF(win.getren(), camera.w/2, 0, camera.w/2, win.geth());
        /*
        TEXTURE midline(surf, win.getren());
        midline.queryF();
        midline.set_dstpos(win.getw()/2 - 1, 0);
        midline.drawC(win.getren());
        */
        list.edit(string("camera.w/2: " + to_string(camera.w/2)).c_str(), 0);
        list.edit(string("man.getcenpos.x: " + to_string(man.get_cenpos().x)).c_str(), 1);
        list.edit(string("camera.x: " + to_string(camera.x)).c_str(), 2);
        list.edit((string("X(start, end, W): (" + to_string(startX) + ", " + to_string(endX) + ", " + to_string(W) + ")")).c_str(), 3);
        list.draw(win.getren());
        SDL_RenderDrawLineF(win.getren(), 160, 0, 160, win.geth());
        SDL_RenderDrawLineF(win.getren(), 480, 0, 480, win.geth());
        // must fix the center snapping issue at beginning and end of sliding
        man.drawOF(win.getren(), &camera, 1 / scalex);
        SDL_SetRenderTarget(win.getren(), NULL);
        SDL_Rect dest = { 0, 0, win.getw(), win.geth()};
        SDL_RenderCopy(win.getren(), renderTarget, NULL, NULL);
        win.pst();
        SDL_Delay(10);
    }
    return 0;
}