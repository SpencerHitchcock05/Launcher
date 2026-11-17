#include "draw/draw_text.h"
#include <cstdio>
#include <cstdint>
#include <unordered_map>

namespace {
struct Entry { SDL_Texture* tex; int w, h; };
std::unordered_map<std::string, Entry> cache;
}

bool initText() {
    if (TTF_WasInit()) return true;
    if (TTF_Init() != 0) {
        std::fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

TTF_Font* loadFont(const std::string& path, int size) {
    TTF_Font* f = TTF_OpenFont(path.c_str(), size);
    if (!f) std::fprintf(stderr, "TTF_OpenFont(%s) failed: %s\n", path.c_str(), TTF_GetError());
    return f;
}

void clearTextCache() {
    for (auto& kv : cache) SDL_DestroyTexture(kv.second.tex);
    cache.clear();
}

void closeFont(TTF_Font* font) {
    if (!font) return;
    clearTextCache();   // cached entries are keyed by font pointer, so drop them
    TTF_CloseFont(font);
}

void drawText(SDL_Renderer* ren, TTF_Font* font, const std::string& text,
              int x, int y, SDL_Color color) {
    if (!font || text.empty()) return;

    std::string key = std::to_string(reinterpret_cast<std::uintptr_t>(font)) + ":" + text;
    auto it = cache.find(key);

    if (it == cache.end()) {
        // Render in white once; the color is applied at draw time below.
        SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), SDL_Color{255, 255, 255, 255});
        if (!surf) return;
        SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
        Entry e{tex, surf->w, surf->h};
        SDL_FreeSurface(surf);
        if (!tex) return;

        if (cache.size() > 512) clearTextCache();   // stops changing strings (a clock) growing it forever
        it = cache.emplace(key, e).first;
    }

    Entry& e = it->second;
    SDL_SetTextureColorMod(e.tex, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(e.tex, color.a);
    SDL_SetTextureBlendMode(e.tex, SDL_BLENDMODE_BLEND);
    SDL_Rect dst{x, y, e.w, e.h};
    SDL_RenderCopy(ren, e.tex, nullptr, &dst);
}

void closeText() {
    clearTextCache();
    TTF_Quit();
}