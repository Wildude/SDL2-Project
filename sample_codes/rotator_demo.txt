#include "../Files/headers/vector2D.h"
#include "../Files/headers/BSDLF.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <vector>
#include <conio.h>
#include <cstring>
template<class T> void vin(T data_entered)
{
    //validation coming soon
}
int main(int argn, char** args)
{
    WINDOW win;
    TEXTURE tex1;
    win.crtB();
    tex1.setren(win.getren());
    win.pstcol(255, 255, 255, 255);
    tex1.load("../Images/point.jpg");
    tex1.queryF();
    tex1.set_dstdim(1, 100);
    tex1.set_dstpos(100, 100);
    tex1.setcenter();
    SDL_Event event;
    Vint2 mouse;
    int speed = 1;
    while(event.type != SDL_QUIT)
    {
    	static int i = 0;
    	SDL_PollEvent(&event);
    	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
    	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])speed++;
    	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])speed--;
    	SDL_GetMouseState(&mouse.getx(), &mouse.gety());
    	tex1.set_dstpos(mouse.getx() - tex1.getcenter().x, mouse.gety() - tex1.getcenter().y);
    	tex1.setangle(i);
    	tex1.drawO();
    	win.clr();
    	SDL_Delay(10);
    	i+=speed;
    }
    SDL_Quit();
    tex1.display();
}
