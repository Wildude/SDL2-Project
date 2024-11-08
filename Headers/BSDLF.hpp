using namespace SDL2;
class EVENT
{
    SDL_Event event;
    public:
    EVENT()
    {
        SDL_PollEvent(&event);
    }
    int poll()
    {
        return SDL_PollEvent(&event);
    }
    Uint8 key(SDL_Scancode keypressed)
    {
        return SDL_GetKeyboardState(NULL)[keypressed];
    }
    bool mbn(int index)
    {
        return (event.button.button == index - 1);
    }
    /*
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
    // arrows
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]);
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]);
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]);
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]);
    // WASD
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W]);
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A]);
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S]);
    if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D]);
    // mouse button click
    if(event.button.button == 1); // left click
    if(event.button.button == 2); // middle click
    if(event.button.button == 3); // right click
    */
};
class WINDOW
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    string title;
    int x;
    int y;
    int w;
    int h;
    Uint32 flag;
    SDL_RendererFlip flip;
    SDL_Color col = {0, 0, 0, 0};
    public:
    SDL_Renderer* getren() const
    {
        return renderer;
    }
    SDL_Window* getwin() const
    {
        return window;
    }
    ~WINDOW()
    {
        SDL_DestroyWindow(window);
        if(renderer)SDL_DestroyRenderer(renderer);
    }
    WINDOW(const char* title_ = NULL, int x_ = SDL_WINDOWPOS_CENTERED, int y_ = SDL_WINDOWPOS_CENTERED, int w_ = 640, int h_ = 480, Uint32 flag_ = SDL_WINDOW_SHOWN)
    {
        INIT();
        setwin(title_, x_, y_, w_, h_, flag_);
        renderer = NULL;
    }
    int getx() {return x;}
    int gety() {return y;}
    int getw() {return w;}
    int geth() {return h;}
    string gettitle() {return title;}
    inline void pst()
    {
        return SDL2::pst(renderer);
    }
    inline int clr()
    {
        return SDL2::clr(renderer);
    }
    SDL_Renderer* setRGB(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0)
    {
        col.r = r;
        col.g = g;
        col.b = b;
        col.a = a;
        return renderer;
    }
    int pstcol(SDL_Color* color = NULL)
    {
        SDL_Color colr = (color ? *color : col);
        return pstcol(colr.r, colr.g, colr.b, colr.a);
    }
    int pstcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_Color col = {r, g, b, a};
        int ret = set_rencol(&col);
        clr();
        pst();
        return ret;
    }
    SDL_Renderer* setcol(const SDL_Color& color)
    {
        setRGB(color.r, color.g, color.b, color.a);
        return renderer;
    }
    int set_rencol(SDL_Color*col_p = NULL)
    {
        SDL_Color color = (col_p ? *col_p : col);
        return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_Renderer* crtren(SDL_Window* window_ = NULL, int index = -1, Uint32 flag = SDL_RENDERER_ACCELERATED)
    {
        renderer = SDL_CreateRenderer((window_ ? window_ : window), index, flag);
        return renderer;
    }
    static int INIT()
    {
        return (SDL_WasInit(SDL_INIT_VIDEO) ? SDL_WasInit(SDL_INIT_VIDEO) : SDL_Init(SDL_INIT_VIDEO));
    }
    void setwin(const char* title_ = NULL, int x_ = SDL_WINDOWPOS_CENTERED, int y_ = SDL_WINDOWPOS_CENTERED, int w_ = 640, int h_ = 480, Uint32 flag_ = SDL_WINDOW_SHOWN)
    {
        title = title_;
        x = x_;
        y = y_;
        w = w_;
        h = h_;
        flag = flag_;
    }
    int crtB()
    {
        crtwin(title.c_str(), x, y, w, h, flag);
        crtren();
        if(!window || !renderer)return 0;
        else return 1;
    }
    int crtBn()
    {
        crtwin();
        crtren();
        if(!window || !renderer)return 0;
        else return 1;
    }
    SDL_Window* crtwin(const char* title_ = NULL, int x_ = SDL_WINDOWPOS_CENTERED, int y_ = SDL_WINDOWPOS_CENTERED, int w_ = 640, int h_ = 480, Uint32 flag_ = SDL_WINDOW_SHOWN)
    {
        window = SDL_CreateWindow((const char*)(title_ ? title_ : title.c_str()), x_, y_, w_, h_, flag_);
        return window;
    }
    void setdim(int w_ = 640, int h_ = 480)
    {
        w = w_;
        h = h_;
    }
    void setpos(int x_ = SDL_WINDOWPOS_CENTERED, int y_ = SDL_WINDOWPOS_CENTERED)
    {
        x = x_;
        y = y_;
    }
    void setflag(Uint32 flag_ = SDL_WINDOW_SHOWN)
    {
        flag = flag_;
    }
};
class RENDERER
{
    SDL_Renderer* renderer;
    SDL_Color col;
    Uint32 flag;
    int index;
    public:
    RENDERER()
    {
        renderer = NULL;
        col.r = col.g = col.b = col.a = 0;
        flag = SDL_RENDERER_ACCELERATED;
        index = -1;
    }
    void setflag(Uint32 flag_ = SDL_RENDERER_TARGETTEXTURE)
    {
        flag = flag_;
    }
    void pst()
    {
        return SDL2::pst(renderer);
    }
    int clr()
    {
        return SDL2::clr(renderer);
    }
    SDL_Renderer* getren() const
    {
        return renderer;
    }
    SDL_Renderer* setren(SDL_Renderer* rend = NULL)
    {
        renderer = rend;
        return renderer;
    }
    SDL_Renderer* setRGB(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0)
    {
        col.r = r;
        col.g = g;
        col.b = b;
        col.a = a;
        return renderer;
    }
    int pstcol(SDL_Color* color = NULL)
    {
        SDL_Color colr = (color ? *color : col);
        return pstcol(colr.r, colr.g, colr.b, colr.a);
    }
    int pstcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_Color col = {r, g, b, a};
        int ret = set_rencol(&col);
        clr();
        pst();
        return ret;
    }
    SDL_Renderer* setcol(SDL_Color& color)
    {
        setRGB(color.r, color.g, color.b, color.a);
        return renderer;
    }
    int set_rencol(SDL_Color*col_p = NULL)
    {
        SDL_Color color = (col_p ? *col_p : col);
        return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_Renderer* crt(SDL_Window* window_ = NULL)
    {
        return crtren(window_, index, flag);
    }
    SDL_Renderer* crtren(SDL_Window* window_ = NULL, int index_ = -1, Uint32 flag_ = SDL_RENDERER_ACCELERATED)
    {
        renderer = SDL_CreateRenderer((window_), index_, flag_);
        return renderer;
    }
};
class TEXTURE
{
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    SDL_Rect src = {0, 0, 0, 0};
    SDL_FRect dst = {0, 0, 0, 0};
    SDL_FPoint center = {0, 0};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Color col = {0, 0, 0, 0};
    string path;
    char TYPE;
    double angle = 0;
    public:
    TEXTURE(){
        texture = NULL;
        renderer = NULL;
        surface = NULL;
        INIT();
    }
    void copy(const TEXTURE& t){
        setren(t.renderer);
        setpath(t.path.c_str());
        checkTYPE();
        load();
    }
    TEXTURE(const char* filepath, SDL_Renderer* ren)
    {
        //cout<<" contructor called for textures\n";
        texture = NULL;
        renderer = NULL;
        surface = NULL;
        setren(ren);
        INIT();
        setpath(filepath);
        checkTYPE();
        load();
    }
    const TEXTURE& operator=(const TEXTURE& t)
    {
        //cout<<" assignment called for font\n";
        if(this != &t){
            texture = t.texture;
            surface = t.surface;
            renderer = t.renderer;
            src = t.src;
            dst = t.dst;
            center = t.center;
            flip = t.flip;
            col = t.col;
            path = t.path;
            TYPE = t.TYPE;
            angle = t.angle;
            return *this;
        }
    }
    TEXTURE(SDL_Surface* surf, SDL_Renderer* rend){
        texture = NULL;
        renderer = NULL;
        surface = NULL;
        INIT();
        setren(rend);
        surfcpy(surf);
    }
    SDL_Renderer* setren(SDL_Renderer* rend = NULL)
    {
        renderer = rend;
        return renderer;
    }
    SDL_Renderer* crtren(SDL_Window* win = NULL, int index = -1, Uint32 flag = SDL_RENDERER_ACCELERATED)
    {
        renderer = crtren(win, index, flag);
        return renderer;
    }
    SDL_Renderer* getren() const
    {
        return renderer;
    }
    const char getTYPE()
    {
        return TYPE;
    }
    void setTYPE(const char ch = '\0')
    {
        //cout<<" setting type: "<<ch<<endl;
        TYPE = ch;
    }
    const char checkTYPE()
    {
        //cout<<" checking type: \n";
        if(strmap::strcheck(path.c_str(), ".ttf"))setTYPE('F');
        if
        (
            strmap::strcheck(path.c_str(), ".png")
            ||
            strmap::strcheck(path.c_str(), ".jpg")
            ||
            strmap::strcheck(path.c_str(), ".bmp")
        )setTYPE('I');
        else setTYPE('\0');
        return getTYPE();
    }
    void setangle(double angle_)
    {
        angle = angle_;
    }
    double getangle()
    {
        return angle;
    }
    void displayf(ofstream& out)
    {
        out<<" Texture condition: "<<(texture ? "alive\n": "dead\n");
        out<<" Surface condition: "<<(surface?  "alive\n": "dead\n");
        out<<" Renderer condition: "<<(renderer ?  "alive\n": "dead\n");
        out<<" angle: "<<angle<<endl;
        out<<" src_pos(x, y): "<<src.x<<','<<src.y<<endl;
        out<<" src_dim(w, h): "<<src.w<<','<<src.h<<endl;
        out<<" dst_pos(x, y): "<<dst.x<<','<<dst.y<<endl;
        out<<" dst_dim(w, h): "<<dst.w<<','<<dst.h<<endl;
        out<<" center(x, y): "<<center.x<<','<<center.y<<endl;
        out<<" col(r, g, b, a): "<<(int)col.r<<','<<(int)col.g<<','<<(int)col.b<<','<<(int)col.a<<endl;
        out<<" flipstate: "<<flip<<endl;
    }
    void display(ostream& os = cout)
    {
        os<<" Texture condition: "<<(texture ? "alive\n": "dead\n");
        os<<" Surface condition: "<<(surface?  "alive\n": "dead\n");
        os<<" Renderer condition: "<<(renderer ?  "alive\n": "dead\n");
        os<<" angle: "<<angle<<endl;
        os<<" src_pos(x, y): "<<src.x<<','<<src.y<<endl;
        os<<" src_dim(w, h): "<<src.w<<','<<src.h<<endl;
        os<<" dst_pos(x, y): "<<dst.x<<','<<dst.y<<endl;
        os<<" dst_dim(w, h): "<<dst.w<<','<<dst.h<<endl;
        os<<" center(x, y): "<<center.x<<','<<center.y<<endl;
        os<<" col(r, g, b, a): "<<(int)col.r<<','<<(int)col.g<<','<<(int)col.b<<','<<(int)col.a<<endl;
        os<<" flipstate: "<<flip<<endl;
    }
    const SDL_FPoint& getcenter()
    {
        return center;
    }
    SDL_Texture* gettexture()
    {
        return texture;
    }
    ~TEXTURE()
    {
        if(surface)SDL_FreeSurface(surface);
        if(texture)SDL_DestroyTexture(texture);
    }
    void setflip(SDL_RendererFlip flag_)
    {
        flip = flag_;
    }
    string setpath(const char* filepath)
    {
        //cout<<" setting path: "<<filepath<<endl;
        path = new char[strlen(filepath)];
        path = filepath;
        return path;
    }
    string getpath()
    {
        return path;
    }
    static int INIT()
    {
        return (SDL_WasInit(SDL_INIT_VIDEO) ? SDL_WasInit(SDL_INIT_VIDEO) : SDL_Init(SDL_INIT_VIDEO));
    }
    const SDL_Rect& set_srcpos(int x = 0, int y = 0)
    {
        src.x = x;
        src.y = y;
        return src;
    }
    const SDL_Rect& set_srcdim(int w, int h)
    {
        src.w = w;
        src.h = h;
        return src;
    }
    const SDL_FRect& set_dstpos(float x = 0, float y = 0)
    {
        dst.x = x;
        dst.y = y;
        return dst;
    }
    SDL_FPoint get_cenpos(){
        SDL_FPoint point = {dst.x + center.x, dst.y + center.y};
        return point;
    }
    const SDL_FRect& set_cenpos(float x = 0, float y = 0)
    {
        return set_dstpos(x - center.x, y - center.y);
    }
    const SDL_FRect& set_dstdim(int w = 0, int h = 0)
    {
        dst.w = (w ? w : src.w);
        dst.h = (h ? h : src.h);
        return dst;
    }
    void magnify(float w = 1, float h = -1){
        h = (h <= 0 ? w : h);
        dst.w *= w;
        dst.h *= h;
        setcenter(center.x * w, center.y * h);
    }
    const SDL_Rect& set_src(int w, int h, float x = -1, float y = -1)
    {
        src.w = w;
        src.h = h;
        if(x > -1)src.x = x;
        if(y > -1)src.y = y;
        return src;
    }
    const SDL_FRect& set_dst(int w, int h, float x = -1, float y = -1)
    {
        dst.w = w;
        dst.h = h;
        if(x > -1)dst.x = x;
        if(y > -1)dst.y = y;
        return dst;
    }
    const SDL_Rect& set_src(const SDL_Rect& src_)
    {
        src = src_;
        return src;
    }
    const SDL_FRect& set_dst(const SDL_FRect& dst_)
    {
        dst = dst_;
        return dst;
    }
    SDL_FRect& getdst() // const
    {
        return dst;
    }
    SDL_Rect& getsrc() // const
    {
        return src;
    }
    const SDL_FRect& getdst() const
    {
        return dst;
    }
    const SDL_Rect& getsrc() const
    {
        return src;
    }
    SDL_Rect retquery()
    {
        SDL_Rect ret;
        queryR(&ret);
        return ret;
    }
    const SDL_FPoint& setcenter(float x, float y)
    {
        center.x = x;
        center.y = y;
        return center;
    }
    const SDL_FPoint& setcenter()
    {
        return setcenter(dst.w/2, dst.h/2);
    }
    int query(int* w = NULL, int * h = NULL)
    {
        return SDL_QueryTexture(texture, NULL, NULL, (w ? w : &src.w), (h ? h : &src.h));
    }
    int queryR(SDL_Rect* src_ = NULL)
    {
        setcenter();
        return query((src_ ? &(src_->w) : &src.w), (src_ ? &(src_->h) : &src.h));
    }
    SDL_Texture* load(const char* filepath = NULL, SDL_Renderer* rend = NULL)
    {
        texture = IMG_LoadTexture((rend ? rend : renderer), filepath ? filepath : path.c_str());
        return texture;
    }
    SDL_Texture* surfcpy(SDL_Surface* surf = NULL, SDL_Renderer* rend = NULL)
    {
        texture = SDL_CreateTextureFromSurface((rend ? rend : renderer), (surf ? surf : surface));
        return texture;
    }
    int rencpy(double* angle_ = NULL, SDL_FRect* dst_ = NULL, SDL_RendererFlip flag = SDL_FLIP_NONE, SDL_FPoint* center_ = NULL, SDL_Rect* src_ = NULL, SDL_Renderer* rend = NULL)
    {
        return SDL_RenderCopyExF((rend ? rend : renderer), texture, (src_ ? src_ : &src), (dst_ ? dst_ : &dst), (angle_ ? *angle_ : angle), (center_ ? center_ : &center), flag);
    }
    int queryF()
    {
        if(query() < 0){return -2;}
        set_srcpos();
        set_dstpos();
        set_dstdim();
        setcenter();
        return 1;
    }
    int queryC(){
        if(queryR() < 0){return -2;}
        set_dstdim();
        setcenter();
        return 1;
    }
    int queryN(){
        return SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
    }
    int drawC(SDL_Renderer* rend = NULL)
    {
        if(rencpy(NULL, &dst, flip, &center, &src, rend) < 0)return -3;
        return 1;
    }
    int drawO(SDL_Renderer* rend = NULL)
    {
    	if(rencpy(NULL, &dst, flip, &center, &src, rend) < 0)return -3;
        pst(rend ? rend : renderer);
        return 1;
    }
    int drawI(const char* filepath, bool clrer = 1, SDL_Renderer* rend = NULL)
    {
        if(!load(filepath, rend)){return -1;}
        if(queryR() < 0){return -2;}
        set_srcpos();
        set_dstpos();
        set_dstdim();
        setcenter();
        if(rencpy(NULL, &dst, flip, &center, &src, rend) < 0)return -3;
        pst(rend);
        if(clrer)if(clr(rend) < 0) return -4;
        return 1;
    }
    int draw(SDL_Renderer* rend = NULL, bool clrer = 1)
    {
        if(queryR() < 0){return -1;}
        set_srcpos();
        set_dstpos();
        set_dstdim();
        setcenter();
        if(rencpy(NULL, &dst, flip, &center, &src, (rend ? rend : renderer)) < 0)return -2;
        pst(rend ? rend : renderer);
        if(clrer)if(clr((rend ? rend : renderer)) < 0) return -3;
        return 1;
    }
};
class FONT
{
    #define DEF_FONT "../Fonts/ROCKB.ttf"
    #define CHANGE_DEF_FONT(FONT_X) DEF_FONT = FONT_X
    //static const string DEFONT = "../Fonts/nyala.ttf";
    protected:
    TTF_Font* fontdata = NULL;
    int ptsize;
    string text;
    string path;
    SDL_Color col1 = {255, 255, 255, 255}, col2 = {0,0,0,0};
    public:
    const FONT& operator=(const FONT& f)
    {
        //cout<<" assignment called for font\n";
        ptsize = f.ptsize;
        //cout<<" ptsize assigned\n";
        setpath(f.path.c_str());
        //cout<<" filepath set\n";
        settext(f.text);
        //cout<<" text set\n";
        setfontD();
        //cout<<" font opening success\n";
        col1 = f.col1;
        col2 = f.col2;
        //cout<<" colors set\n";
        return *this;
    }
    FONT(const FONT& f)
    {
        *this = f;
    }
    TTF_Font* getfont()
    {
        return fontdata;
    }
    const string& gettext() const //
    {
        return text;
    }
    int getptsize()
    {
        return ptsize;
    }
    int TEXT_size(int* w, int *h)
    {
        return TTF_SizeText(getfont(), gettext().c_str(), w, h);
    }
    int setptsize(int pt_size = 12) {ptsize = pt_size;}
    FONT(const char* fontpath = DEF_FONT, int pt_size = 20, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0)
    {
        //cout<<" constructor called for font\n";
        INIT();
        setpath(fontpath);
        setptsize(pt_size);
        setfontD();
        setcol1(r, g, b, a);
        setcol2(255 - r, 255 - g, 255 - b, 255 - a);
    }
    static int INIT()
    {
        return (TTF_WasInit() ? TTF_WasInit() : TTF_Init());
    }
    const SDL_Color& setcol1(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0) //
    {
        //cout<<" setting col1: "<<(int)r<<','<<(int)g<<','<<(int)b<<','<<(int)a<<endl;
        col1.r = r;
        col1.g = g;
        col1.b = b;
        col1.a = a;
        return col1;
    }
    const SDL_Color& setcol2(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0) //
    {
        //cout<<" setting col2: "<<(int)r<<','<<(int)g<<','<<(int)b<<','<<(int)a<<endl;
        col2.r = r;
        col2.g = g;
        col2.b = b;
        col2.a = a;
        return col2;
    }
    const SDL_Color& getcol1() // 
    {
        return col1;
    }
    const SDL_Color& getcol2() // 
    {
        return col2;
    }
    const string& getpath() const //
    {
        return path;
    }
    const string& setpath(const char* fontpath = "../Fonts/nyala.ttf") //
    {
        path = fontpath;
        return path;
    }
    TTF_Font* setfont(const char* fontpath = "../Fonts/nyala.ttf", int pt_size = 12)
    {
        //cout<<" setting font: "<<fontpath<<" with ptsize: "<<pt_size<<endl;
        fontdata = TTF_OpenFont(fontpath, pt_size);
        if(!fontdata){cout<<" font loading error: "<<SDL_GetError()<<endl;}
        return fontdata;
    }
    TTF_Font* setfontD()
    {
        fontdata = setfont(path.c_str(), ptsize);
        return fontdata;
    }
    SDL_Surface* solid_render(const char* _text = NULL, SDL_Color* col = NULL)
    {
        return TTF_RenderText_Solid(fontdata, (_text ? _text : text.c_str()), (col ? *col : col1));
    }
    SDL_Surface* shaded_render(const char* _text = NULL, SDL_Color* cola = NULL, SDL_Color* colb = NULL)
    {
        return TTF_RenderText_Shaded(fontdata, (_text ? _text : text.c_str()), (cola ? *cola : col1), (colb ? *colb : col2));
    }
    SDL_Surface* blended_render(const char* _text = NULL, SDL_Color* col = NULL)
    {
        return TTF_RenderText_Blended(fontdata, (_text ? _text : text.c_str()), (col ? *col : col1));
    }
    SDL_Surface* LCD_render(const char* _text = NULL, SDL_Color* cola = NULL, SDL_Color* colb = NULL)
    {
        return TTF_RenderText_LCD(fontdata, (_text ? _text : text.c_str()), (cola ? *cola : col1), (colb ? *colb : col2));
    }
    SDL_Surface* blended_render_utf8(const char* _text = NULL, SDL_Color* col = NULL){
        return TTF_RenderUTF8_Blended(fontdata, (_text ? _text : text.c_str()), (col ? *col : col1));
    }
    SDL_Surface* blended_render_unicode(const char* _text = NULL, SDL_Color* col = NULL){
        return TTF_RenderUNICODE_Blended(fontdata, (const Uint16*)(_text ? _text : text.c_str()), (col ? *col : col1));
    }
    const string settext(const string& text_)
    {
        text = text_;
        return text;
    }
    ~FONT()
    {
        TTF_CloseFont(fontdata);
    }
};
class TXT: protected FONT{
    public:
    TEXTURE board;
    const string& gettext() const{
        return FONT::gettext();
    }
    TXT(){
        FONT();
    }
    void queryB(int *w = NULL, int *h = NULL){
        w = (!w ? &board.getsrc().w : w);
        h = (!h ? &board.getsrc().h : h);
        TEXT_size(w, h);
    }
    bool checkfont(){
        return (fontdata ? true : false);
    }
    TXT(const char* text, SDL_Renderer* rend, int pts = 20, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0, const char* fontpath = DEF_FONT){
        FONT(DEF_FONT, pts, r, g, b, a);
        board.setren(rend);
        queryB();
        board.surfcpy(blended_render(text, &col1));
        board.queryF();
    }
};
class AUDIO
{
    private:
    Mix_Chunk* chunk = NULL;
    public:
    AUDIO(int freq, Uint16 format, int channels, int chunksize){
        INIT(SDL_INIT_AUDIO);
        Open_AUD(freq, format, channels, chunksize);
    }
    AUDIO(){
        INIT(SDL_INIT_AUDIO);
        Open_AUD(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    }
    AUDIO(const string& path){
        INIT(SDL_INIT_AUDIO);
        Open_AUD(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
        load(path);
        //allocate_channels(4);
    }
    void load(const char* path){
        chunk = Load_WAV(path);
        if(!chunk)cout << SDL_GetError() << "\a\n";
    }
    void load(const string& path){
        load(path.c_str());
    }
    int setvol(int vol){
        return Set_chunkVOL(chunk, vol);
    }
    int play(int chann, int loops = 1){
        return Mix_PlayChannel(chann, chunk, loops);
    }
    int playt(int chann, int time, int loops = 1){
        return Play_chann(chann, chunk, loops, time);
    }
    int halt(int chann){
        return haltchann(chann);
    }
    ~AUDIO(){
        FreeChunk(chunk);
        closeAUD();
    }
};
