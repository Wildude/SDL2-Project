/*
* Polygon detection checker
* constructs user inputed number of regular polygons
* INCOMPLETE (currently only constructs two)
* checks polygon detection for two polygons
* purpose:
    to quickly visualize and help in finding an algorithm description for:
    - inter-polygon intersection (to be tested in this program)
    - collision (a direct outcome of this program, if suck-seed-ed)
*
*/
#include "../Files/headers/vector2D.h"
#include "../Files/Headers/BSDLF.h"
#include <fstream>
template<class T> void vin(T data_entered)
{
    //validation coming soon
}
int main(int argn, char** args)
{
    int num;
    cout<<" Enter number of polygons: ";
    cin>>num;
    int **Polygons = new int*[num];
    Vflt2 *centers = new Vflt2[num];
    cout<<" Enter "<<num<<" polygon details:\n";
    for(int i = 0; i < num; i++)
    {
        Polygons[i] = new int[2];
        cout<<" polygon "<<i + 1<<":\n";
        cout<<" number of sides: ";
        cin>>Polygons[i][0];
        cout<<" sidelength: ";
        cin>>Polygons[i][1];
        cout<<" center(x, y): ";
        cin>>centers[i];
    }
    WINDOW win;
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE *cpoint = new TEXTURE[num];
    FONT *the_text = new FONT[num];
    SDL_Color *cols = new SDL_Color[num];
    TEXTURE *board = new TEXTURE[num];
    double *angles = new double[num];
    for(int i = 0; i < num; i++)
    {
        cpoint[i].setren(win.getren());
        cpoint[i].setpath("../Images/point_red.jpg");
        cpoint[i].load();
        the_text[i].setpath("../Fonts/Rock.ttf");
        the_text[i].setptsize(15);
        the_text[i].setfontD();
        cols[i] = {255, 0, 0, 255};
        the_text[i].setcol1(cols[i].r, cols[i].g, cols[i].b, cols[i].a);
        board[i].setren(win.getren());
        angles[i] = 0;
    }
    double angle0 = 0;
    SDL_Event event;
    TEXTURE mouse;
    mouse.setren(win.getren());
    mouse.load("../Images/point_red.jpg");
    mouse.queryF();
    mouse.setcenter();
    Vflt2 mousepos;
    SDL_ShowCursor(0);
    while(event.type != SDL_QUIT)
    {
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        mousepos.getx() = x;
        mousepos.gety() = y;
        if(event.button.button == 1)centers[0] = mousepos;
        if(event.button.button == 3)centers[1] = mousepos;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])angles[0]++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])angles[0]--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])angles[1]++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])angles[1]--;
        Vflt2 rayterm(mousepos.getx() + 2000 * cos(torad(angle0)), mousepos.gety() - 2000 * sin(torad(angle0)));
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])Polygons[0][0]++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])if(Polygons[0][0] > 3)Polygons[0][0]--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])Polygons[0][1] += 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])if(Polygons[0][1] > 50)Polygons[0][1] -= 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_L])Polygons[1][0]++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_J])if(Polygons[1][0] > 3)Polygons[1][0]--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_I])Polygons[1][1] += 5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_K])if(Polygons[1][1] > 50)Polygons[1][1] -= 5;
        Vflt2* vertices = new Vflt2[Polygons[0][0]];
        TEXTURE* points = new TEXTURE[Polygons[0][0]];
        TEXTURE* lines = new TEXTURE[Polygons[0][0]];
        Vflt2* vertices2 = new Vflt2[Polygons[1][0]];
        TEXTURE* points2 = new TEXTURE[Polygons[1][0]];
        TEXTURE* lines2 = new TEXTURE[Polygons[1][0]];
        for(int i = 0; i < Polygons[0][0]; i++)
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
        for(int i = 0; i < Polygons[1][0]; i++)
        {
            lines2[i].setren(win.getren());
            points2[i].setren(win.getren());
            lines2[i].load("../Images/point.jpg");
            points2[i].load("../Images/point.jpg");
            points2[i].queryF();
            lines2[i].queryF();
            if(!lines2[i].gettexture()){cout<<" line error\n";return 2;}
            if(!points2[i].gettexture()){cout<<" point error\n"; return 3;}
        }
        vertices = n_gonr(centers[0], Polygons[0][0], Polygons[0][1]);
        rotate_rC(vertices, angles[0], Polygons[0][0]);
        vertices2 = n_gonr(centers[1], Polygons[1][0], Polygons[1][1]);
        rotate_rC(vertices2, angles[1], Polygons[1][0]);
        mouse.set_dstpos(mousepos.getx(), mousepos.gety());
        mouse.set_dstdim((mousepos - rayterm).getmag(), mouse.getdst().h);
        mouse.setangle(-1 * angler(mousepos, rayterm));
        mouse.drawC();
        char text[15], text2[15];
        int count = INTERSECT(vertices, vertices2, Polygons[0][0], Polygons[1][0]);
        if(in_polyB(vertices, mousepos, rayterm, Polygons[0][0]))
		{
			strcpy(text, "mouse Detected");
		}
        else strcpy(text, strmap::to_cc_str(count));
        if(in_polyB(vertices2, mousepos, rayterm, Polygons[1][0]))
		{
			strcpy(text2, "mouse Detected");
		}
        else strcpy(text2, strmap::to_cc_str(count));
        for(int i = 0; i < Polygons[0][0]; i++)
        {
        	points[i].set_dstpos(vertices[i].getx(), vertices[i].gety());
        	lines[i].set_dstpos(vertices[i].getx(), vertices[i].gety());
            lines[i].set_dstdim((vertices[i] - vertices[i != Polygons[0][0]-1 ? i + 1 : 0]).getmag(), 1);
            double angle = -1 * angler(vertices[i], vertices[i != Polygons[0][0]-1 ? i + 1 : 0]);
            lines[i].setangle(angle);
            lines[i].setcenter(0,0);
            points[i].drawC();
            lines[i].drawC();
        }
        for(int i = 0; i < Polygons[1][0]; i++)
        {
        	points2[i].set_dstpos(vertices2[i].getx(), vertices2[i].gety());
        	lines2[i].set_dstpos(vertices2[i].getx(), vertices2[i].gety());
            lines2[i].set_dstdim((vertices2[i] - vertices2[i != Polygons[1][0]-1 ? i + 1 : 0]).getmag(), 1);
            double angle = -1 * angler(vertices2[i], vertices2[i != Polygons[1][0]-1 ? i + 1 : 0]);
            lines2[i].setangle(angle);
            lines2[i].setcenter(0,0);
            points2[i].drawC();
            lines2[i].drawC();
        }
        Vflt2 center = C_x_y_find(vertices, Polygons[0][0]);
        cpoint[0].queryF();
        cpoint[0].set_dstpos(center.getx(), center.gety());
        cpoint[0].drawC();
        board[0].surfcpy(the_text[0].blended_render((const char*)text));
        if(!board[0].gettexture()){cout<<" tex error: "<<SDL_GetError()<<endl; return -1;}
        board[0].queryF();
        board[0].set_dstpos(center.getx(), center.gety());
        board[0].drawC();
        Vflt2 center2 = C_x_y_find(vertices2, Polygons[1][0]);
        cpoint[1].queryF();
        cpoint[1].set_dstpos(center2.getx(), center2.gety());
        cpoint[1].drawC();
        board[1].surfcpy(the_text[1].blended_render((const char*)text2));
        if(!board[1].gettexture()){cout<<" tex error: "<<SDL_GetError()<<endl; return -1;}
        board[1].queryF();
        board[1].set_dstpos(center2.getx(), center2.gety());
        board[1].drawC();
        win.pst();
        win.clr();
        SDL_Delay(10);
        angle0+=1;
    }
    SDL_Quit();
}
