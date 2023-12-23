#include <SDL.h>

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(1200, 800, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 4, 4);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, 1200 / 2, 800 / 2);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    return 0;
}