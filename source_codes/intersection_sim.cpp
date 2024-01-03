#include "../Files/headers/vector2D.h"
#include "../Files/headers/BSDLF.h"
#include <conio.h>
template<class T> void vin(T data_entered)
{
    //validation coming soon
}
int main(int argn, char** args)
{
	Vint2 L[5] = 
	{
		Vint2(320, 200), 
		Vint2(L[0].getx() + 100, L[0].gety() - 200),
		Vint2(220, 200),
		Vint2(L[2].getx() + 400, L[2].gety() - 200),
		intersector(L[0], L[1], L[2], L[3])
	};
	int mag = 10;
	WINDOW win;
	win.crtB();
	win.pstcol(255, 255, 255, 255);
	//L[4] *= -1;
	TEXTURE tex[5];
	for(int i = 0; i < 5; i++)
	{
		tex[i].setren(win.getren());
		if(i != 4)tex[i].load("../Images/point.jpg");
		else tex[i].load("../Images/point_red.jpg");
		tex[i].queryF();
		tex[i].set_dstdim(tex[i].getsrc().w * mag, tex[i].getsrc().h * mag);
		tex[i].setcenter(tex[i].getdst().w / mag, tex[i].getdst().h / mag);
	}
	SDL_Event event;
	while(event.type != SDL_QUIT)
	{
		SDL_PollEvent(&event);
		if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
		if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])SDL_GetMouseState(&L[0].getx(), &L[0].gety());
		if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])SDL_GetMouseState(&L[1].getx(), &L[1].gety());
		if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])SDL_GetMouseState(&L[2].getx(), &L[2].gety());
		if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_F])SDL_GetMouseState(&L[3].getx(), &L[3].gety());
		for(int i = 0; i < 5; i++)
		{
			if(i == 4)
			{
				L[i] = intersector(L[0], L[1], L[2], L[3]);
				cout<<L[i]<<endl;
			}
			tex[i].set_dstpos(L[i].getx(), L[i].gety());
			//cout<<" pos["<<i<<"] = "<<L[i]<<endl;
			if(i == 0 || i == 2)
			{
				tex[i].set_dstdim((L[i] - L[i+1]).getmag(), tex[i].getdst().h);
				tex[i].setangle(-1 * angler(L[i], L[i+1]));	
			}
			tex[i].drawO();
		}
		//system("cls");
		win.clr();
		SDL_Delay(10);
	}
	SDL_Quit();	
}
/*


*/
