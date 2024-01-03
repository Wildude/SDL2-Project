#include "../Files/headers/vector2D.h"
#include "../Files/Headers/BSDLF.h"
#include <vector>
#include <string>
template<class T> void vin(T data_entered)
{
    //validation coming soon
}
int main(int argn, char** args)
{
    TTF_Init();
    WINDOW win;
	//("Polygon Drawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_FULLSCREEN);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    SDL_Event event;
    typedef vector<Vint2> VECS;
    typedef vector<TEXTURE> TEXS;
    typedef vector<string> STRS;
    VECS ver;
    TEXS bds;
    TEXS ims;
    STRS strs;
    Vint2 mousepos;
    int sidecounter = 0;
    Vint2 fixedpos(20, 20);
    TTF_Font* font = TTF_OpenFont("../Fonts/Rock.ttf", 15);
    SDL_Color col;
    col.r = 255;
    col.g = 0;
    col.b = 0;
    col.a = 255;
    Vint2 centroid_P;
    TEXTURE centroid_T("../Images/point_red.jpg");
    centroid_T.setren(win.getren());
    centroid_T.load();
    centroid_T.queryF();
    TEXTURE center_text;
    center_text.setren(win.getren());
    center_text.surfcpy(TTF_RenderText_Blended(font, "center", col));
    center_text.queryF();
    SDL_Init(SDL_INIT_AUDIO);
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 4, 4096) < 0)
    {
        cout<<" MIXER FAILED: "<<SDL_GetError()<<endl;
    }
    Mix_Chunk* Controls = Mix_LoadWAV("../Audio/Controls_long.wav");
    if(!Controls)
    {
        cout<<" Chunk error: "<<SDL_GetError()<<endl;
    }
    Mix_PlayChannelTimed(-1, Controls, 0, -1);
    while(event.type != SDL_QUIT)
    {
    	//int framestart = SDL_GetTicks();
    	double angle = 0;
    	static int i = 0;
        SDL_PollEvent(&event);
        int x, y;
        SDL_GetMouseState(&x, &y);
        mousepos.getx() = float(x);
        mousepos.gety() = float(y);
        char str[9] = {'P', 'o', 'i', 'n', 't', ' '};
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
                case 1:
                {
                	ver.push_back(Vint2(mousepos.getx(), mousepos.gety()));
                    ims.push_back(TEXTURE());
                    bds.push_back(TEXTURE());
                    //fonts.push_back(FONT("../Fonts/Rock.ttf", 15, 0, 100, 255, 255));
                    strcat(str, strmap::to_cc_str(ver.size()));
                    strs.push_back(" Point " + strmap::to_str(ver.size()));
                    break;
                }
                default: break;
            }
            case SDL_KEYDOWN:
            {
                if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])return 0;
                if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])
				{
					ver.erase(ver.begin(), ver.end());
					ims.erase(ims.begin(), ims.end());
                    bds.erase(bds.begin(), bds.end());
                    strs.erase(strs.begin(), strs.end());
				}
                if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])angle++;
                if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])angle--;
            }
            default: break;
        }
        rotate_rC(ver, angle, &mousepos);
        for(int i = 0; i < ver.size(); i++)
        {
        	if(i >= 0) //control condition (to be updated later)
			{
				ims[i].setren(win.getren());
        		bds[i].setren(win.getren());
        		ims[i].load("../Images/point.jpg");
        		ims[i].queryF();
        		ims[i].set_dstpos(ver[i].getx(), ver[i].gety());
        		ims[i].set_dstdim((ver[i] - ver[i != ver.size() - 1 ? i + 1 : 0]).getmag(), ims[i].getdst().h);
        		ims[i].setangle(-1 * angler(ver[i], ver[i != ver.size() - 1 ? i + 1 : 0]));
        		bds[i].surfcpy(TTF_RenderText_Blended(font, strs[i].c_str(), col));
	            bds[i].queryF();
	            bds[i].set_dstpos(ver[i].getx(), ver[i].gety());
                bds[i].setflip(SDL_FLIP_NONE);
	        }
            ims[i].drawC();
            bds[i].drawC();
        }
        /*
        if(ver.size() >= 3)
        {
			centroid_P = C_x_y_find(ver);
        	center_text.set_dstpos(centroid_P.getx(), centroid_P.gety());
        	centroid_T.set_dstpos(centroid_P.getx(), centroid_P.gety());
        	centroid_T.setflip(SDL_FLIP_NONE);
        	centroid_T.drawC();
        	center_text.drawC();        	
        }
        */
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
    SDL_Quit();
}
