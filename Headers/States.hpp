class State{
    public:
    State(const char* stname = ""): name(stname){}
    ~State(){}
    virtual void update(InputManager&) = 0;
    virtual void render(SDL_Renderer*) = 0;
    virtual void init() = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void cleanup() = 0;
    virtual string getID() const = 0;
    protected:
    string name;
};
class StateManager{
    public:
    StateManager(){}
    ~StateManager(){}
    State* getCurrent() const{
        return gStates.back();
    }
    void pushState(State* pState){
        if(pState){
            if(!gStates.empty()){
                if(gStates.back()->getID() == pState->getID())return;
            }
            gStates.push_back(pState);
            pState->onEnter();
        }
        return;
    }
    void changeState(State* pState){
        if(!gStates.empty()){
            if(!pState)return;
            if(gStates.back()->getID() == pState->getID()){
                return;
            }
            gStates.back()->onExit();
            //delete gStates.back();
            gStates.pop_back();
        }
        pushState(pState);
    }
    void popState(){
        if(!gStates.empty()){
            gStates.back()->onExit();
            //delete gStates.back();
            gStates.pop_back();
        }
    }
    void update(InputManager& input){
        if(!gStates.empty()){
            gStates.back()->update(input);
        }
    }
    void render(SDL_Renderer* rend){
        if(!gStates.empty()){
            gStates.back()->render(rend);
        }
    }
    private:
    vector<State*> gStates;
};
template <class T>
struct ChangeStateCommand : public command <T> {
    StateManager& manager;
    State* nextState;
    enum func{pushit, changeit, popit}type;
    ChangeStateCommand(StateManager& stman, State* next = NULL, func typedo = pushit): command<T>(), manager(stman), nextState(next), type(typedo){}
    void setNext(State* next, func typedo = pushit){
        nextState = next;
        type = typedo;
    }
    void setRef(StateManager* stman) {
        manager = stman;
    }
    StateManager* getRef() const {
        return &manager;
    }
    void execute() override {
        switch (type){
            case pushit:
            manager.pushState(nextState);
            break;
            case changeit:
            manager.changeState(nextState);
            break;
            case popit:
            manager.popState();
            break;
            default:
            manager.pushState(nextState);
            break;
        }
    }
};
class MenuState : public State{
    vector<UIContainer> UICs;
    vector<SDL_Texture*> textures;
    public:
    MenuState(const char* id = "Menu State"): State(id) {}
    int size(){
        return UICs.size();
    }
    vector<UIContainer>& getUICs(){
        return UICs;
    }
    void push(const UIContainer& uic){
        UICs.push_back(uic);
        textures.push_back(NULL);
    }
    void pop(){
        if(!UICs.empty()){
            UICs.pop_back();
            if(!textures.empty()){
                SDL_DestroyTexture(textures.back());
                textures.pop_back();
            }
        }
    }
    void update(InputManager& input) override {
        for(UIContainer& uic : UICs)
        uic.update(input);
        // Update logic for menu state
    }
    void render(SDL_Renderer* rend) override{
        int size = UICs.size();
        if(!size){
            return;
        }
        for(int i = 0; i < size; i++)
        UICs[i].render(rend, textures[i]);
    }
    void init() override {
        // Initialization logic for menu state
    }
    void cleanup() override {
        for(UIContainer& uic : UICs){
            uic.getList().clear();
        }
        UICs.clear();
        for(SDL_Texture* tex : textures){
            if(tex){
                SDL_DestroyTexture(tex);
            }
        }
        textures.clear();
        // Cleanup logic for menu state
    }
    void onEnter() override {
        return;
    }
    void onExit() override {
        return;
    }
    string getID() const{
        return name;
    }
};
class AnimationState : public State{

};