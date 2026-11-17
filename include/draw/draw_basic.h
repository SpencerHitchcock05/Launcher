#pragma once
#include <SDL2/SDL.h>
#include "util/utils.h"

void fillRect(SDL_Renderer* ren, int x, int y, int w, int h, Color c);

void drawRect(SDL_Renderer* ren, int x, int y, int w, int h, Color c, int thickness = 1);

void drawBox(SDL_Renderer* ren, int x, int y, int w, int h,
             Color fill, Color border, int borderThickness = 2);