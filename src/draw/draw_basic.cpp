#include "util/utils.h"
#include "draw/draw_basic.h"

void fillRect(SDL_Renderer* ren, int x, int y, int w, int h, Color c) {
    SDL_SetRenderDrawBlendMode(ren, c.a < 255 ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
    SDL_Rect rect{x, y, w, h};
    SDL_RenderFillRect(ren, &rect);
}

void drawRect(SDL_Renderer* ren, int x, int y, int w, int h, Color c, int thickness) {
    if (thickness < 1) return;
    if (thickness * 2 >= w || thickness * 2 >= h) {   
        fillRect(ren, x, y, w, h, c);
        return;
    }
    fillRect(ren, x, y, w, thickness, c);                              
    fillRect(ren, x, y + h - thickness, w, thickness, c);              
    fillRect(ren, x, y + thickness, thickness, h - 2 * thickness, c);  
    fillRect(ren, x + w - thickness, y + thickness,
             thickness, h - 2 * thickness, c);                        
}

void drawBox(SDL_Renderer* ren, int x, int y, int w, int h,
             Color fill, Color border, int borderThickness) {
    fillRect(ren, x, y, w, h, fill);
    drawRect(ren, x, y, w, h, border, borderThickness);
}