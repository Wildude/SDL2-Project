#include <uicontainer.hpp>
#include <uitab.hpp>
#include <uibutton.hpp>
#include <uislider.hpp>
#include <uitextswitch.hpp>
#include <uicommand.hpp>
#include <uilabel.hpp>
#include <TextBox.hpp>
#include <window.hpp>
#include <InputManager.hpp>
//
template <class T>
struct pair{
    T first, second;
    pair(const T& fir, const T& sec): first(fir), second(sec) {}
    pair(T* fir, T* sec) : first(*fir), second(*sec) {}
};
template <class T>
struct twin{
    T* first, second;
    twin(const T& fir, const T& sec): first(fir), second(sec) {}
    twin(T* fir, T* sec) : first(*fir), second(*sec) {}
};
template <class T>
struct dual{
    T& first, second;
    dual(T& fir, T& sec): first(fir), second(sec) {}
    dual(T* fir, T* sec) : first(*fir), second(*sec) {}
};
typedef pair<SDL_Color> ColPair;
WINDOW win("UI2_element test");
std::vector<FONT> fntPool;
std::vector<ColPair> colPool;
//
std::vector<UIcontainer> contPool;
    std::vector<UItab> tbPool;
    std::vector<UIbutton> btnPool;
    std::vector<UIslider> sldrPool;
    std::vector<UItextswitch> txtswchPool;
    std::vector<UIlabel> lblPool;
    //
std::vector<UIColor> colcmdPool;
    std::vector<UIFont> fntcmdPool;
    std::vector<UIMultiCommand> mltcmdPool;
    //
    InputManager input;
int main(int argn, char** args){
    win.crtB();
    //win.pstcol(0, 0, 255, 255);
    //
    colPool.push_back(ColPair({0, 0, 0, 255}, {255, 0, 255, 255}));
    colPool.push_back(ColPair({255, 0, 0, 125}, {0, 0, 255, 255}));
    //
    fntPool.push_back(FONT(FNT_ROCK, 20));
    fntPool.push_back(FONT(FNT_ROCKB, 20));
    //
    lblPool.push_back(UIlabel("testLabel", &fntPool.front()));
    //
    lblPool.front().setfg(colPool.back().first);
    lblPool.front().setbg(colPool.back().second);
    lblPool.front().setPos(win.getw()/2, win.geth()/2);
    lblPool.front().getBox()->border = 10;
    lblPool.front().getBox()->padding = 5;
    SDL_Point point;
    //
    colcmdPool.push_back(UIColor(colPool.back().first, colPool.back().second));
    colcmdPool.push_back(UIColor(colPool.front().first, colPool.front().second));
    //
    fntcmdPool.push_back(FONT(FNT_ROCKB, 20));
    fntcmdPool.push_back(FONT(FNT_ROCK, 20));
    //
    int drawtype = 0;
    TextBox dtype("drawtype: 0", fntPool.front()), boolstats("", fntPool.front());
    dtype.setboxpos(0, 0);
    boolstats.setboxpos(0, boolstats.getBox().h);
    while(!input.shouldQuit()){
        input.update();
        SDL_GetMouseState(&point.x, &point.y);
        //
        if(input.isMouseDown(SDL_BUTTON_RIGHT)){
            lblPool.front().setPos(point.x, point.y);
        }
        if(input.isKeyPressed(SDL_SCANCODE_DOWN)){
            lblPool.front().getBox()->padding--;
        }
        if(input.isKeyPressed(SDL_SCANCODE_UP)){
            lblPool.front().getBox()->padding++;
        }
        if(input.isKeyPressed(SDL_SCANCODE_LEFT)){
            lblPool.front().getBox()->border--;
        }
        if(input.isKeyPressed(SDL_SCANCODE_RIGHT)){
            lblPool.front().getBox()->border++;
        }
        if(input.isKeyPressed(SDL_SCANCODE_W)){
            drawtype++;
            dtype.settext("drawtype: " + std::to_string(drawtype));
        }
        if(input.isKeyPressed(SDL_SCANCODE_S)){
            drawtype--;
            dtype.settext("drawtype: " + std::to_string(drawtype));
        }
        lblPool.front().update(input);
        boolstats.settext(
            "hv: " + std::to_string(lblPool.front().gethover()) + ", " +
            "ck: " + std::to_string(lblPool.front().getclick()) + ", " +
            "fs: " + std::to_string(lblPool.front().getfocus()) + ", " +
            "rt: " + std::to_string(lblPool.front().getrevert()) + ", " +
            "st: " + std::to_string(lblPool.front().getstate()) 
        );
        if(lblPool.front().getstate()){
            system("cls");
            std::cout << " state changed\n";
            if(lblPool.front().getclick())
            {
                std::cout << " click detected\n";
                colcmdPool.front().execute(&lblPool.front());
            }
            else if(lblPool.front().getfocus()){
                std::cout << " focus detected\n";
                fntcmdPool.front().execute(&lblPool.front());
            }
            else if(lblPool.front().getrevert()){
                colcmdPool.back().execute(&lblPool.front());
                fntcmdPool.back().execute(&lblPool.front());
            }
        }
        boolstats.draw(win.getren(), NULL);
        dtype.draw(win.getren(), NULL);
        lblPool.front().render(win.getren(), drawtype);
        win.pst();
        win.clr();
        SDL_Delay(33);
    }
    return 0;
}
