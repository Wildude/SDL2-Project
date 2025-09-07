#include "../include/renderer.hpp"
#include <cmath>
RENDERER::RENDERER()
{
    renderer = NULL;
    col.r = col.g = col.b = col.a = 0;
    flag = SDL_RENDERER_ACCELERATED;
    index = -1;
}
void RENDERER::setflag(Uint32 flag_ )
{
    flag = flag_;
}
void RENDERER::pst()
{
    return SDL_RenderPresent(renderer);
}
int RENDERER::clr()
{
    return SDL_RenderClear(renderer);
}
SDL_Renderer* RENDERER::getren() const
{
    return renderer;
}
SDL_Renderer* RENDERER::setren(SDL_Renderer* rend )
{
    renderer = rend;
    return renderer;
}
SDL_Renderer* RENDERER::setRGB(Uint8 r , Uint8 g , Uint8 b , Uint8 a )
{
    col.r = r;
    col.g = g;
    col.b = b;
    col.a = a;
    return renderer;
}
int RENDERER::pstcol(SDL_Color* color )
{
    SDL_Color colr = (color ? *color : col);
    return pstcol(colr.r, colr.g, colr.b, colr.a);
}
int RENDERER::pstcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Color col = {r, g, b, a};
    int ret = set_rencol(&col);
    clr();
    pst();
    return ret;
}
SDL_Renderer* RENDERER::setcol(SDL_Color& color)
{
    setRGB(color.r, color.g, color.b, color.a);
    return renderer;
}
int RENDERER::set_rencol(SDL_Color*col_p )
{
    SDL_Color color = (col_p ? *col_p : col);
    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
SDL_Renderer* RENDERER::crt(SDL_Window* window_ )
{
    return crtren(window_, index, flag);
}
SDL_Renderer* RENDERER::crtren(SDL_Window* window_ , int index_ , Uint32 flag_ )
{
    renderer = SDL_CreateRenderer((window_), index_, flag_);
    return renderer;
}
void RENDERER::drawline(const SDL_Point& v1, const SDL_Point& v2)
{
    SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
}
void RENDERER::drawrect(const SDL_Rect& cam)
{
    SDL_RenderDrawRect(renderer, &cam);   
}
// filled rectangle and point remaining
int setRenCol(SDL_Renderer* renderer, const SDL_Color& col){
    return SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
}
int setRenCol(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
// color manipulations:
SDL_Color brightenColor(const SDL_Color& color, float intensity) {
    intensity = clamp(intensity, 0.0f, 1.0f);
    SDL_Color result;
    result.r = static_cast<Uint8>(clamp(color.r + (255 - color.r) * intensity, 0.0f, 255.0f));
    result.g = static_cast<Uint8>(clamp(color.g + (255 - color.g) * intensity, 0.0f, 255.0f));
    result.b = static_cast<Uint8>(clamp(color.b + (255 - color.b) * intensity, 0.0f, 255.0f));
    result.a = color.a; // Preserve alpha
    return result;
}
SDL_Color greenToRed(const SDL_Color& color, float t ) {
    t = clamp(t, 0.0f, 1.0f);
    SDL_Color result;
    result.r = color.g * t;
    result.g = color.r * t;
    result.b = color.b;                                
    result.a = color.a;                                  
    return result;
}
SDL_Color darken(const SDL_Color& color, float t ){
    float brightness = (color.r + color.g + color.b) / 3.0f;
    SDL_Color result;
    result.r = static_cast<Uint8>((1.0f - t) * color.r + t * brightness + 0.5f);
    result.g = static_cast<Uint8>((1.0f - t) * color.g + t * brightness + 0.5f);
    result.b = static_cast<Uint8>((1.0f - t) * color.b + t * brightness + 0.5f);
    result.a = color.a;
    return result;
}
SDL_Color addGreyTint(const SDL_Color& color, float t) {
    // Clamp t between 0 and 1
    t = clamp(t, 0.0f, 1.0f);

    Uint8 grey = 128; // You can change this to any grey level

    SDL_Color result;
    result.r = static_cast<Uint8>((1.0f - t) * color.r + t * grey + 0.5f);
    result.g = static_cast<Uint8>((1.0f - t) * color.g + t * grey + 0.5f);
    result.b = static_cast<Uint8>((1.0f - t) * color.b + t * grey + 0.5f);
    result.a = color.a; // Preserve alpha

    return result;
}
// Draw thick line between (x1, y1) and (x2, y2)
void DrawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = sqrtf(dx * dx + dy * dy);
    float nx = -dy / len * thickness / 2.0f;
    float ny = dx / len * thickness / 2.0f;

    SDL_Vertex verts[4] = {
        {{x1 + nx, y1 + ny}, {255, 0, 0, 255}, {0, 0}},
        {{x1 - nx, y1 - ny}, {255, 0, 0, 255}, {0, 0}},
        {{x2 - nx, y2 - ny}, {255, 0, 0, 255}, {0, 0}},
        {{x2 + nx, y2 + ny}, {255, 0, 0, 255}, {0, 0}}
    };

    int indices[6] = {0, 1, 2, 0, 2, 3};

    SDL_RenderGeometry(renderer, nullptr, verts, 4, indices, 6);
}
void drawHorizontalLine(SDL_Renderer* renderer, int x1, int x2, int y) {
    if (x1 > x2) std::swap(x1, x2);
    SDL_RenderDrawLine(renderer, x1, y, x2, y);
}

void fillFlatBottomTriangle(SDL_Renderer* renderer, SDL_Point v0, SDL_Point v1, SDL_Point v2) {
    float invslope1 = (float)(v1.x - v0.x) / (v1.y - v0.y);
    float invslope2 = (float)(v2.x - v0.x) / (v2.y - v0.y);

    float curx1 = v0.x;
    float curx2 = v0.x;

    for (int y = v0.y; y <= v1.y; ++y) {
        drawHorizontalLine(renderer, (int)curx1, (int)curx2, y);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void fillFlatTopTriangle(SDL_Renderer* renderer, SDL_Point v0, SDL_Point v1, SDL_Point v2) {
    float invslope1 = (float)(v2.x - v0.x) / (v2.y - v0.y);
    float invslope2 = (float)(v2.x - v1.x) / (v2.y - v1.y);

    float curx1 = v2.x;
    float curx2 = v2.x;

    for (int y = v2.y; y > v0.y; --y) {
        drawHorizontalLine(renderer, (int)curx1, (int)curx2, y);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void fillTriangle(SDL_Renderer* renderer, SDL_Point p0, SDL_Point p1, SDL_Point p2) {
    // Sort points by Y (ascending)
    if (p0.y > p1.y) std::swap(p0, p1);
    if (p0.y > p2.y) std::swap(p0, p2);
    if (p1.y > p2.y) std::swap(p1, p2);

    if (p1.y == p2.y) {
        // Flat-bottom triangle
        fillFlatBottomTriangle(renderer, p0, p1, p2);
    }
    else if (p0.y == p1.y) {
        // Flat-top triangle
        fillFlatTopTriangle(renderer, p0, p1, p2);
    }
    else {
        // General triangle: split into two
        int splitX = p0.x + (float)(p2.x - p0.x) * (p1.y - p0.y) / (float)(p2.y - p0.y);
        SDL_Point split = { splitX, p1.y };
        fillFlatBottomTriangle(renderer, p0, p1, split);
        fillFlatTopTriangle(renderer, p1, split, p2);
    }
}