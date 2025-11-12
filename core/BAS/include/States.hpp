#pragma once
#include <inputManager.hpp>
#include <GUI.hpp>
#include <iostream>
#include <vector>
class State{
    public:
    State(const char* stname = "");
    ~State();
    virtual void update(InputManager&) = 0;
    virtual void render(SDL_Renderer*) = 0;
    virtual void init() = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void cleanup() = 0;
    virtual std::string getID() const = 0;
    protected:
    std::string name;
};
class StateManager{
    public:
    StateManager();
    ~StateManager();
    State* getCurrent() const;
    void pushState(State* pState);
    void changeState(State* pState);
    void popState();
    void update(InputManager& input);
    void render(SDL_Renderer* rend);
    private:
    std::vector<State*> gStates;
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
    ChangeStateCommand* clone() const override {
        return new ChangeStateCommand(manager, nextState, type);
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
    std::vector<UIContainer> UICs;
    public:
    MenuState(const char* id = "Menu State");
    int size();
    std::vector<UIContainer>& getUICs();
    void push(const UIContainer& uic);
    void pop();
    void update(InputManager& input) override ;
    void render(SDL_Renderer* rend) override;
    void init() override ;
    void cleanup() override ;
    void onEnter() override ;
    void onExit() override ;
    std::string getID() const;
};
class AnimationState : public State{

};