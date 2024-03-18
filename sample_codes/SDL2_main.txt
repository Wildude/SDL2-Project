#include <SDL2/SDL.h>
int main(int arn, char **args)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Delay(2 * 1000);
	SDL_Quit();
}
