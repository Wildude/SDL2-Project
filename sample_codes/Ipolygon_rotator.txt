#include "../Files/headers/vector2D.h"
#include "../Files/Headers/BSDLF.h"
#include <fstream>
template<class T> void vin(T data_entered)
{
    //validation coming soon
}
int main(int argn, char** args)
{
    int sides, sidelength;
    cout<<" Enter number of vertices (sides): ";
    cin>>sides;
    cout<<" Enter sidelength: ";
    cin>>sidelength;
    Vflt2* vec1 = new Vflt2[sides];
    WINDOW win;
    win.crtB();
    TEXTURE* points = new TEXTURE[sides];
    TEXTURE* lines = new TEXTURE[sides];
    for(int i = 0; i < sides; i++)
    {
        lines[i].setren(win.getren());
        points[i].setren(win.getren());
        lines[i].load("../Images/point.jpg");
        points[i].load("../Images/point.jpg");
        points[i].queryF();
        lines[i].queryF();
        if(!lines[i].gettexture()){cout<<" line error\n";return 2;}
        if(!points[i].gettexture()){cout<<" point error\n"; return 3;}
    }
    win.pstcol(255, 255, 255, 255);
    TEXTURE cpoint;
    cpoint.setren(win.getren());
    cpoint.load("../Images/point_red.jpg");
    FONT the_text("../Fonts/Rock.ttf", 14);
    SDL_Color red;
    red.r = red.a = 255;
    red.g = red.b = 0;
    the_text.setcol1(red.r, red.b, red.g, red.a);
    SDL_Event event;
    TEXTURE board;
    board.setren(win.getren());
    double angle = 0;
    Vint2 center_v(320, 240);
    TEXTURE mouse;
    mouse.setren(win.getren());
    mouse.load("../Images/point_red.jpg");
    mouse.queryF();
    mouse.setcenter();
    Vint2 mousepos;
    SDL_ShowCursor(0);
    double angle2 = 0;
    while(event.type != SDL_QUIT)
    {
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        SDL_GetMouseState(&mousepos.getx(), &mousepos.gety());
        angle++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])sidelength++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])sidelength--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])angle2++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])angle2--;
        Vint2 rayterm(mousepos.getx() + 2000 * cos(torad(angle)), mousepos.gety() - 2000 * sin(torad(angle)));
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])sides++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])if(sides > 3)sides--;
        if(event.button.button == 1)SDL_GetMouseState(&center_v.getx(), &center_v.gety());
        vec1 = n_gonr(Vflt2(center_v.getx(), center_v.gety()), sides, sidelength);
        rotate_rC(vec1, angle2, sides);
        mouse.set_dstpos(mousepos.getx(), mousepos.gety());
        mouse.set_dstdim((mousepos - rayterm).getmag(), mouse.getdst().h);
        mouse.setangle(-1 * angler(mousepos, rayterm));
        mouse.drawC();
        char text[15];
        SDL_GetMouseState(&mousepos.getx(), &mousepos.gety());
        //cout<<" mousepos: "<<mousepos<<endl;
        if(in_polyB(vec1, Vflt2(mousepos.getx(), mousepos.gety()), Vflt2(rayterm.getx(), rayterm.gety()), sides))
		{
			strcpy(text, "mouse Detected");
		}
        else strcpy(text, "no mouse");
        for(int i = 0; i < sides; i++)
        {
        	points[i].set_dstpos(vec1[i].getx(), vec1[i].gety());
        	lines[i].set_dstpos(vec1[i].getx(), vec1[i].gety());
            lines[i].set_dstdim((vec1[i] - vec1[i != sides-1 ? i + 1 : 0]).getmag(), 1);
            double angle = -1 * angler(vec1[i], vec1[i != sides-1 ? i + 1 : 0]);
            lines[i].setangle(angle);
            lines[i].setcenter(0,0);
            points[i].drawC();
            lines[i].drawC();
        }
        Vflt2 center = C_x_y_find(vec1, sides);
        cpoint.queryF();
        cpoint.set_dstpos(center.getx(), center.gety());
        cpoint.drawC();
        board.surfcpy(the_text.blended_render((const char*)text));
        if(!board.gettexture()){cout<<" tex error: "<<SDL_GetError()<<endl; return -1;}
        board.queryF();
        board.set_dstpos(center.getx(), center.gety());
        board.drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
    SDL_Quit();
}
