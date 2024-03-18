#include "../Files/Headers/BSDLF.h"
#include "../Files/Headers/vector2D.h"
int main(int arn, char** args)
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Chunk* gunshot = Mix_LoadWAV("../Audio/gunshot.wav");
    Mix_Chunk* empty = Mix_LoadWAV("../Audio/emptygun.wav");
    Mix_Chunk* reload = Mix_LoadWAV("../Audio/reload.wav");
    int fullclip = 30;
    int bullets = fullclip;
    Mix_AllocateChannels(4);
    char text[12];
    WINDOW win("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);
    FONT GUI_text("../Fonts/Rock.ttf", 20, 0, 255, 0, 255);
    win.crtB();
    TEXTURE board;
    board.setren(win.getren());
    win.pstcol(255, 255, 255, 255);
    int mag = 1;
    Vint2 pistol_pos(320, 240);
    Vint2 srcdim(127, 97);
    Vint2 center(65, 29);
    Vint2 dstpos(320, 240);
    Vint2 dstdim = srcdim * mag;
    TEXTURE gun;
    gun.setren(win.getren());
    gun.load("../Images/Uzi_sprite3.png");
    gun.queryF();
    SDL_Event event;
    Vint2 target;
    Vint2 angular;
    TEXTURE point, mousep;
    point.setren(win.getren());
    mousep.setren(win.getren());
    point.load("../Images/point_red.jpg");
    mousep.load("../Images/Crosshair_red.png");
    point.queryF();
    mousep.queryF();
    FONT controls("../Fonts/Rock.ttf", 20, 255, 0, 200, 255);
    const char* ctrls[4] = {"Arrow keys for movement", "Mouse for aim", "Left mouse button for shooting", "R for reload and ESC for quit"};
    TEXTURE howtos[4];
    for(int i = 0; i < 4; i++)
    {
        howtos[i].setren(win.getren());
        howtos[i].surfcpy(controls.blended_render(ctrls[i]));
        howtos[i].queryF();
        howtos[i].set_dstpos(640 - howtos[i].getdst().w, 480 - (i + 1) * howtos[i].getdst().h);
    }
    SDL_ShowCursor(SDL_DISABLE);
    while(event.type != SDL_QUIT)
    {
        bool shot = false;
        bool empt = false;
        bool relo = false;
        SDL_PollEvent(&event);
        Vint2 srcpos(1, 1);
        if(!bullets)srcpos.getx() += 2 * srcdim.getx();
        SDL_GetMouseState(&target.getx(), &target.gety());
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])dstpos.gety()-=5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])dstpos.gety()+=5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])dstpos.getx()-=5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])dstpos.getx()+=5;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_R])
        {
            relo = true;
            bullets = fullclip;
        }
        if(event.button.button == 1)
        {
            if(bullets > 0)
            {
                bullets--;
                srcpos.getx() += srcdim.getx();
                shot = true;
            }
            else
            {
                empt = true;
            }
        }
        string str = "Bullets: " + strmap::to_str(bullets);
        if(bullets >= 7)GUI_text.setcol1(0, 255, 0, 255);
        if(bullets < 7)GUI_text.setcol1(255, 200, 0, 255);
        if(bullets < 4)GUI_text.setcol1(255, 0, 0, 255);
        if(!board.surfcpy(GUI_text.blended_render(str.c_str())))
        {
        	cout<<" texture error: "<<SDL_GetError()<<endl;
        	return -1;
        }
        //board.load("../Images/Crosshair_black.png");
        board.queryF();
        mousep.set_dstpos(target.getx(), target.gety());
        gun.set_srcpos(srcpos.getx(), srcpos.gety());
        gun.set_srcdim(srcdim.getx(), srcdim.gety());
        gun.setcenter(center.getx(), center.gety());
        gun.set_cenpos(dstpos.getx(), dstpos.gety());
        gun.set_dstdim(dstdim.getx(), dstdim.gety());
        //cout<<" here:\n";
        point.set_dstpos(dstpos.getx(), dstpos.gety());
        point.set_dstdim((dstpos - target).getmag(), point.getdst().h);
        point.setangle(-1 * angler(dstpos, target));
        gun.setangle(-1 * angler(dstpos, target));
        if(target.getx() < dstpos.getx())
		{
			gun.setflip(SDL_FLIP_HORIZONTAL);
			gun.setangle(180 + -1 * angler(dstpos, target));
		}
		else gun.setflip(SDL_FLIP_NONE);
        gun.drawO();
        if(shot && !empt)Mix_PlayChannelTimed(0, gunshot, 0, 0.25);
        else if(empt)Mix_PlayChannelTimed(0, empty, 0, 0.25);
        else if(relo)Mix_PlayChannelTimed(0, reload, 0, 0.25);
        point.drawC();
        mousep.drawC();
        board.setflip(SDL_FLIP_NONE);
        board.drawC();
        for(int i = 0; i < 4; i++)
		{
			howtos[i].setflip(SDL_FLIP_NONE);
			howtos[i].drawC();
		}
        win.pst();
        win.clr();
        SDL_Delay(100);
    }
    SDL_Quit();
}
