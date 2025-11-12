//g++ -I../src/Include -L../src/Lib -o ../Executables/Tilemaptest.exe Tilemaptest.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net -lz
//
/*
* FINAL UPDATES
* - was able to rescale visible tiles to the camera
* - Need to fix center snapping issue (fixed)
* - Need to fix quick crashing issue (fixed)
* - Need to fix magnification misalignment issue (fixed)
* - Need to optimize the usage of render target (fixed)
* - Tilemap drawing system integrated
* - Need to fix tile rotating feature (able to rotate only the map, but movement is still local)
* - Level details not displayed properly (Layers cause program crash and only display '64')
* - Possible cause is map size (so above problem is almost fixed)
* 
*/
#include "../Headers/inclusions.hpp"
#include <map>
int main(int argn, char** args)
{
    WINDOW win("Tilemaptest");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    vector<vector<vector<int>>> Layers;
    Level bit16;
    bit16.parseLevel("../Files/XML/StageX.tmx", win.getren());
    // consider deleting doc by scoping out
    //bit16.display();
    //return 1;
    int mapWidth = bit16.getMapWidth();
    int mapHeight = bit16.getMapHeight();
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
    SDL_Color col = {200, 0, 0, 255};
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
    list.setpos(win.getw()/4, win.geth()/4);
    list.add("", NULL, &col);
    list.add();
    double angle = 0;
    int framestarter = 0;
    int quant = 3;
    TextInputHandler input;
    while(!input.shouldQuit()){
        input.update();
        bool moved = false, camscaled = false;
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        if(input.isKeyDown(SDL_SCANCODE_ESCAPE))break;
        if(input.isKeyDown(SDL_SCANCODE_Q))angle--;
        if(input.isKeyDown(SDL_SCANCODE_E))angle++;
        if(input.isKeyDown(SDL_SCANCODE_LEFT)){
            moved = true;
            vel.getx() -= speed * physx::delta;
        }
        if(input.isKeyDown(SDL_SCANCODE_RIGHT)){
            moved = true;
            vel.getx() += speed * physx::delta;
        }
        if(input.isKeyDown(SDL_SCANCODE_UP)){
            moved = true;
            vel.gety() += speed * physx::delta;
        }
        if(input.isKeyDown(SDL_SCANCODE_DOWN)){
            moved = true;
            vel.gety() -= speed * physx::delta;
        }
        if(!moved){
            framestarter = !framestarter ? SDL_GetTicks() : framestarter;
            if(SDL_GetTicks() - framestarter > 100){
                vel.getx() = 0;
                vel.gety() = 0;
                framestarter = SDL_GetTicks();
            }
        }
        else framestarter = 0;
        if(input.isKeyDown(SDL_SCANCODE_W)){
            speed += (speed >= 100 ? 0 : 1);
        }
        if(input.isKeyDown(SDL_SCANCODE_S)){
            speed -= (speed <= 0 ? 0 : 1);
        }
        if(input.isKeyReady(SDL_SCANCODE_SPACE, quant)){
            //vel = Vflt2_0;
            if(camera.w < win.getw() * 3 && camera.h < win.geth() * 3){
                camera.w *= 2;
                camera.h *= 2;
            }
            camscaled = true;
        }
        if(input.isKeyReady(SDL_SCANCODE_MINUS, quant)){
            if(camera.w > win.getw() / 10 && camera.h > win.getw() / 10){
                camera.w -= 5;
                camera.h -= 5;
            }
            camscaled = true;
        }
        if(input.isKeyReady(SDL_SCANCODE_EQUALS, quant)){
            if(camera.w < win.getw() * 3 && camera.h < win.geth() * 3){
                camera.w += 5;
                camera.h += 5;
            }
            camscaled = true;
        }
        if(input.isKeyReady(SDL_SCANCODE_BACKSPACE, quant)){   
            if(camera.w > win.getw() / 10 && camera.h > win.getw() / 10){
                camera.w /= 2;
                camera.h /= 2;
            }
            camscaled = true;
            cout << " backed\n";
        }
        if(input.isMouseDown(SDL_BUTTON_LEFT)){   
            input.setTextUse(true);
        }
        if(input.isMouseDown(SDL_BUTTON_RIGHT)){   
            input.setTextUse(false);
        }
        //vel = (vel.getmag() * cos(torad(angle)), vel.getmag() * sin(torad(angle)));
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
        bit16.Frender(win.getren(), camera);
        //
        midlinex.drawC(win.getren());
        midliney.drawC(win.getren());
        //
        list.edit(string(" text: " + input.getText()).c_str(), 0);
        list.edit(string(" textinput?: " + (input.getTextState() ? string("true") : string("false"))).c_str(), 1);
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
        SDL_Delay(16);
    }
    return 0;
}