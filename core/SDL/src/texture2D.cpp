#include <texture2D.hpp>
#include <cstring>
std::ofstream texture_file("texfile.log");
Texture2D::Texture2D(){
    // renderer = NULL;
    INIT();
}
Texture2D::Texture2D(const Texture2D& t){
    *this = t;
}
void Texture2D::copy(const Texture2D& t, SDL_Renderer* rend){
    setpath(t.path);
    load(NULL, rend);
}
Texture2D::Texture2D(const char* filepath, SDL_Renderer* ren)
{
    //std::cout<<" contructor called for textures\n";
    texture = NULL;
    // renderer = NULL;
    INIT();
    setpath(filepath);
    load(filepath, ren);
}
const Texture2D& Texture2D::operator=(const Texture2D& t)
{
    //std::cout<<" assignment called for font\n";
    if(this != &t){
        texture = t.texture;
        // renderer = t.renderer;
        src = t.src;
        dst = t.dst;
        center = t.center;
        // flip = t.flip;
        path = t.path;
        // angle = t.angle;
        return *this;
    }
}
Texture2D::Texture2D(SDL_Surface* surf, SDL_Renderer* rend){
    texture = NULL;
    // renderer = NULL;
    INIT();
    surfcpy(surf, rend);
}
SDL_Renderer* Texture2D::crtren(SDL_Window* win , int index , Uint32 flag )
{
    // renderer = crtren(win, index, flag);
    return NULL; //renderer;
}
SDL_Renderer* Texture2D::getren() const
{
    return NULL;// renderer;
}
void Texture2D::setangle(double angle_)
{
    //angle = angle_;
}
double Texture2D::getangle()
{
    return -1.99999999999999F;// angle;
}
void Texture2D::displayf(std::ofstream& out)
{
    out<<" Texture condition: "<<(texture ? "alive\n": "dead\n");
    //out<<" Renderer condition: "<<(renderer ?  "alive\n": "dead\n");
    //out<<" angle: "<<angle<<std::endl;
    out<<" src_pos(x, y): "<<src.x<<','<<src.y<<std::endl;
    out<<" src_dim(w, h): "<<src.w<<','<<src.h<<std::endl;
    out<<" dst_pos(x, y): "<<dst.x<<','<<dst.y<<std::endl;
    out<<" dst_dim(w, h): "<<dst.w<<','<<dst.h<<std::endl;
    out<<" center(x, y): "<<center.x<<','<<center.y<<std::endl;
    //out<<" flipstate: "<<flip<<std::endl;
}
void Texture2D::display(std::ostream& os )
{
    os<<" Texture condition: "<<(texture ? "alive\n": "dead\n");
    //os<<" Renderer condition: "<<(renderer ?  "alive\n": "dead\n");
    //os<<" angle: "<<angle<<std::endl;
    os<<" src_pos(x, y): "<<src.x<<','<<src.y<<std::endl;
    os<<" src_dim(w, h): "<<src.w<<','<<src.h<<std::endl;
    os<<" dst_pos(x, y): "<<dst.x<<','<<dst.y<<std::endl;
    os<<" dst_dim(w, h): "<<dst.w<<','<<dst.h<<std::endl;
    os<<" center(x, y): "<<center.x<<','<<center.y<<std::endl;
    // os<<" flipstate: "<<flip<<std::endl;
}
const SDL_FPoint& Texture2D::getcenter()
{
    return center;
}
SDL_Texture* Texture2D::gettexture()
{
    return texture;
}
Texture2D::~Texture2D()
{
    if(texture)SDL_DestroyTexture(texture);
    if(path)delete[] path;
}
void Texture2D::setflip(const SDL_RendererFlip& flag_)
{
    // flip = flag_;
}
const char* Texture2D::setpath(const char* fpath)
{
    //std::cout<<" setting path: "<<filepath<<std::endl;
    if(fpath){
        if(path && strcmp(fpath, path) == 0)return path; // no change
        if(path)delete[] path;
        path = new char[strlen(fpath) + 1];
        strcpy(path, fpath);
    }
    else{
        if(path)delete[] path;
        path = NULL;
        delTex();
    }
}
const char* Texture2D::getpath()
{
    return path;
}
int Texture2D::INIT()
{
    return (SDL_WasInit(SDL_INIT_VIDEO) ? SDL_WasInit(SDL_INIT_VIDEO) : SDL_Init(SDL_INIT_VIDEO));
}
const SDL_Rect& Texture2D::set_srcpos(int x , int y )
{
    src.x = x;
    src.y = y;
    return src;
}
const SDL_Rect& Texture2D::set_srcdim(int w, int h)
{
    src.w = w;
    src.h = h;
    return src;
}
const SDL_FRect& Texture2D::set_dstpos(float x , float y )
{
    dst.x = x;
    dst.y = y;
    return dst;
}
SDL_FPoint Texture2D::get_cenpos(){ // no optimization
    SDL_FPoint point = {dst.x + center.x, dst.y + center.y};
    return point;
}
const SDL_FRect& Texture2D::set_cenpos(float x , float y )
{
    return set_dstpos(x - center.x, y - center.y);
}
const SDL_FRect& Texture2D::set_dstdim(int w , int h )
{
    dst.w = (w ? w : dst.w);
    dst.h = (h ? h : dst.h);
    return dst;
}
void Texture2D::magnify(float w , float h ){
    h = (h <= 0 ? w : h);
    dst.w *= w;
    dst.h *= h;
    setcenter(center.x * w, center.y * h);
}
const SDL_Rect& Texture2D::set_src(int w, int h, float x , float y )
{
    src.w = w;
    src.h = h;
    if(x > -1)src.x = x;
    if(y > -1)src.y = y;
    return src;
}
const SDL_FRect& Texture2D::set_dst(int w, int h, float x , float y )
{
    dst.w = w;
    dst.h = h;
    if(x > -1)dst.x = x;
    if(y > -1)dst.y = y;
    return dst;
}
const SDL_Rect& Texture2D::set_src(const SDL_Rect& src_)
{
    src = src_;
    return src;
}
const SDL_FRect& Texture2D::set_dst(const SDL_FRect& dst_)
{
    dst = dst_;
    return dst;
}
SDL_FRect& Texture2D::getdst() // const
{
    return dst;
}
SDL_Rect& Texture2D::getsrc() // const
{
    return src;
}
const SDL_FRect& Texture2D::getdst() const
{
    return dst;
}
const SDL_Rect& Texture2D::getsrc() const
{
    return src;
}
SDL_Rect Texture2D::retquery() // no optimization
{
    SDL_Rect ret;
    queryR(&ret);
    return ret;
}
const SDL_FPoint& Texture2D::setcenter(float x, float y)
{
    center.x = x;
    center.y = y;
    return center;
}
const SDL_FPoint& Texture2D::setcenter()
{
    return setcenter(dst.w/2, dst.h/2);
}
int Texture2D::query(int* w , int * h )
{
    return SDL_QueryTexture(texture, NULL, NULL, (w ? w : &src.w), (h ? h : &src.h));
}
int Texture2D::queryR(SDL_Rect* src_ )
{
    setcenter();
    return query((src_ ? &(src_->w) : &src.w), (src_ ? &(src_->h) : &src.h));
}
void Texture2D::delTex(){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}
SDL_Texture* Texture2D::load(const char* filepath, SDL_Renderer* rend)
{
    delTex();
    texture = IMG_LoadTexture((rend), filepath ? filepath : path);
    if(!texture)texture_file << " Error loading texture: " << SDL_GetError() << std::endl;
    return texture;
}
SDL_Texture* Texture2D::surfcpy(SDL_Surface*& surf, SDL_Renderer* rend)
{
    texture = SDL_CreateTextureFromSurface((rend), surf);
    return texture;
}
int Texture2D::rencpy(SDL_Renderer* rend, SDL_FRect* dst_ , SDL_Rect* src_ , SDL_RendererFlip flag , SDL_FPoint* center_ , double angle )
{
    return SDL_RenderCopyExF(rend, texture, (src_ ? src_ : &src), (dst_ ? dst_ : &dst), angle, (center_ ? center_ : &center), flag);
}
int Texture2D::queryF()
{
    if(query() < 0){return -2;}
    set_srcpos();
    set_dstpos();
    set_dstdim(src.w, src.h);
    setcenter();
    return 1;
}
int Texture2D::queryC(){
    if(queryR() < 0){return -2;}
    set_dstdim();
    setcenter();
    return 1;
}
int Texture2D::queryN(){
    return SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
}
int Texture2D::drawRect(const SDL_Rect& rect, SDL_Renderer* rend, int ptsize ){
    if(ptsize <= 1){
        SDL_RenderDrawRect(rend, &rect);
    }
    SDL_Rect lines[4] = {
        {rect.x - ptsize/2, rect.y - ptsize/2, rect.w + ptsize, ptsize},
        {rect.x - ptsize/2, rect.y - ptsize/2, ptsize, rect.h + ptsize},
        {rect.x - ptsize/2, rect.y + rect.h - ptsize/2, rect.w + ptsize, ptsize},
        {rect.x + rect.w - ptsize/2, rect.y - ptsize/2, ptsize, rect.h + ptsize}
    };
    for(int i = 0; i < 4; i++){
        SDL_RenderFillRect(rend, &lines[i]);
    }
}
int Texture2D::drawRectP(const SDL_Rect& rect, SDL_Renderer* rend, int ptsize ){
    if(ptsize == 1){
        SDL_RenderDrawRect(rend, &rect);
    }
    SDL_Rect lines[4] = {
        {rect.x - ptsize/2, rect.y - ptsize/2, rect.w + ptsize, ptsize},
        {rect.x - ptsize/2, rect.y + ptsize/2, ptsize, rect.h},
        {rect.x + ptsize/2, rect.y + rect.h - ptsize/2, rect.w, ptsize},
        {rect.x + rect.w - ptsize/2, rect.y + ptsize/2, ptsize, rect.h}
    };
    for(int i = 0; i < 4; i++){
        SDL_RenderFillRect(rend, &lines[i]);
    }
}
// don't use
int Texture2D::drawPX(SDL_Renderer* rend, SDL_FRect* rect , float scale ){
    SDL_FRect* drawRect = (rect ? new SDL_FRect({dst.x - (bool)(dst.x/(rect->w * scale)) * (rect->w * scale) , dst.y - (int)(dst.y/(rect->h * scale)) * (rect->h * scale), dst.w * scale, dst.h * scale}) : new SDL_FRect({dst.x, dst.y, dst.w * scale, dst.h * scale}));
    return drawC(rend, drawRect);
}
int Texture2D::drawOF(SDL_Renderer* rend, SDL_FRect* rect , float scale , double angle ){
    SDL_FPoint c = {getcenter().x * scale, getcenter().y * scale};
    SDL_FRect* drawRect = (rect ? new SDL_FRect({dst.x - rect->x - (c.x - getcenter().x), dst.y - rect->y - (c.y - getcenter().y), dst.w * scale, dst.h * scale}) : new SDL_FRect({dst.x, dst.y, dst.w * scale, dst.h * scale}));
    return drawC(rend, drawRect, angle);
}
int Texture2D::drawC(SDL_Renderer* rend, SDL_FRect* rect , double angle , SDL_RendererFlip flip )
{
    if(rencpy(rend, rect, NULL, flip, NULL, angle) < 0)return -3;
    return 1;
}
int Texture2D::drawO(SDL_Renderer* rend, SDL_FRect* rect , SDL_RendererFlip flip )
{
    if(rencpy(rend, rect, NULL, flip, &center, 0) < 0)return -3;
    SDL_RenderPresent(rend);
    return 1;
}
int Texture2D::drawI(const char* filepath, SDL_Renderer* rend, bool clrer , SDL_FRect* rect , SDL_RendererFlip flip )
{
    if(!load(filepath, rend)){return -1;}
    if(queryR() < 0){return -2;}
    set_srcpos();
    set_dstpos();
    set_dstdim();
    setcenter();
    if(rencpy(rend, (rect ? rect : &dst), NULL, flip, &center, 0) < 0)return -3;
    SDL_RenderPresent(rend);
    if(clrer)if(SDL_RenderClear(rend) < 0) return -4;
    return 1;
}
int Texture2D::draw(SDL_Renderer* rend, SDL_FRect* rect , bool clrer , SDL_RendererFlip flip )
{
    if(queryR() < 0){return -1;}
    set_srcpos();
    set_dstpos();
    set_dstdim();
    setcenter();
    if(rencpy(rend, (rect ? rect : &dst), NULL, flip, &center, 0) < 0)return -2;
    SDL_RenderPresent(rend);
    if(clrer)if(SDL_RenderClear((rend)) < 0) return -3;
    return 1;
}
int Texture2D::drawRect(SDL_Rect rect){

}
//
//
SDLImage::SDLImage() : texture(NULL), w(0), h(0) {}
SDLImage::SDLImage(const char* path, SDL_Renderer* rend){
    texture = IMG_LoadTexture(rend, path);
    if(!texture){
        std::cout << " IMGLoad error: " << IMG_GetError() << std::endl;
        w = 0; h = 0;
        return;
    }
    queryF();
}
SDLImage::SDLImage(SDL_Texture* tex): texture(tex){
    if(texture)queryF();
    else {
        w = 0;
        h = 0;
    }
}
SDLImage::SDLImage(const SDLImage& other): texture(other.texture), w(other.w), h(other.h) {}
SDLImage& SDLImage::operator=(const SDLImage& other){
    if(this != &other){
        texture = other.texture;
        w = other.w;
        h = other.h;
    }
    return *this;
}
void SDLImage::load(const char* path, SDL_Renderer* rend){
    delTex();
    texture = IMG_LoadTexture(rend, path);
    if(!texture){
        std::cout << " IMGLoad error: " << IMG_GetError() << std::endl;
        w = 0; h = 0;
        return;
    }
    queryF();
}
void SDLImage::load(SDL_Texture* tex){
    delTex();
    texture = tex;
    queryF();
}
SDL_Texture* SDLImage::gettex() const {
    return texture;
}
int SDLImage::query(int& wd, int& hd) const {
    return SDL_QueryTexture(texture, NULL, NULL, &wd, &hd);
}
int SDLImage::queryF(){
    return SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}
void SDLImage::draw(const SDL_Rect& dst, const SDL_Rect& src, SDL_Renderer* rend){
    SDL_RenderCopy(rend, texture, &src, &dst);
}
void SDLImage::drawSRC(const SDL_Rect& src, SDL_Renderer* rend){
    SDL_Rect dst = {0, 0, w, h};
    SDL_RenderCopy(rend, texture, &src, &dst);
}
void SDLImage::drawDST(const SDL_Rect& dst, SDL_Renderer* rend){
    SDL_RenderCopy(rend, texture, NULL, &dst);
}
void SDLImage::drawSRCpos(const SDL_Point& src, SDL_Renderer* rend){
    SDL_Rect srcrect = {src.x, src.y, w, h};
    SDL_Rect dst = {0, 0, w, h};
    SDL_RenderCopy(rend, texture, &srcrect, &dst);
}
void SDLImage::drawDSTpos(const SDL_Point& dst, SDL_Renderer* rend){
    SDL_Rect dstrect = {dst.x, dst.y, w, h};
    SDL_RenderCopy(rend, texture, NULL, &dstrect);
}
void SDLImage::drawSRCdim(const SDL_Point& src, SDL_Renderer* rend){
    SDL_Rect srcrect = {0, 0, src.x, src.y};
    SDL_Rect dst = {0, 0, w, h};
    SDL_RenderCopy(rend, texture, &srcrect, &dst);
}
void SDLImage::drawDSTdim(const SDL_Point& dst, SDL_Renderer* rend){
    SDL_Rect dstrect = {0, 0, dst.x, dst.y};
    SDL_RenderCopy(rend, texture, NULL, &dstrect);
}
void SDLImage::drawSRCp(int x, int y, SDL_Renderer* rend){
    SDL_Rect srcrect = {x, y, w, h};
    SDL_Rect dst = {0, 0, w, h};
    SDL_RenderCopy(rend, texture, &srcrect, &dst);
}
void SDLImage::drawDSTp(int x, int y, SDL_Renderer* rend){
    SDL_Rect dstrect = {x, y, w, h};
    SDL_RenderCopy(rend, texture, NULL, &dstrect);
}
void SDLImage::drawSRCd(int x, int y, SDL_Renderer* rend){
    SDL_Rect srcrect = {0, 0, x, y};
    SDL_Rect dst = {0, 0, w, h};
    SDL_RenderCopy(rend, texture, &srcrect, &dst);
}
void SDLImage::drawDSTd(int x, int y, SDL_Renderer* rend){
    SDL_Rect dstrect = {0, 0, x, y};
    SDL_RenderCopy(rend, texture, NULL, &dstrect);
}
void SDLImage::drawSRCpd(int x, int y, int wd, int hd, SDL_Renderer* rend){
    SDL_Rect srcrect = {x, y, wd, hd};
    SDL_Rect dst = {0, 0, w, h};
    SDL_RenderCopy(rend, texture, &srcrect, &dst);
}
void SDLImage::drawDSTpd(int x, int y, int wd, int hd, SDL_Renderer* rend){
    SDL_Rect dstrect = {x, y, wd, hd};
    SDL_RenderCopy(rend, texture, NULL, &dstrect);
}
void SDLImage::draw(SDL_Renderer* rend){
    SDL_Rect dstrect = {0, 0, w, h};
    SDL_RenderCopy(rend, texture, NULL, &dstrect);
}
SDLImage::~SDLImage(){
    delTex();
}