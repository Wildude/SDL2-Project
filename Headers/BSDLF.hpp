const string filepath = "../Files/Data/";
const string event_path = "events.log";
const string window_path = "windows.log";
const string renderer_path = "renderer.log";
const string font_path = "fonts.log";
const string texture_path = "textures.log";
const string audio_path = "audio.log";
const string network_path = "network.log";
const string textbox_path = "textbox.log";
ofstream event_file(filepath + event_path);
ofstream window_file(filepath + window_path);
ofstream renderer_file(filepath + renderer_path);
ofstream font_file(filepath + font_path);
ofstream texture_file(filepath + texture_path);
ofstream audio_file(filepath + audio_path);
ofstream network_file(filepath + network_path);
ofstream textbox_file(filepath + textbox_path);
using namespace SDL2;

class InputManager {
    public:
    InputManager() {
        keyDown.fill(false);
        //keyPressed.fill(false);
        keyReleased.fill(false);
        keyDelayCounters.fill(0);
        mouseDelayCounters.fill(0);
    }

    void update() {
        // Reset transitional states
        //keyPressed.fill(false);
        keyReleased.fill(false);
        //mousePressed.fill(false);
        mouseReleased.fill(false);

        // Poll all events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN && !e.key.repeat) {
                SDL_Scancode sc = e.key.keysym.scancode;
                keyDown[sc] = true;
                //keyPressed[sc] = true;
            } else if (e.type == SDL_KEYUP) {
                SDL_Scancode sc = e.key.keysym.scancode;
                keyDown[sc] = false;
                keyReleased[sc] = true;
                keyDelayCounters[sc] = 0;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                mouseDown[e.button.button] = true;
                //mouseDelayCounters[e.button.button]++;
                //mousePressed[e.button.button] = true;
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                mouseDown[e.button.button] = false;
                mouseReleased[e.button.button] = true;
                mouseDelayCounters[e.button.button] = 0;
            }

            if (e.type == SDL_MOUSEMOTION) {
                mouseXY.x = e.motion.x;
                mouseXY.y = e.motion.y;
            }

            if (e.type == SDL_MOUSEWHEEL) {
                mouseWheelY = e.wheel.y;
            }
        }

        // Update key repeat delay counters
        updateDelays();

        mouseWheelY = 0; // Reset wheel each frame
    }

    bool shouldQuit() const { return quit; }

    // Keyboard input
    bool isKeyDown(SDL_Scancode key) const {
        //cout << " checking key: " << keyDown[key] <<endl; 
        return keyDown[key]; 
    }
    //bool isKeyJustPressed(SDL_Scancode key) const { return keyPressed[key]; }
    bool isKeyReleased(SDL_Scancode key) const { return keyReleased[key]; }

    // Delayed action support
    bool isKeyReady(SDL_Scancode key, int delayFrames = 10){
        if(keyDown[key]){
            if(keyDelayCounters[key] && keyDelayCounters[key] < delayFrames){
                cout << " key not ready: " << keyDelayCounters[key] << endl;
                return false;
            }
            else{
                if(key == SDL_SCANCODE_INSERT){
                    // cout << " evaluated\n";
                }
                keyDelayCounters[key] = 0;
                return true;
            }
        }
        else return false;
    }
    bool isMouseReady(Uint8 button, int delayFrames = 30){
        if(mouseDown[button]){
            if(mouseDelayCounters[button] > 1 && mouseDelayCounters[button] < delayFrames){
                //cout << " mouse not ready: " << mouseDelayCounters[button] << endl;
                mouseDelayCounters[button]++;
                return false;
            }
            else{
                //cout << " mouse ready: " << endl;
                mouseDelayCounters[button] = 0;
                mouseDelayCounters[button] = 2; // Reset to 1 to avoid immediate re-triggering
                return true;
            }
        }
        else return false;
    }
    // Mouse input
    bool isMouseDown(Uint8 button) const { return mouseDown[button]; }
    //bool isMouseJustPressed(Uint8 button) const { return mousePressed[button]; }
    bool isMouseReleased(Uint8 button) const { return mouseReleased[button]; }

    int getMouseX() const { return mouseXY.x; }
    int getMouseY() const { return mouseXY.y; }
    const SDL_Point& getMouseP() const { return mouseXY; }
    int getMouseWheelY() const { return mouseWheelY; }
    const array<int, SDL_NUM_SCANCODES>& getDelayCounters(){
        return keyDelayCounters;
    }
    array<bool, SDL_NUM_SCANCODES>& getKeyDowns(){
        return keyDown;
    }
    protected:
    void updateDelays() {
        for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
            if (keyDown[i]) {
                keyDelayCounters[i]++;
            } else {
                keyDelayCounters[i] = 0;
            }
        }
    }
    bool quit = false;
    

    array<bool, SDL_NUM_SCANCODES> keyDown;
    // array<bool, SDL_NUM_SCANCODES> keyPressed;
    array<bool, SDL_NUM_SCANCODES> keyReleased;
    array<int, SDL_NUM_SCANCODES> keyDelayCounters;
    array<int, 8> mouseDelayCounters{}; // SDL_BUTTON_LEFT...SDL_BUTTON_X2
    array<bool, 8> mouseDown{};      // SDL_BUTTON_LEFT...SDL_BUTTON_X2
    //array<bool, 8> mousePressed{};
    array<bool, 8> mouseReleased{};
    SDL_Point mouseXY = {0, 0};
    int mouseWheelY = 0;
    protected: SDL_Event e;
};
class TextInputHandler : public InputManager {
    public:
    TextInputHandler(bool use = false, string* whichtext = NULL) : useText(use), textTo(whichtext), quitCase(SDL_SCANCODE_RETURN), InputManager(){
        if(useText)startText();
    }
    void setTextUse(bool use){
        useText = use;
    }
    // checks if the input handler is on text input mode
    bool checkText(){
        if(!useText)SDL_StopTextInput();
        else SDL_StartTextInput();
        return useText;
    }
    bool getTextState() const{
        return useText;
    }
    ~TextInputHandler() {
        SDL_StopTextInput(); // Stop listening for text input when done
    }
    void update() {
        if (useText){
            if (!SDL_IsTextInputActive()) SDL_StartTextInput();
        }
        // Only start text input once when entering text mode
        else if(SDL_IsTextInputActive()) SDL_StopTextInput();

        // Reset transitional states
        //keyPressed.fill(false);
        keyReleased.fill(false);
        //mousePressed.fill(false);
        mouseReleased.fill(false);

        // Poll all events
        // Clear all events in this mode
        while (SDL_PollEvent(&e)) {
            //cout << " still on text: "<< useText << endl;
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                //cout << " mouse button down\n";
                //cout << " mouse: " << (int)e.button.button << endl;
                mouseDown[e.button.button] = true;
                mouseDelayCounters[e.button.button]++;
                //mousePressed[e.button.button] = true;
            } 
            else if (e.type == SDL_MOUSEBUTTONUP) {
                //cout << " mouse button up\n";
                //cout << " mouse: " << (int)e.button.button << endl;
                mouseDown[e.button.button] = false;
                mouseReleased[e.button.button] = true;
                mouseDelayCounters[e.button.button] = 0;
            }
            if (e.type == SDL_MOUSEMOTION) {
                mouseXY.x = e.motion.x;
                mouseXY.y = e.motion.y;
            }
            if (e.type == SDL_MOUSEWHEEL) {
                mouseWheelY = e.wheel.y;
            }
            if (e.type == SDL_KEYUP) {
                SDL_Scancode sc = e.key.keysym.scancode;
                keyDown[sc] = false;
                keyReleased[sc] = true;
                keyDelayCounters[sc] = 0;
            }
            if(!useText){
                textTo = NULL;
                if (e.type == SDL_KEYDOWN && !e.key.repeat) {
                SDL_Scancode sc = e.key.keysym.scancode;
                keyDown[sc] = true;
                //keyPressed[sc] = true;
                } else if (e.type == SDL_KEYUP) {
                    SDL_Scancode sc = e.key.keysym.scancode;
                    keyDown[sc] = false;
                    keyReleased[sc] = true;
                    keyDelayCounters[sc] = 0;
                }
            }   
            else{
                if (e.type == SDL_TEXTINPUT) {
                    inputText += e.text.text;
                } 
                else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                        inputText.pop_back();
                    } else if (
                        e.key.keysym.sym == SDL_GetKeyFromScancode(quitCase) || 
                        e.key.keysym.sym == SDLK_ESCAPE
                    ) {
                        useText = false;
                        SDL_StopTextInput();  // stop when exiting
                        textTo = NULL;
                    }
                }
                if(useText && !textTo)textTo = &inputText; // Update the textTo pointer to the current inputText
            }
            
        }
        
        // Update key repeat delay counters
        updateDelays();
        mouseWheelY = 0; // Reset wheel each frame
    }
    const string& getText() const {
        return inputText;
    }

    void clearText() {
        inputText.clear();
    }
    void setInput(){
        textTo = NULL;
    }
    void setInput(string*& the_str){
        if(!textTo)textTo  = &inputText;
        the_str = textTo;
    }
    void setInput(string& the_str){
        textTo = &the_str;
    }
    void setQuitCase(SDL_Scancode quiter = SDL_SCANCODE_RETURN){
        quitCase = quiter;
    }

private:
    void startText(){
        SDL_StartTextInput(); // Start listening for text input
        inputText.clear();    // Initialize empty text buffer
    }
    bool useText;
    string inputText; // Stores the text input
    string* textTo;
    SDL_Scancode quitCase;
};
class WINDOW
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    string title;
    int x, y, w, h;
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
    int getx() const {return x;}
    int gety() const {return y;}
    int getw() const {return w;}
    int geth() const {return h;}
    int getcx() {return w/2;}
    int getcy() {return h/2;}
    Vint2 getc() {return Vint2(w/2, h/2);}
    SDL_Point getc() const {return SDL_Point({w/2, h/2});}
    string gettitle() const {return title;}
    inline void pst()
    {
        return SDL2::pst(renderer);
    }
    inline int clr(const SDL_Color& col = {255, 255, 255, 255})
    {
        set_rencol(col.r, col.b, col.g, col.a);
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
        if(!color)return 0;
        return pstcol(color->r, color->g, color->b, color->a);
    }
    int pstcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_Color col = {r, g, b, a};
        int ret = set_rencol(&col);
        clr(col);
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
    int set_rencol(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        return SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
    void set_clrcol(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
        col = SDL_Color({r, g, b, a});
    }
    SDL_Renderer* crtren(SDL_Window* window_ = NULL, int index = -1, Uint32 flag = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC)
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
    void drawline(const Vflt2& v1, const Vflt2& v2)
    {
        SDL_RenderDrawLine(renderer, v1.getx(), v1.gety(), v2.getx(), v2.gety());
    }
    void drawrect(const SDL_Rect& cam)
    {
        SDL_RenderDrawRect(renderer, &cam);   
    }
    // filled rectangle and point remaining
};
class TEXTURE
{
    SDL_Texture* texture = NULL; // 4 bytes (pointer)
    // SDL_Renderer* renderer; // 4 bytes (pointer) // x
    SDL_Rect src = {0, 0, 0, 0}; // 16 bytes (4 * 4 int) // x
    SDL_FRect dst = {0, 0, 0, 0}; // 16 bytes (4 * 4 float) //x
    SDL_FPoint center = {0, 0}; // 8 bytes (4 + 4 float) //x
    // SDL_RendererFlip flip = SDL_FLIP_NONE; // 4 bytes (optional)
    char* path = NULL;
    // double angle = 0; // 8 bytes
    // total = 
    public:
    TEXTURE(){
        // renderer = NULL;
        INIT();
    }
    void copy(const TEXTURE& t, SDL_Renderer* rend){
        setpath(t.path);
        load(NULL, rend);
    }
    TEXTURE(const char* filepath, SDL_Renderer* ren)
    {
        //cout<<" contructor called for textures\n";
        texture = NULL;
        // renderer = NULL;
        INIT();
        setpath(filepath);
        load(filepath, ren);
    }
    const TEXTURE& operator=(const TEXTURE& t)
    {
        //cout<<" assignment called for font\n";
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
    TEXTURE(SDL_Surface* surf, SDL_Renderer* rend){
        texture = NULL;
        // renderer = NULL;
        INIT();
        surfcpy(surf, rend);
    }
    SDL_Renderer* crtren(SDL_Window* win = NULL, int index = -1, Uint32 flag = SDL_RENDERER_ACCELERATED)
    {
        // renderer = crtren(win, index, flag);
        return NULL; //renderer;
    }
    SDL_Renderer* getren() const
    {
        return NULL;// renderer;
    }
    void setangle(double angle_)
    {
        //angle = angle_;
    }
    double getangle()
    {
        return -1.99999999999999F;// angle;
    }
    void displayf(ofstream& out)
    {
        out<<" Texture condition: "<<(texture ? "alive\n": "dead\n");
        //out<<" Renderer condition: "<<(renderer ?  "alive\n": "dead\n");
        //out<<" angle: "<<angle<<endl;
        out<<" src_pos(x, y): "<<src.x<<','<<src.y<<endl;
        out<<" src_dim(w, h): "<<src.w<<','<<src.h<<endl;
        out<<" dst_pos(x, y): "<<dst.x<<','<<dst.y<<endl;
        out<<" dst_dim(w, h): "<<dst.w<<','<<dst.h<<endl;
        out<<" center(x, y): "<<center.x<<','<<center.y<<endl;
        //out<<" flipstate: "<<flip<<endl;
    }
    void display(ostream& os = cout)
    {
        os<<" Texture condition: "<<(texture ? "alive\n": "dead\n");
        //os<<" Renderer condition: "<<(renderer ?  "alive\n": "dead\n");
        //os<<" angle: "<<angle<<endl;
        os<<" src_pos(x, y): "<<src.x<<','<<src.y<<endl;
        os<<" src_dim(w, h): "<<src.w<<','<<src.h<<endl;
        os<<" dst_pos(x, y): "<<dst.x<<','<<dst.y<<endl;
        os<<" dst_dim(w, h): "<<dst.w<<','<<dst.h<<endl;
        os<<" center(x, y): "<<center.x<<','<<center.y<<endl;
        // os<<" flipstate: "<<flip<<endl;
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
        if(texture)SDL_DestroyTexture(texture);
        if(path)delete[] path;
    }
    void setflip(const SDL_RendererFlip& flag_)
    {
        // flip = flag_;
    }
    const char* setpath(const char* fpath)
    {
        //cout<<" setting path: "<<filepath<<endl;
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
    const char* getpath()
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
    SDL_FPoint get_cenpos(){ // no optimization
        SDL_FPoint point = {dst.x + center.x, dst.y + center.y};
        return point;
    }
    const SDL_FRect& set_cenpos(float x = 0, float y = 0)
    {
        return set_dstpos(x - center.x, y - center.y);
    }
    const SDL_FRect& set_dstdim(int w = 0, int h = 0)
    {
        dst.w = (w ? w : dst.w);
        dst.h = (h ? h : dst.h);
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
    SDL_Rect retquery() // no optimization
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
    void delTex(){
        if(texture){
            SDL_DestroyTexture(texture);
            texture = NULL;
        }
    }
    SDL_Texture* load(const char* filepath, SDL_Renderer* rend)
    {
        delTex();
        texture = IMG_LoadTexture((rend), filepath ? filepath : path);
        if(!texture)texture_file << " Error loading texture: " << SDL_GetError() << endl;
        return texture;
    }
    SDL_Texture* surfcpy(SDL_Surface*& surf, SDL_Renderer* rend)
    {
        texture = SDL_CreateTextureFromSurface((rend), surf);
        return texture;
    }
    int rencpy(SDL_Renderer* rend, SDL_FRect* dst_ = NULL, SDL_Rect* src_ = NULL, SDL_RendererFlip flag = SDL_FLIP_NONE, SDL_FPoint* center_ = NULL, double angle = 0)
    {
        return SDL_RenderCopyExF(rend, texture, (src_ ? src_ : &src), (dst_ ? dst_ : &dst), angle, (center_ ? center_ : &center), flag);
    }
    int queryF()
    {
        if(query() < 0){return -2;}
        set_srcpos();
        set_dstpos();
        set_dstdim(src.w, src.h);
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
    static int drawRect(const SDL_Rect& rect, SDL_Renderer* rend, int ptsize = 1){
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
    static int drawRectP(const SDL_Rect& rect, SDL_Renderer* rend, int ptsize = 1){
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
    int drawPX(SDL_Renderer* rend, SDL_FRect* rect = NULL, float scale = 0.5){
        SDL_FRect* drawRect = (rect ? new SDL_FRect({dst.x - (bool)(dst.x/(rect->w * scale)) * (rect->w * scale) , dst.y - (int)(dst.y/(rect->h * scale)) * (rect->h * scale), dst.w * scale, dst.h * scale}) : new SDL_FRect({dst.x, dst.y, dst.w * scale, dst.h * scale}));
        return drawC(rend, drawRect);
    }
    int drawOF(SDL_Renderer* rend, SDL_FRect* rect = NULL, float scale = 1, double angle = 0){
        SDL_FPoint c = {getcenter().x * scale, getcenter().y * scale};
        SDL_FRect* drawRect = (rect ? new SDL_FRect({dst.x - rect->x - (c.x - getcenter().x), dst.y - rect->y - (c.y - getcenter().y), dst.w * scale, dst.h * scale}) : new SDL_FRect({dst.x, dst.y, dst.w * scale, dst.h * scale}));
        return drawC(rend, drawRect, angle);
    }
    int drawC(SDL_Renderer* rend, SDL_FRect* rect = NULL, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        if(rencpy(rend, rect, NULL, flip, NULL, angle) < 0)return -3;
        return 1;
    }
    int drawO(SDL_Renderer* rend, SDL_FRect* rect = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
    	if(rencpy(rend, rect, NULL, flip, &center, 0) < 0)return -3;
        pst(rend);
        return 1;
    }
    int drawI(const char* filepath, SDL_Renderer* rend, bool clrer = 1, SDL_FRect* rect = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        if(!load(filepath, rend)){return -1;}
        if(queryR() < 0){return -2;}
        set_srcpos();
        set_dstpos();
        set_dstdim();
        setcenter();
        if(rencpy(rend, (rect ? rect : &dst), NULL, flip, &center, 0) < 0)return -3;
        pst(rend);
        if(clrer)if(clr(rend) < 0) return -4;
        return 1;
    }
    int draw(SDL_Renderer* rend, SDL_FRect* rect = NULL, bool clrer = 1, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        if(queryR() < 0){return -1;}
        set_srcpos();
        set_dstpos();
        set_dstdim();
        setcenter();
        if(rencpy(rend, (rect ? rect : &dst), NULL, flip, &center, 0) < 0)return -2;
        pst(rend);
        if(clrer)if(clr((rend)) < 0) return -3;
        return 1;
    }
    int drawRect(SDL_Rect rect){

    }
};
class FONT
{
    #define DEF_FONT "../Fonts/nyala.ttf"
    #define CHANGE_DEF_FONT(FONT_X) DEF_FONT = FONT_X
    //static const string DEFONT = "../Fonts/nyala.ttf";    
    public:
    FONT(){
        // cout<<" constructor called for font\n";
        INIT();
        ptsize = 12;
    }
    const FONT& operator=(const FONT& f)
    {
        // cout<<" assignment called for font\n";
        if(this == &f)return *this;
        int result = setpath(f.path);
        if(result == 0 && ptsize != f.ptsize){
            // cout << "\n pt assigned";
            ptsize = f.ptsize;
            setfont(path);
        }
        else if(result == 1){
            ptsize = f.ptsize;
            setfont(path);
        }
        // cout<<"\n ptsize: " << ptsize << endl;
        // cout<<" path: " << (path ? path : "NULL") << endl;
        return *this;
    }
    inline void delpath(){
        if(path)delete[] path;
        path = NULL;
    }
    inline void delfont(){
        if(fontdata){
            TTF_CloseFont(fontdata);
            fontdata = NULL;
        }
    }
    int setpath(const char* fpath){
        // cout << " setting path: \n";
        if(fpath){
            if(path && strcmp(fpath, path) == 0){
                // cout << " same pathes, quiting\n";
                return 0;
            }
            // cout << " different pathes editing\n";
            if(path)delete[] path;
            path = new char[strlen(fpath) + 1];
            strcpy(path, fpath);       
            return 1;
        }
        else{
            // cout << " new path empty, deleting path\n";
            if(path)delete[] path;
            path = NULL;
            delfont();
            return -1;
        }
    }
    FONT(const FONT& f)
    {
        *this = f;
    }
    FONT(const FONT& f, int style)
    {
        *this = f;
        setStyle(style);
    }
    TTF_Font* getfont() const
    {
        TTF_Font* font = fontdata;
        return font;
    }
    int getptsize() const
    {
        return ptsize;
    }
    const char* getpath() const{
        return path;
    }
    inline int TEXT_size(const char* thetext, int* w, int *h) const
    {
        return TTF_SizeText(getfont(), thetext, w, h);
    }
    void setptsize(int pt_size) {
        ptsize = pt_size;
    }
    FONT(const char* fontpath, int pt_size): FONT()
    {
        setpath(fontpath);
        setptsize(pt_size);
        setfont(path);
    }
    static int INIT()
    {
        return (TTF_WasInit() ? TTF_WasInit() : TTF_Init());
    }
    bool checkpath(){
        font_file << " checking font path: ";
        if(!path){
            font_file << "fontpath is NULL\n";
            delfont();
            return false;
        }
        font_file << " good\n";
        return true;
    }
    bool checkfont(){
        font_file << " checking font: ";
        if(!fontdata){
            font_file << "fontdata is NULL\n";
            delpath();
            return false;
        }
        font_file << " good\n";
        return true;
    }
    void display() const{
        cout << " checkfont: " << (fontdata != NULL ? "true\n" : "false\n");
        cout << " ptsize: " << ptsize << endl;
        cout << " path: " << path << endl;
    }
    void setStyle(int style){
        TTF_SetFontStyle(fontdata, style);
    }
    int getStyle() {
        int style = TTF_GetFontStyle(fontdata);
        cout << " style:";
        if (style == TTF_STYLE_NORMAL) cout << " NORMAL";
        else {
            if (style & TTF_STYLE_BOLD) cout << " BOLD";
            if (style & TTF_STYLE_ITALIC) cout << " ITALIC";
            if (style & TTF_STYLE_UNDERLINE) cout << " UNDERLINE";
            if (style & TTF_STYLE_STRIKETHROUGH) cout << " STRIKETHROUGH";
        }
        cout << "\n";
        return style;
    }

    /*
    Constant	                Effect
    TTF_STYLE_NORMAL	        Default
    TTF_STYLE_BOLD	            Bold text
    TTF_STYLE_ITALIC	        Slanted text
    TTF_STYLE_UNDERLINE	        Underline
    TTF_STYLE_STRIKETHROUGH	    Strike line
    */
    ~FONT()
    {
        font_file.close();
        TTF_CloseFont(fontdata);
        delete[] path;
    }
    friend ostream& operator<<(ostream&, const FONT&);
    private:
    TTF_Font* fontdata = NULL; // 4 bytes
    char* path = NULL; // 4 bytes
    int ptsize; // 4 bytes
    // total = 12 bytes
    TTF_Font* setfont(const char* fontpath = "../Fonts/nyala.ttf")
    {
        // cout<<" setting font: "<<fontpath<<" with ptsize: "<< ptsize <<endl;
        delfont();
        fontdata = TTF_OpenFont(fontpath, ptsize);
        if(!fontdata){
            cout <<" font loading error: "<<SDL_GetError()<<endl; 
            font_file << " font loading error: " << SDL_GetError() << endl;
            
            return NULL;
        }
        return fontdata;
    }
};
ostream& operator<<(ostream& os, const FONT& font){
    os << '<' << font.getpath() << ">(x" << font.getptsize() << ')';
    return os;
}
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
    void updatebox(){
        switch (anchor){
            case TOP_LEFT:
            padding.x = 0;
            padding.y = 0;
            break;
            case CENTER:
            padding.x = 
            padding.y =
            padding.w =
            padding.h = 
            max(max(padding.x, padding.y),max(padding.w, padding.h));
            break;
            case BOTTOM_RIGHT:
            padding.w = 0;
            padding.h = 0;
            break;
            case TOP:
            padding.y = 0;
            break;
            case BOTTOM:
            padding.h = 0;
            break;
            case LEFT:
            padding.x = 0;
            break;
            case RIGHT:
            padding.w = 0;
            break;
            case TOP_RIGHT:
            padding.w = 0;
            padding.y = 0;
            break;
            BOTTOM_LEFT:
            padding.x = 0;
            padding.h = 0;
            break;
            default:
            break;
        }   
    }
    public:
    // Anchor/origin (e.g., top-left, center)
    enum Anchor { TOP_LEFT, CENTER, BOTTOM_RIGHT, TOP, BOTTOM, LEFT, RIGHT, TOP_RIGHT, BOTTOM_LEFT, CUSTOM};
    Anchor anchor = CENTER;
    Box() {
        padding = {0, 0, 0, 0};
        border = {0, 0, 0, 0};
        margin = {0, 0, 0, 0};
    }
    const Box& operator=(const Box& box){
        if(this != &box){
            contentRect = box.contentRect;
            padding = box.padding;
            border = box.border;
            margin = box.margin;
            borderColor = box.borderColor;
            backgroundColor = box.backgroundColor;
            anchor = box.anchor;
        }
        return *this;
    }
    Box(const Box& box){
        *this = box;
    }
    Box(int x, int y, int w, int h){
        contentRect = {x, y, w, h};
    }
    float padavgx(){
        return (padding.x + padding.w)/2.0f;
    }
    float padavgy(){
        return (padding.y + padding.h)/2.0f;
    }
    float padavg(){
        return (padavgx() + padavgy())/2;
    }
    float borderavgx(){
        return (border.x + border.w)/2.0f;
    }
    float borderavgy(){
        return (border.y + border.h)/2.0f;
    }
    float borderavg(){
        return (borderavgx() + borderavgy())/2;
    }
    float marginavgx(){
        return (margin.x + margin.w)/2.0f;
    }
    float marginavgy(){
        return (margin.y + margin.h)/2.0f;
    }
    float marginavg(){
        return (marginavgx() + marginavgy())/2;
    }
    void setanchor(Anchor Nanchor = CENTER){
        anchor = Nanchor;
        updatebox();
    }
    const SDL_Rect& getcontent(){
        return contentRect;
    }
    void setpos(SDL_Point point){
        setpos(point.x, point.y);
    }
    void setpos(int x, int y){
        contentRect.x = x;
        contentRect.y = y;
    }
    void setSize(int w, int h){
        contentRect.w = w;
        contentRect.h = h;
    }
    void setpadding(int x = -1, int y = -1, int w = -1, int h = -1){
        if(x == -1 && y == -1 && w == -1 && h == -1){
            padding.x =
            padding.y = 
            padding.w = 
            padding.h = 
            max(max(padding.x, padding.y), max(padding.w, padding.h));
            // cout << " previous pad\n";
            return;
        }
        else if(y == -1 && w == -1 && h == -1){
            padding.x = 
            padding.y =
            padding.w =
            padding.h = x;
            // cout << " center pad\n";
            return;
        }
        else if(w == -1 && h == -1){
            padding.x = padding.w = x;
            padding.y = padding.h = y;
            // cout << " 2x center pad\n";
            return;
        }
        else if(h == -1){
            padding.x = x;
            padding.y = padding.h = y;
            padding.w = w;
            // cout << " 3x pad\n";
            return;
        }
        else{
            padding.x = x;
            padding.y = y;
            padding.w = w;
            padding.h = h;
            // cout << " 4x pad\n";
            return;
        }
    }
    void setborder(int x = -1, int y = -1, int w = -1, int h = -1){
        if(x == -1 && y == -1 && w == -1 && h == -1){
            border.x =
            border.y =
            border.w =
            border.h =
            max(max(border.x, border.y), max(border.w, border.h));
            return;
        }
        else if(y == -1 && w == -1 && h == -1){
            border.x =
            border.y =
            border.w =
            border.h = x;
            return;
        }
        else if(w == -1 && h == -1){
            border.x = border.w = x;
            border.y = border.h = y;
            return;
        }
        else if(h == -1){
            border.x = x;
            border.y = border.h = y;
            border.w = w;
            return;
        }
        else{
            border.x = x;
            border.y = y;
            border.w = w;
            border.h = h;
            return;
        }
    }
    void setmargin(int x = -1, int y = -1, int w = -1, int h = -1){
        if(x == -1 && y == -1 && w == -1 && h == -1){
            margin.x =
            margin.y =
            margin.w =
            margin.h =
            max(max(margin.x, margin.y), max(margin.w, margin.h));
            return;
        }
        else if(y == -1 && w == -1 && h == -1){
            margin.x =
            margin.y =
            margin.w =
            margin.h = x;
            return;
        }
        else if(w == -1 && h == -1){
            margin.x = margin.w = x;
            margin.y = margin.h = y;
            return;
        }
        else if(h == -1){
            margin.x = x;
            margin.y = margin.h = y;
            margin.w = w;
            return;
        }
        else{
            margin.x = x;
            margin.y = y;
            margin.w = w;
            margin.h = h;
            return;
        }
    }
    const SDL_Rect& getpadding(){
        return padding;
    }
    const SDL_Rect& getmargin(){
        return margin;
    }
    const SDL_Rect& getborder(){
        return border;
    }
    // Final computed size including all layers
    SDL_Rect fullRect() const {
        SDL_Rect rect;
        rect.x = contentRect.x
                 - padding.x - border.x - margin.x;
        rect.y = contentRect.y
                 - padding.y - border.y - margin.y;
        rect.w = contentRect.w
                 + padding.x + padding.w
                 + border.x + border.w
                 + margin.x + margin.w;
        rect.h = contentRect.h
                 + padding.y + padding.h
                 + border.y + border.h
                 + margin.y + margin.h;
        return rect;
    }

    SDL_Rect paddingBox() const {
        SDL_Rect rect = contentRect;
        rect.x -= padding.x;
        rect.y -= padding.y;
        rect.w += padding.x + padding.w;
        rect.h += padding.y + padding.h;
        return rect;
    }

    SDL_Rect borderBox() const {
        SDL_Rect pad = paddingBox();
        pad.x -= border.x;
        pad.y -= border.y;
        pad.w += border.x + border.w;
        pad.h += border.y + border.h;
        return pad;
    }

    SDL_Rect marginBox() const {
        SDL_Rect border = borderBox();
        border.x -= margin.x;
        border.y -= margin.y;
        border.w += margin.x + margin.w;
        border.h += margin.y + margin.h;
        return border;
    }
};
class TextBox{
    private:
    SDL_Rect box; // 16 bytes
    SDL_Color col1, col2; // 2 * 4 bytes
    string text; // 24 bytes
    FONT font; // 12 bytes
    // total = 66 bytes
    void setbox(int x, int y, int w, int h)
    {
        box = {x, y, w, h};
    }
    public:
    TextBox(): font(), text(""){
        // cout << " creating textbox\n";
        checkfile();
        textbox_file << " creating textbox\n";
        setbox(0, 0, 0, 0);
        col1 = {0, 0, 0, 255};
        col2 = {255, 255, 255, 255};
    }
    void checkfile(){
        if(!textbox_file.is_open()){
            textbox_file.open(filepath + textbox_path, ios::app);
        }
    }
    SDL_Surface* solid_render(const char* text_ = NULL, SDL_Color* col = NULL)
    {
        return TTF_RenderText_Solid(font.getfont(), (text_ ? text_ : text.c_str()), (col ? *col : col1));
    }
    SDL_Surface* shaded_render(const char* text_ = NULL, SDL_Color* cola = NULL, SDL_Color* colb = NULL)
    {
        return TTF_RenderText_Shaded(font.getfont(), (text_ ? text_ : text.c_str()), (cola ? *cola : col1), (colb ? *colb : col2));
    }
    SDL_Surface* blended_render(const char* text_ = NULL, SDL_Color* col = NULL)
    {
        return TTF_RenderText_Blended(font.getfont(), (text_ ? text_ : text.c_str()), (col ? *col : col1));
    }
    SDL_Surface* LCD_render(const char* text_ = NULL, SDL_Color* cola = NULL, SDL_Color* colb = NULL)
    {
        return TTF_RenderText_LCD(font.getfont(), (text_ ? text_ : text.c_str()), (cola ? *cola : col1), (colb ? *colb : col2));
    }
    SDL_Surface* blended_render_utf8(const char* text_ = NULL, SDL_Color* col = NULL){
        return TTF_RenderUTF8_Blended(font.getfont(), (text_ ? text_ : text.c_str()), (col ? *col : col1));
    }
    SDL_Surface* blended_render_unicode(const char* text_ = NULL, SDL_Color* col = NULL){
        return TTF_RenderUNICODE_Blended(font.getfont(), (const Uint16*)(text_ ? text_ : text.c_str()), (col ? *col : col1));
    }
    TextBox(const string& text_, int x, int y, int w, int h, const FONT& font_, SDL_Color* cola = NULL, SDL_Color* colb = NULL) : TextBox()
    {
        text = text_;
        font = font_;
        col1 = (cola ? *cola : SDL_Color({0, 0, 0, 0}));
        col2 = (colb ? *colb : SDL_Color({(Uint8)(255 - col1.r), (Uint8)(255 - col1.g), (Uint8)(255 - col1.b), (Uint8)(255 - col1.a)}));
        box = {x, y, w, h};
    }
    TextBox(const string& text_, const FONT& font_): TextBox(){
        text = text_;
        font = font_;
        col1 = SDL_Color({0, 0, 0, 0});
        col2 = SDL_Color({(Uint8)(255 - col1.r), (Uint8)(255 - col1.g), (Uint8)(255 - col1.b), (Uint8)(255 - col1.a)});
        font.TEXT_size(text.c_str(), &box.w, &box.h);
        box.x = 0;
        box.y = 0;
    }
    TextBox(const char* path, int ptsize = 12): TextBox(){
        font = FONT(path, ptsize);
    }
    void setcol1(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        col1.r = r;
        col1.g = g;
        col1.b = b;
        col1.a = a;
    }
    void setcol2()
    {
        setcol2(255 - col1.r, 255 - col1.g, 255 - col1.b, 255 - col1.a);
    }
    void setcol2(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        col2.r = r;
        col2.g = g;
        col2.b = b;
        col2.a = a;
    }
    void setfont(const FONT& font_){
        font = font_;
        font.TEXT_size(text.c_str(), &box.w, &box.h);
    }
    void settext(const char* text_)
    {
        if(text != string(text_)){
            text = text_;
            font.TEXT_size(text.c_str(), &box.w, &box.h);
        }   
    }
    void settext(const string& text_)
    {
        if(text != text_){
            text = text_;
            font.TEXT_size(text.c_str(), &box.w, &box.h);
        }
    }
    void setboxpos(int x, int y)
    {
        box.x = x;
        box.y = y;
    }
    void draw(SDL_Renderer* rend, SDL_Texture*& board, short drawtype = 2)
    {
        checkfile();
        textbox_file << " drawing textbox\n";
        SDL_Surface* surf;
        switch (drawtype)
        {
        case 0:
            textbox_file << " solid render\n";
            surf = solid_render(text.c_str(), &col1);
            break;
        case 1:
            textbox_file << " shaded render\n";
            surf = shaded_render(text.c_str(), &col1, &col2);
            break;
        case 2:
            textbox_file << " blended render\n";
            surf = blended_render(text.c_str(), &col1);
            break;
        case 3:
            textbox_file << " LCD render\n";
            surf = LCD_render(text.c_str(), &col1, &col2);
            break;
        default:
            textbox_file << " blended render\n";
            surf = blended_render(text.c_str(), &col1);
            break;
        }
        if(!surf){
            font_file << " Error drawing to surface: " << SDL_GetError() << endl;
            return;
        }
        if(!board)SDL_DestroyTexture(board);
        board = SDL_CreateTextureFromSurface(rend, surf);
        if(!board){
            textbox_file << " Texture creation error: " << SDL_GetError() << endl;
            return;
        }
        else textbox_file << " Texture creation success\n";
        if(SDL_RenderCopy(rend, board, NULL, &box) < 0){
            textbox_file << " RenderCopy error: " << SDL_GetError() << endl;
            return;
        }
        SDL_DestroyTexture(board);
        textbox_file << " destroyed texture\n";
        SDL_FreeSurface(surf);
        textbox_file << " destroyed surface\n";
    }
    void printbox(){
        cout << box.x << ", " << box.y << ", " << box.w << ", " << box.h;
    }
    const SDL_Rect& getBoxc() const{
        return box;
    }
    const FONT& getFontc() const{
        return font;
    }
    const SDL_Color& getCol1c() const{
        return col1;
    }
    const SDL_Color& getCol2c() const{
        return col2;
    }
    SDL_Rect& getBox(){
        return box;
    }
    FONT& getFont(){
        return font;
    }
    SDL_Color& getCol1(){
        return col1;
    }
    SDL_Color& getCol2(){
        return col2;
    }
    // pointers
    SDL_Rect* getBoxP(){
        return &box;
    }
    FONT* getFontP(){
        return &font;
    }
    SDL_Color* getCol1P(){
        return &col1;
    }
    SDL_Color* getCol2P(){
        return &col2;
    }
    const char* getText() const{
        return text.c_str();
    }
    string& getTextRef(){
        return text;
    }
    ~TextBox(){
        textbox_file << " destroying textbox\n";
        textbox_file.close();
    }
    friend ostream& operator<<(ostream&, const TextBox&);
};
ostream& operator<<(ostream& os, const TextBox& box){
    os << '\"' << box.getText() << '\"'
    << ' ' 
    << '(' 
    << box.getBoxc().x << ',' 
    << box.getBoxc().y << ',' 
    << box.getBoxc().w << ',' 
    << box.getBoxc().h << ')'
    << ' ' << box.getFontc() << ' '
    << '{'  
    << (int)box.getCol1c().r << ','
    << (int)box.getCol1c().g << ','
    << (int)box.getCol1c().b << ','
    << (int)box.getCol1c().a << '}'
    << ' ' << '{'
    << (int)box.getCol2c().r << ','
    << (int)box.getCol2c().g << ','
    << (int)box.getCol2c().b << ','
    << (int)box.getCol2c().a << '}';
    return os;
}
class TextList{
    //improved from vector (12 bytes) to nodestack (8 bytes)
    //nodestack<TextBox> boxes;
    vector<TextBox> boxes;
    int xpos, ypos; // 4 bytes
    // total = 12 bytes
    public:
    TextList(){}
    TextList(const vector<TextBox>& texts, int x, int y = 0)
    {
        for(int i = 0; i < texts.size(); i++)boxes.push_back(texts[i]);
        xpos = x;
        ypos = y;
        setup();
    }
    void setpos(int x, int y = 0){
        xpos = x;
        ypos = y;
        setup();
    }
    void setup()
    {
        int size = boxes.size();
        for(int i = 0; i < size; i++){
            boxes[i].setboxpos(xpos, i ? boxes[i - 1].getBox().y + boxes[i - 1].getBox().h : ypos);
        }
        // below is a nodestack implementation
        /*
            Lnode<TextBox>* curr = boxes.peek();
            Lnode<TextBox>* prev = NULL;
            if(!curr)return;
            // maybe check for previous push operation to save time used for traversal
            while(curr){
                curr->id.setboxpos(xpos, prev ? prev->id.getBox().h : 0);
                prev = curr;
                curr = curr->next;
            }
        */
    }
    void add(const char* txt, FONT* font = NULL, SDL_Color* col1 = NULL, SDL_Color* col2 = NULL){
        int w, h;
        int size = boxes.size();
        // the following implementation has nodestack adaptations as well
        if(!font){
            if(size/*boxes.peek()*/){
                font = new FONT(boxes[size - 1]/*boxes.peek()->id*/.getFont());
            }
            else font = new FONT();
        }
        font->TEXT_size(txt, &w, &h);
        if(!col1){
            if(size/*boxes.peek()*/)
                col1 = &boxes[size - 1]/*boxes.peek()->id*/.getCol1(); // hmmm
            else col1 = new SDL_Color({0, 0, 0, 0});
        }
        if(!col2)
            col2 = new SDL_Color({
                (Uint8)(255 - col1->r), 
                (Uint8)(255 - col1->g), 
                (Uint8)(255 - col1->b), 
                (Uint8)(255 - col1->a)
            });
        int yoffset = (
            size /*boxes.peek()*/ ? 
            boxes[size - 1]/*boxes.peek()->id*/.getBox().y + boxes[size - 1]/*boxes.peek()->id*/.getBox().h 
            : ypos
        );
        TextBox tbox(txt, *font);
        tbox.setboxpos(xpos, yoffset);
        tbox.setcol1(col1->r, col1->g, col1->b, col1->a);
        tbox.setcol2(col2->r, col2->g, col2->b, col2->a);
        boxes.push_back(tbox);
        //boxes.push(tbox);
    }
    void add(string txt){return add(txt.c_str());}
    void add(){return add("");}
    void draw(SDL_Renderer* rend, short drawtype = 2){
        // has nodestack impns
        int size = boxes.size();
        for(int i = 0; i < size; i++){
            SDL_Texture* board = NULL;
            boxes[i].draw(rend, board, drawtype);
        }
        /*
        Lnode<TextBox>* curr = boxes.peek();
        while(curr){
            SDL_Texture* board;
            curr->id.draw(rend, board, drawtype);
            curr = curr->next;
        }
        */
    }
    void drawi(int i, SDL_Renderer* rend, SDL_Texture*& board, short drawtype = 2){
        boxes[i].draw(rend, board, drawtype);
        /*
        Lnode<TextBox>* head = boxes.peek();
        Lnode<TextBox>* curr = nextNode(head, i);
        curr->id.draw(rend, board, drawtype);
        */
    }
    void edit(const char* text, int i = 0){
        boxes[i].settext(text);
    }
    const vector<TextBox>& getBoxes(){
        return boxes;
    }
    /*
    nodestack<TextBox> getBoxes(){
        return boxes;
    }
    */
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
        if(!chunk)audio_file << SDL_GetError() << "\a\n";
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
class NetworkManager {
public:
    NetworkManager() {
        if (SDLNet_Init() < 0) {
            network_file << "SDLNet_Init failed: " << SDLNet_GetError() << endl;
            //throw runtime_error("Failed to initialize SDL_net");
        }
    }

    ~NetworkManager() {
        SDLNet_Quit();
    }

    bool connectToHost(const string& host, Uint16 port) {
        IPaddress ip;
        if (SDLNet_ResolveHost(&ip, host.c_str(), port) < 0) {
            network_file << "Failed to resolve host: " << SDLNet_GetError() << endl;
            return false;
        }
        socket = SDLNet_TCP_Open(&ip);
        if (!socket) {
            network_file << "Failed to open socket: " << SDLNet_GetError() << endl;
            return false;
        }
        return true;
    }

    bool waitForConnection(Uint16 port) {
        IPaddress ip;
        if (SDLNet_ResolveHost(&ip, NULL, port) < 0) {
            network_file << "Failed to resolve host for server: " << SDLNet_GetError() << endl;
            return false;
        }
        serverSocket = SDLNet_TCP_Open(&ip);
        if (!serverSocket) {
            network_file << "Failed to open server socket: " << SDLNet_GetError() << endl;
            return false;
        }
        network_file << "Waiting for client connection..." << endl;
        socket = SDLNet_TCP_Accept(serverSocket);
        if (!socket) {
            network_file << "No client connected." << endl;
            return false;
        }
        return true;
    }

    string getIP(TCPsocket sock) {
        IPaddress* remoteIP = SDLNet_TCP_GetPeerAddress(sock);
        if (!remoteIP) {
            network_file << "Failed to get peer address: " << SDLNet_GetError() << endl;
            return "";
        }
        Uint32 ip = SDL_SwapBE32(remoteIP->host);
        return to_string((ip >> 24) & 0xFF) + "." +
               to_string((ip >> 16) & 0xFF) + "." +
               to_string((ip >> 8) & 0xFF) + "." +
               to_string(ip & 0xFF);
    }

    bool createUDP(Uint16 port) {
        udpSocket = SDLNet_UDP_Open(port);
        if (!udpSocket) {
            network_file << "Failed to open UDP socket: " << SDLNet_GetError() << endl;
            return false;
        }
        return true;
    }

    bool bindUDP(const string& host, Uint16 port) {
        if (SDLNet_ResolveHost(&udpIP, host.c_str(), port) < 0) {
            network_file << "Failed to resolve UDP host: " << SDLNet_GetError() << endl;
            return false;
        }
        return true;
    }

    bool sendUDP(const void* data, int len) {
        UDPpacket packet;
        packet.data = (Uint8*)data;
        packet.len = len;
        packet.address = udpIP;
        if (SDLNet_UDP_Send(udpSocket, -1, &packet) == 0) {
            network_file << "Failed to send UDP packet: " << SDLNet_GetError() << endl;
            return false;
        }
        return true;
    }

    int receiveUDP(void* buffer, int maxlen) {
        UDPpacket packet;
        packet.data = (Uint8*)buffer;
        packet.maxlen = maxlen;
        if (SDLNet_UDP_Recv(udpSocket, &packet) == 0) {
            network_file << "No UDP packet received." << endl;
            return 0;
        }
        return packet.len;
    }

private:
    TCPsocket socket;
    TCPsocket serverSocket;
    UDPsocket udpSocket;
    IPaddress udpIP;
};