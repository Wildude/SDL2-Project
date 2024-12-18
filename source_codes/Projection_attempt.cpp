//g++ -I../src/Include -L../src/Lib -o ../Executables/Projection_attempt.exe Projection_attempt.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    WINDOW win(" Projection attempt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    Vflt2* points = new Vflt2[4];
    points[0] = Vflt2(win.getw()/2 - 50, win.geth()/2 - 100);
    points[1] = Vflt2(win.getw()/2 + 50, win.geth()/2 - 100);
    points[2] = Vflt2(win.getw()/2 + 50, win.geth()/2 + 100);
    points[3] = Vflt2(win.getw()/2 - 50, win.geth()/2 + 100);
    //rotate_rC(points, 45, 4);
    SDL_Event event;
    double angle = 0;
    double distance = 200;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])angle++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])angle--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])distance--;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])distance++;
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE])angle = 0;
        //if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])anglexy = 0;
        //points = n_gonr(Vflt2(win.getw()/2, win.geth()/2), 4, 150, anglexy);
        TXT angleTxt(to_string(angle).c_str(), win.getren(), 14);
        angleTxt.board.set_dstpos(0, 0);
        angleTxt.board.drawC();
        TXT distTxt(to_string(distance).c_str(), win.getren(), 14);
        distTxt.board.set_dstpos(0, distTxt.board.getdst().h);
        distTxt.board.drawC();
        TEXTURE pts[4], pts2[4];
        Vflt2 points2[4];
        for(int i = 0; i < 4; i++){
            float z = (points[i].getx() - win.getw()/2) * sin(torad(angle));
            points2[i].getx() = (points[i].getx() - win.getw()/2) * cos(torad(angle));
            float scale = distance / (distance - z);
            points2[i].gety() = (points[i].gety() - win.geth()/2) * scale;
            points2[i].getx() += win.getw()/2;
            points2[i].gety() += win.geth()/2;
        }
        for(int i = 0; i < 4; i++){
            float mag_origin = (Vflt2(win.getw()/2, win.geth()/2) - points2[i]).getmag();
            double ang_origin = angle_bn(Vflt2(win.getw()/2, win.geth()/2), points2[i]);
            SDL_Surface* surf = SDL_CreateRGBSurface(0, 2, 2, 8, 0, 0, 0, 0);
            SDL_SetSurfaceColorMod(surf, 255, 0, 0);
            pts[i].setren(win.getren());
            pts[i].surfcpy(surf);
            pts[i].queryF();
            pts[i].set_cenpos(points2[i].getx(), points2[i].gety());
            //
            SDL_SetSurfaceColorMod(surf, 0, 0, 255);
            pts2[i].setren(win.getren());
            pts2[i].surfcpy(surf);
            pts2[i].queryF();
            pts2[i].set_cenpos(win.getw()/2, win.geth()/2);
            pts2[i].set_dstdim(mag_origin, 2);
            pts2[i].setangle(-ang_origin);
            pts2[i].drawC();
            //
            double anglebn = angle_bn(points2[i], points2[i < 3 ? i + 1 : 0]);
            double magnitude = (points2[i] - points2[i < 3 ? i + 1 : 0]).getmag();
            pts[i].set_dstdim(magnitude, 2);
            pts[i].setangle(-anglebn);
            pts[i].drawC();
            // save for later
            /*
            TTF_Font* font = TTF_OpenFont("../Fonts/nyala.ttf", 14);
            SDL_Color fg = {150, 150, 150};
            string the_text = string("p1(" + to_string(points[i].getx()) + ", " + to_string(points[i].gety()) + ")");
            SDL_Texture* board = SDL_CreateTextureFromSurface(win.getren(), TTF_RenderText_Blended(font, the_text.c_str(), fg));
            SDL_FRect rect = {points[i].getx(), points[i].gety(), 0, 0};
            TTF_SizeText(font, the_text.c_str(), reinterpret_cast<int*>(&rect.w), reinterpret_cast<int*>(&rect.h));
            SDL_RenderCopyF(win.getren(), board, NULL, &rect);
            */
            //
        }
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
}
/* GPT WAY
for(int i = 0; i < 4; i++){
            float z = points[i].getx() * sin(torad(angle));
            float scale = distance / (distance - z);
            points[i].getx() *= cos(torad(angle));
            points[i].gety() *= scale;
        }
        for(int i = 0; i < 4; i++){
            float mag_origin = (Vflt2(win.getw()/2, win.geth()/2) - points[i]).getmag();
            double ang_origin = angle_bn(Vflt2(win.getw()/2, win.geth()/2), points[i]);
            SDL_Surface* surf = SDL_CreateRGBSurface(0, 2, 2, 8, 0, 0, 0, 0);
            SDL_SetSurfaceColorMod(surf, 255, 0, 0);
            pts[i].setren(win.getren());
            pts[i].surfcpy(surf);
            pts[i].queryF();
            pts[i].set_cenpos(points[i].getx(), points[i].gety());
            //
            SDL_SetSurfaceColorMod(surf, 0, 0, 255);
            pts2[i].setren(win.getren());
            pts2[i].surfcpy(surf);
            pts2[i].queryF();
            pts2[i].set_cenpos(win.getw()/2, win.geth()/2);
            pts2[i].set_dstdim(mag_origin, 2);
            pts2[i].setangle(-ang_origin);
            pts2[i].drawC();
            //
            double anglebn = angle_bn(points[i], points[i < 3 ? i + 1 : 0]);
            double magnitude = (points[i] - points[i < 3 ? i + 1 : 0]).getmag();
            pts[i].set_dstdim(magnitude, 2);
            pts[i].setangle(-anglebn);
            pts[i].drawC();
            // save for later
            /*
            TTF_Font* font = TTF_OpenFont("../Fonts/nyala.ttf", 14);
            SDL_Color fg = {150, 150, 150};
            string the_text = string("p1(" + to_string(points[i].getx()) + ", " + to_string(points[i].gety()) + ")");
            SDL_Texture* board = SDL_CreateTextureFromSurface(win.getren(), TTF_RenderText_Blended(font, the_text.c_str(), fg));
            SDL_FRect rect = {points[i].getx(), points[i].gety(), 0, 0};
            TTF_SizeText(font, the_text.c_str(), reinterpret_cast<int*>(&rect.w), reinterpret_cast<int*>(&rect.h));
            SDL_RenderCopyF(win.getren(), board, NULL, &rect);
            //
            TXT ptTxt(string("p" + to_string(i)).c_str(), win.getren(), 14);
            ptTxt.board.set_dstpos(points[i].getx(), points[i].gety());
            ptTxt.board.drawC();
        }
*/