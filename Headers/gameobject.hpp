class GameObject{
    virtual void update(InputManager&) = 0;
    virtual void render(SDL_Renderer*, int) = 0;
    // virtual void clean() = 0;
};
