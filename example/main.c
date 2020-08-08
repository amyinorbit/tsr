#include <tsr/tsr.h>
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

void debug_tsr(const tsr_surface_t *fb) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *w;
    SDL_Renderer *r;
    tsr_vec2_t size = tsr_surface_size(fb);


    SDL_CreateWindowAndRenderer(size.x, size.y, SDL_WINDOW_SHOWN, &w, &r);
    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(
        (void*)tsr_surface_pixels(fb),
        size.x, size.y,
        32, size.x*4,
        0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
    );

    if (surf == NULL) {
      SDL_Log("Creating surface failed: %s", SDL_GetError());
      exit(1);
    }


    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, surf);
    SDL_FreeSurface(surf);

    bool quit = false;
    while(!quit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) quit = true;
        }
        SDL_SetRenderDrawColor(r, 0, 0, 0, 0xff);
        SDL_RenderClear(r);
        SDL_RenderCopy(r, tex, NULL, NULL);
        SDL_RenderPresent(r);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
}

int main() {

    tsr_surface_t *font = tsr_surface_load("test-image.png");
    tsr_surface_t *buffer = tsr_surface_new(24 * 12, 11 * 18);
    tsr_target_t *target = tsr_target_new(buffer);

    tsr_rect_t character = tsr_rect(tsr_vec2(12, 0), tsr_vec2(12, 18));
    tsr_color(target, 0, 0, 0, 1);
    tsr_clear(target);
    tsr_color(target, 1, 0, 1, 1);
    tsr_blit_ex(target, font, tsr_vec2(20, 20), &character);

    tsr_rect_t test = tsr_rect(tsr_vec2(50, 50), tsr_vec2(100, 50));
    // tsr_move_to(target, 50, 50);
    tsr_box(target, &test, 1);

    tsr_vline(target, 100, 30, 80, 4);
    tsr_color(target, 0.f, 1.f, 1.f, 0.5f);
    tsr_hline(target, 100, 30, 80, 4);

    debug_tsr(buffer);

    tsr_target_delete(target);
    tsr_surface_delete(font);
}
