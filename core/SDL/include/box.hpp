#pragma once
#include <SDL2/SDL.h>
#include <iostream>
class Box {
    SDL_Rect contentRect;      // Position and size of the actual content (text/image/button)
    SDL_Rect padding; // Space around content (inside the border)
    SDL_Rect border; // Border thickness (around the padding)
    SDL_Rect margin; // margin
    // ---------------------------------------------
    // x - left, y - top, w - right, h - bottom
    // ---------------------------------------------
    // Optional: Colors or styles
    SDL_Color borderColor; // Color of the border
    SDL_Color backgroundColor; // Background color of the content area
    void updatebox();
    public:
    // Anchor/origin (e.g., top-left, center)
    enum Anchor { TOP_LEFT, CENTER, BOTTOM_RIGHT, TOP, BOTTOM, LEFT, RIGHT, TOP_RIGHT, BOTTOM_LEFT, CUSTOM};
    Anchor anchor = CENTER;
    Box();
    const Box& operator=(const Box& box);
    Box(const Box& box);
    Box(int x, int y, int w, int h);
    float padavgx();
    float padavgy();
    float padavg();
    float borderavgx();
    float borderavgy();
    float borderavg();
    float marginavgx();
    float marginavgy();
    float marginavg();
    void setanchor(Anchor Nanchor = CENTER);
    const SDL_Rect& getcontent();
    void setpos(SDL_Point point);
    void setpos(int x, int y);
    void setSize(int w, int h);
    void setpadding(int x = -1, int y = -1, int w = -1, int h = -1);
    void setborder(int x = -1, int y = -1, int w = -1, int h = -1);
    void setmargin(int x = -1, int y = -1, int w = -1, int h = -1);
    const SDL_Rect& getpadding();
    const SDL_Rect& getmargin();
    const SDL_Rect& getborder();
    // Final computed size including all layers
    SDL_Rect fullRect() const ;

    SDL_Rect paddingBox() const ;

    SDL_Rect borderBox() const ;

    SDL_Rect marginBox() const ;
};