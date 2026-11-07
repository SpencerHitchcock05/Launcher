#include <iostream>
#include <SDL2/SDL.h>

int main(int, char**) {
    std::cout << "Hello WOrleds" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Launcher", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (win == nullptr || ren == nullptr) {
        std::cerr << "SDL_CreateWindow or SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_RenderSetLogicalSize(ren, 640, 480);

    SDL_Rect box{300, 220, 40, 40};

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP]) {
            box.y -= 5;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            box.y += 5;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            box.x -= 5;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            box.x += 5;
        }   

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);  
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        SDL_RenderFillRect(ren, &box);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}