#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Rectangle points
struct Point {
    float x, y;
};
/*

*/
// Rectangle points (relative to its center)
std::vector<Point> rectangle = {
    {SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 100},  // Top-left
    {SCREEN_WIDTH/2 + 50, SCREEN_HEIGHT/2 - 100},   // Top-right
    {SCREEN_WIDTH/2 + 25, SCREEN_HEIGHT/2 + 100},    // Bottom-right
    {SCREEN_WIDTH/2 - 25, SCREEN_HEIGHT/2 + 100}    // Bottom-left
};
/*
// Rectangle points (relative to its center)
std::vector<Point> rectangle = {
    {-100, -50},  // Top-left
    {100, -50},   // Top-right
    {100, 50},    // Bottom-right
    {-100, 50}    // Bottom-left
};
*/

const int DISTANCE = 500; // Perspective distance

// Helper function to find the center of the rectangle
Point calculateCenter(const std::vector<Point>& points) {
    float minX = points[0].x, maxX = points[0].x;
    float minY = points[0].y, maxY = points[0].y;

    for (const auto& point : points) {
        if (point.x < minX) minX = point.x;
        if (point.x > maxX) maxX = point.x;
        if (point.y < minY) minY = point.y;
        if (point.y > maxY) maxY = point.y;
    }

    return {(minX + maxX) / 2, (minY + maxY) / 2};
}

// Projection function
std::vector<Point> project(const std::vector<Point>& points, float angle) {
    std::vector<Point> transformedPoints;
    Point center = calculateCenter(points);

    float angleRad = angle * M_PI / 180.0f;
    float cosTheta = std::cos(angleRad);
    float sinTheta = std::sin(angleRad);

    for (const auto& point : points) {
        // Translate point relative to the center
        float xRel = point.x - center.x;
        float yRel = point.y - center.y;

        // Simulate z-axis rotation
        float z = xRel * sinTheta;
        float xNew = xRel * cosTheta;

        // Perspective scaling
        float scale = DISTANCE / (DISTANCE - z);
        float yNew = yRel * scale;

        // Translate back to the original position
        transformedPoints.push_back({ xNew + center.x, yNew + center.y });
    }

    return transformedPoints;
}
/*
// Draw the rectangle
void drawRectangle(SDL_Renderer* renderer, const std::vector<Point>& points) {
    // Draw the rectangle
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
    for (size_t i = 0; i < points.size(); i++) {
        const Point& p1 = points[i];
        const Point& p2 = points[(i + 1) % points.size()];
        SDL_RenderDrawLine(renderer,
                           p1.x + SCREEN_WIDTH / 2, p1.y + SCREEN_HEIGHT / 2,
                           p2.x + SCREEN_WIDTH / 2, p2.y + SCREEN_HEIGHT / 2);
    }
}
*/
// Draw the rectangle
void drawRectangle(SDL_Renderer* renderer, const std::vector<Point>& points) {
    // Draw the rectangle
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
    for (size_t i = 0; i < points.size(); i++) {
        const Point& p1 = points[i];
        const Point& p2 = points[(i + 1) % points.size()];
        SDL_RenderDrawLine(renderer,
                           p1.x, p1.y,
                           p2.x, p2.y);
    }
}


// Draw slider
void drawSlider(SDL_Renderer* renderer, int sliderX, int sliderY, int sliderWidth, int sliderHeight, int sliderValue) {
    // Slider background
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_Rect sliderBg = { sliderX, sliderY, sliderWidth, sliderHeight };
    SDL_RenderFillRect(renderer, &sliderBg);

    // Slider handle
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    int handleX = sliderX + (sliderValue * sliderWidth) / 180;
    SDL_Rect sliderHandle = { handleX - 5, sliderY, 10, sliderHeight };
    SDL_RenderFillRect(renderer, &sliderHandle);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("3D Projection (Centered Rotation)",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bool running = true;
    SDL_Event event;
    int sliderValue = 90; // Initial rotation angle (0 to 180 degrees)

    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION) {
                if (event.motion.y >= SCREEN_HEIGHT - 50 && event.motion.y <= SCREEN_HEIGHT - 30) {
                    sliderValue = ((event.motion.x - 50) * 180) / (SCREEN_WIDTH - 100);
                    if (sliderValue < 0) sliderValue = 0;
                    if (sliderValue > 180) sliderValue = 180;
                }
            }
        }

        // Transform points
        std::vector<Point> transformedRectangle = project(rectangle, sliderValue - 90);

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen
        SDL_RenderClear(renderer);

        drawRectangle(renderer, transformedRectangle);

        // Draw slider
        drawSlider(renderer, 50, SCREEN_HEIGHT - 50, SCREEN_WIDTH - 100, 20, sliderValue);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
