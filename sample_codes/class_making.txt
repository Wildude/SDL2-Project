#include "../Files/Headers/BSDLF.h"
int main(int arn, char** args)
{
    WINDOW w;
    TEXTURE t;
    FONT f;
    t.crtren(w.crtwin());
    t.surfcpy(f.blended_render("ROCK AND ROLL"));
    t.draw();
    SDL_Delay(1000);
}