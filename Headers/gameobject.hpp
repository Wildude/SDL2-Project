class GameObject{
    virtual void update(InputManager&) = 0;
    virtual void render(SDL_Renderer*, SDL_Texture*&, int) = 0;
    // virtual void clean() = 0;
};
