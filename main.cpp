#include <iostream>
#include <SDL.h>
#include <thread>
#include "ComplexNumber.h"
#include "ColorConvert.h"

#define WIDTH 1400
#define HEIGHT 800
#define PIXEL_SIZE WIDTH * HEIGHT
#define COLORS 60

void process(int startX, int endX,
            int startY, int endY,
            float scale,
            float re_left, float re_shift,
            float im_top, float im_shift,
            ComplexNumber* c, ComplexNumber* offset,
            int iterations,
            unsigned int* pixels,
            const unsigned int* colors,
            int threshold,
            const unsigned int* black) {
    for (int x = startX; x < endX; x++) {
        float re = scale * (re_left + ((float64_t) x * re_shift));

        for (int y = startY; y < endY; y++) {
            float im = scale * (im_top + ((float64_t) y * im_shift));

            auto base = addComplex(c, ComplexNumber{re, im});
            base = addComplex(&base, offset);

            auto multiplier = ComplexNumber{re, im};
            multiplier = addComplex(&multiplier, offset);

            for (int i = 0; i < iterations; i++) {
                if (lengthComplex(&base) < threshold) {
                    pixels[y * WIDTH + x] = *black;
                    base = addComplex(multiplyComplex(&base, &base), &multiplier);
                } else {
                    pixels[y * WIDTH + x] = colors[i % COLORS];
                    break;
                }
            }
        }
    }
}

int main() {
    auto scale = 2.0f;

    int iterations = 2;

    auto offset = ComplexNumber{-0.4, 0};

    auto c = ComplexNumber{0, 0};

    float64_t re_left = -1.0f;
    float64_t re_shift = 2.0f / (float) WIDTH;

    float64_t im_top = -1.0f;
    float64_t im_shift = 2.0f / (float) HEIGHT;

    auto pixel_size = WIDTH * HEIGHT;

    int threshold = 1;


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Hello, World!", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_POPUP_MENU);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    auto* pixels = (unsigned int*)surface->pixels;

    SDL_Renderer* renderer = SDL_GetRenderer(window);
    bool running = true;

    const unsigned int BLACK = SDL_MapRGB(surface->format, 0, 0, 0);

    unsigned int colors[COLORS];

    int color_offset = 0;

    while (running) {
        bool hasUpdated = false;
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        const Uint8* key_state = SDL_GetKeyboardState(NULL);

        if (key_state[SDL_SCANCODE_D]) {
            offset = addComplex(&offset, ComplexNumber{0.01f * scale, 0});
            hasUpdated = true;
        }
        if (key_state[SDL_SCANCODE_A]) {
            offset = addComplex(&offset, ComplexNumber{-0.01f * scale, 0});
            hasUpdated = true;
        }
        if (key_state[SDL_SCANCODE_W]) {
            offset = addComplex(&offset, ComplexNumber{0, -0.01f * scale});
            hasUpdated = true;
        }
        if(key_state[SDL_SCANCODE_S]) {
            offset = addComplex(&offset, ComplexNumber{0, 0.01f * scale});
            hasUpdated = true;
        }
        if(key_state[SDL_SCANCODE_E]) {
            scale *= 0.9;
            hasUpdated = true;
        }
        if(key_state[SDL_SCANCODE_Q]) {
            scale /= 0.9;
            hasUpdated = true;
        }
        if(key_state[SDL_SCANCODE_RIGHT]) {
            iterations += 1;
            hasUpdated = true;
        }
        if(key_state[SDL_SCANCODE_LEFT]) {
            iterations -= 1;
            hasUpdated = true;
        }
        if(key_state[SDL_SCANCODE_UP]) {
            threshold += 1;
            hasUpdated = true;
        }
        if(key_state[SDL_SCANCODE_DOWN]) {
            threshold -= 1;
            hasUpdated = true;
        }

        if (key_state[SDL_SCANCODE_Z]) {
            color_offset += 1;
            for (int i = 0 ; i < COLORS ; i ++) {
                RGB col = HSLToRGB(HSL(color_offset + i * 360 / COLORS, 1.0f, 0.5f));
                colors[i] = SDL_MapRGB(surface->format, col.R, col.G, col.B);
            }
            hasUpdated = true;
        }
        if (key_state[SDL_SCANCODE_X]) {
            color_offset -= 1;
            for (int i = 0 ; i < COLORS ; i ++) {
                RGB col = HSLToRGB(HSL(color_offset + i * 360 / COLORS, 1.0f, 0.5f));
                colors[i] = SDL_MapRGB(surface->format, col.R, col.G, col.B);
            }
            hasUpdated = true;
        }

        if(key_state[SDL_SCANCODE_ESCAPE]) {
            running = false;
        }
        if (!hasUpdated) { continue; }
        SDL_LockSurface(surface);
        std::thread draw(SDL_UpdateWindowSurface, window);

        int thread_count = HEIGHT;
        std::thread THREADS[thread_count];
        for (int i = 0 ; i < thread_count ; i ++) {
            std::thread t(process, 0, WIDTH, HEIGHT * i/thread_count, HEIGHT * (i + 1)/thread_count, scale, re_left, re_shift, im_top, im_shift, &c, &offset, iterations, pixels, colors, threshold, &BLACK);
            THREADS[i].swap(t);
        }
        for (int i = 0 ; i < thread_count ; i ++) {
            THREADS[i].join();
        }
        draw.join();

        SDL_UnlockSurface(surface);
    }


//        SDL_Event e; bool running = false; while( running == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) running = true; } }

    return 0;
}
