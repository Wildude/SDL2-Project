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
#include "../Files/Headers/physics.h"
#include "../Files/Headers/BSDLF.h"
#include <fstream>
template<class T> void vin(T data_entered)
{
    //validation coming soon
}
int main(int argn, char** args)
{
	kinematics k1, k2;
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
	k1.pos = centers[0];
	k2.pos = centers[1];
    WINDOW win;
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    TEXTURE *cpoint = new TEXTURE[num];
    FONT *the_text = new FONT[num];
    SDL_Color *cols = new SDL_Color[num];
    TEXTURE *board = new TEXTURE[num];
    double *angles = new double[num];
    Vflt2** Polyvertices = new Vflt2*[num];
	TEXTURE** points = new TEXTURE*[num];
    TEXTURE** lines = new TEXTURE*[num];
    for(int i = 0; i < num; i++)
    {
        cpoint[i].setren(win.getren());
        cpoint[i].setpath("../Images/point_red.jpg");
        cpoint[i].load();
		cpoint[i].queryF();
		cpoint[i].setcenter();
        the_text[i].setpath("../Fonts/Rock.ttf");
        the_text[i].setptsize(15);
        the_text[i].setfontD();
        cols[i] = {255, 0, 0, 255};
        the_text[i].setcol1(cols[i].r, cols[i].g, cols[i].b, cols[i].a);
        board[i].setren(win.getren());
        angles[i] = 0;
        Polyvertices[i] = new Vflt2[Polygons[i][0]];
		points[i] = new TEXTURE[Polygons[i][0]];
        lines[i] = new TEXTURE[Polygons[i][0]];
		for(int j = 0; j < Polygons[i][0]; j++)
		{
			lines[i][j].setren(win.getren());
            points[i][j].setren(win.getren());
            lines[i][j].load("../Images/point.jpg");
            points[i][j].load("../Images/point.jpg");
            points[i][j].queryF();
            lines[i][j].queryF();
            if(!lines[i][j].gettexture()){cout<<" line error\n";return 2;}
            if(!points[i][j].gettexture()){cout<<" point error\n"; return 3;}
		}
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
    double angle = 0;
    while(event.type != SDL_QUIT)
    {
		k1.vel = Vflt2_0;
        k2.vel = Vflt2_0;
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        int x, y;
        SDL_GetMouseState(&x, &y);
        mousepos.getx() = x;
        mousepos.gety() = y;
        if(event.button.button == 1)centers[0] = mousepos;
        if(event.button.button == 3)centers[1] = mousepos;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])k1.vel.gety() += 10;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])k1.vel.gety() -= 10;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])k1.vel.getx() += 10;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])k1.vel.getx() -= 10;
        Vflt2 rayterm(mousepos.getx() + 2000 * cos(torad(angle0)), mousepos.gety() - 2000 * sin(torad(angle0)));
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])k2.vel.gety() += 10;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])k2.vel.gety() -= 10;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])k2.vel.getx() += 10;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])k2.vel.getx() -= 10;
        k1.up_vel();
        k2.up_vel();
        centers[0].getx() += k1.vel.getx() * quanta;
        centers[0].gety() -= k1.vel.gety() * quanta;
        centers[1].getx() += k2.vel.getx() * quanta;
        centers[1].gety() -= k2.vel.gety() * quanta;
        for(int i = 0; i < num; i++)
        {
            Polyvertices[i] = n_gonr(centers[i], Polygons[i][0], Polygons[i][1]);
            rotate_rC(Polyvertices[i], (i % 2 ? angle : -1 * angle), Polygons[i][0]);
        }
        for(int i = 0; i < num; i++)
        {
            //cout<<" measuring Polygon: "<<i + 1<<" with: \n";
            for(int j = 0; j < num; j++)
            {
                if(i == j)continue;
                //cout<<' '<<j + 1<<':'<<endl;
                Vflt2* detected_point = NULL;
                for(int k = 0; k < Polygons[i][0]; k++)
                {
                    if(p_poly(Polyvertices[j], Polyvertices[i][k], Polygons[j][0]))
                    {
                        detected_point = new Vflt2;
                        *detected_point = Polyvertices[i][k];
                    }
                }
                if(detected_point)
                {
                    //cout<<" point detected: "<<*detected_point<<endl;
                    double angle = angler(centers[j], centers[i]);
                    Vflt2 term = Vflt2
                    (
                        detected_point->getx() + 2000 * cos(torad(angle)), 
                        detected_point->gety() - 2000 * sin(torad(angle))
                    );
                    Vflt2* x_point = NULL;
                    for(int k = 0; k < Polygons[j][0]; k++)
                    {
                        if(intersector_B(*detected_point, term, Polyvertices[j][k], Polyvertices[j][k != Polygons[j][0] - 1 ? k + 1: 0]))
                        {
                            x_point = new Vflt2;
                            *x_point = intersector(*detected_point, term, Polyvertices[j][k], Polyvertices[j][k != Polygons[j][0] - 1 ? k + 1: 0]);
                        }
                    }
                    if(x_point)
                    {
                      //  cout<<" Reintersecion: "<<*x_point<<endl;
                        float mag = (*detected_point - *x_point).getmag();
                        centers[i].getx() += mag * cos(torad(angle));
                        centers[i].gety() -= mag * sin(torad(angle));
                        Polyvertices[i] = n_gonr(centers[i], Polygons[i][0], Polygons[i][1]);
                    }
                }
            }
        }
        //system("cls");
        mouse.set_dstpos(mousepos.getx(), mousepos.gety());
        //mouse.set_dstdim((mousepos - rayterm).getmag(), mouse.getdst().h);
        //mouse.setangle(-1 * angler(mousepos, rayterm));
        mouse.drawC();
		for(int i = 0; i < num; i++)
		{
			for(int j = 0; j < Polygons[i][0]; j++)
			{
				points[i][j].set_dstpos(Polyvertices[i][j].getx(), Polyvertices[i][j].gety());
				lines[i][j].set_dstpos(Polyvertices[i][j].getx(), Polyvertices[i][j].gety());
				lines[i][j].set_dstdim((Polyvertices[i][j] - Polyvertices[i][j != Polygons[i][0]-1 ? j + 1 : 0]).getmag(), 1);
				double angle = -1 * angler(Polyvertices[i][j], Polyvertices[i][j != Polygons[i][0]-1 ? j + 1 : 0]);
				lines[i][j].setangle(angle);
				lines[i][j].setcenter(0,0);
				points[i][j].drawC();
				lines[i][j].drawC();
			}
			Vflt2 center = C_x_y_find(Polyvertices[i], Polygons[i][0]);
			cpoint[i].set_dstpos(center.getx(), center.gety());
			cpoint[i].drawC();
			string str = "(" + strmap::to_str((int)center.getx()) + "," + strmap::to_str((int)center.gety()) + ")";
			board[i].surfcpy(the_text[i].blended_render(str.c_str()));
			if(!board[i].gettexture()){cout<<" tex error: "<<SDL_GetError()<<endl; return -1;}
			board[i].queryF();
			board[i].set_dstpos(center.getx(), center.gety());
			board[i].drawC();
		}
        win.pst();
        win.clr();
        SDL_Delay(10);
        angle+=5;
    }
    SDL_Quit();
}
