#include <SDL2/SDL.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 400;
const int FIGHTER_WIDTH = 50;
const int FIGHTER_HEIGHT = 100;

// Health
int player1_health = 100;
int player2_health = 100;

void drawHealthBars(SDL_Renderer* renderer) {
    // Player 1 health bar
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect health1 = {50, 20, player1_health * 2, 20};
    SDL_RenderFillRect(renderer, &health1);

    // Player 2 health bar
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect health2 = {WIDTH - 250, 20, player2_health * 2, 20};
    SDL_RenderFillRect(renderer, &health2);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("2D Fighting Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect player1 = {100, HEIGHT - FIGHTER_HEIGHT, FIGHTER_WIDTH, FIGHTER_HEIGHT};
    SDL_Rect player2 = {WIDTH - 150, HEIGHT - FIGHTER_HEIGHT, FIGHTER_WIDTH, FIGHTER_HEIGHT};
    SDL_Event e;
    bool quit = false;
    int player_speed = 1;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);

        // Player 1 movement
        if (state[SDL_SCANCODE_A] && player1.x > 0) player1.x -= player_speed;
        if (state[SDL_SCANCODE_D] && player1.x < WIDTH - FIGHTER_WIDTH) player1.x += player_speed;
        if (state[SDL_SCANCODE_W] && player1.y > 0) player1.y -= player_speed;
        if (state[SDL_SCANCODE_S] && player1.y < HEIGHT - FIGHTER_HEIGHT) player1.y += player_speed;

        // Player 2 movement
        if (state[SDL_SCANCODE_LEFT] && player2.x > 0) player2.x -= player_speed;
        if (state[SDL_SCANCODE_RIGHT] && player2.x < WIDTH - FIGHTER_WIDTH) player2.x += player_speed;
        if (state[SDL_SCANCODE_UP] && player2.y > 0) player2.y -= player_speed;
        if (state[SDL_SCANCODE_DOWN] && player2.y < HEIGHT - FIGHTER_HEIGHT) player2.y += player_speed;

        // Simple attack mechanics
        if (state[SDL_SCANCODE_SPACE] && SDL_HasIntersection(&player1, &player2)) {
            player2_health = std::max(0, player2_health - 1);
        }
        if (state[SDL_SCANCODE_RETURN] && SDL_HasIntersection(&player2, &player1)) {
            player1_health = std::max(0, player1_health - 1);
        }

        // Win condition
        if (player1_health <= 0 || player2_health <= 0) {
            std::cout << (player1_health <= 0 ? "Player 2 Wins!" : "Player 1 Wins!") << std::endl;
            quit = true;
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render players
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player1);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &player2);

        // Render health bars
        drawHealthBars(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
