#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

bool initText();                                   
TTF_Font* loadFont(const std::string& path, int size);
void closeFont(TTF_Font* font);

void drawText(SDL_Renderer* ren, TTF_Font* font, const std::string& text,
              int x, int y, SDL_Color color);

void clearTextCache();                             // call before destroying the renderer
void closeText();                                  // call at shutdown