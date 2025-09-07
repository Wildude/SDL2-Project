#include <States.hpp>
// State
State::State(const char* stname ): name(stname){}
State::~State(){}
//virtual void State::update(InputManager&) = 0;
//virtual void State::render(SDL_Renderer*) = 0;
//virtual void State::init() = 0;
//virtual void State::onEnter() = 0;
//virtual void State::onExit() = 0;
//virtual void State::cleanup() = 0;
//virtual string State::getID() const = 0;

// StateManager
StateManager::StateManager(){}
StateManager::~StateManager(){}
State* StateManager::getCurrent() const{
    return gStates.back();
}
void StateManager::pushState(State* pState){
    if(pState){
        if(!gStates.empty()){
            if(gStates.back()->getID() == pState->getID())return;
        }
        gStates.push_back(pState);
        pState->onEnter();
    }
    return;
}
void StateManager::changeState(State* pState){
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
void StateManager::popState(){
    if(!gStates.empty()){
        gStates.back()->onExit();
        //delete gStates.back();
        gStates.pop_back();
    }
}
void StateManager::update(InputManager& input){
    if(!gStates.empty()){
        gStates.back()->update(input);
    }
}
void StateManager::render(SDL_Renderer* rend){
    if(!gStates.empty()){
        gStates.back()->render(rend);
    }
}
//
MenuState::MenuState(const char* id ): State(id) {}
int MenuState::size(){
    return UICs.size();
}
std::vector<UIContainer>& MenuState::getUICs(){
    return UICs;
}
void MenuState::push(const UIContainer& uic){
    UICs.push_back(uic);
}
void MenuState::pop(){
    if(!UICs.empty()){
        UICs.pop_back();
    }
}
void MenuState::update(InputManager& input) /* override */ {
    for(UIContainer& uic : UICs)
    uic.update(input);
    // Update logic for menu state
}
void MenuState::render(SDL_Renderer* rend) /* override */{
    int size = UICs.size();
    if(!size){
        return;
    }
    for(int i = 0; i < size; i++)
    UICs[i].render(rend);
}
void MenuState::init() /* override */ {
    // Initialization logic for menu state
}
void MenuState::cleanup() /* override */ {
    for(UIContainer& uic : UICs){
        uic.getList().clear();
    }
    UICs.clear();
    // Cleanup logic for menu state
}
void MenuState::onEnter() /* override */ {
    return;
}
void MenuState::onExit() /* override */ {
    return;
}
std::string MenuState::getID() const{
    return name;
}
/*
class AnimationState : public State{

};
*/