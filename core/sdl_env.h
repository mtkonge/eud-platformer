#ifndef SDL_ENVIRONMENT_H
#define SDL_ENVIRONMENT_H

#include "game.h"
#include <SDL.h>
#include <SDL_blendmode.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_log.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_scancode.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL_video.h>
#include <stdint.h>

typedef struct SDLEnv {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
} SDLEnv;

void create_sdl_env(SDLEnv* env);
void destroy_sdl_env(SDLEnv* env);
void sdl_env_delay(SDLEnv* env, uint32_t ms);

typedef struct SDLGraphics {
    void (*present)(struct SDLGraphics* graphics);
    void (*clear)(struct SDLGraphics* graphics, Color color);
    void (*draw_rect)(
        struct SDLGraphics* graphics, int x, int y, int width, int height, Color color);
    SDLEnv* env;
} SDLGraphics;

void create_sdl_graphics(SDLGraphics* graphics, SDLEnv* env);
void destroy_sdl_graphics(SDLGraphics* graphics);
void sdl_graphics_present(SDLGraphics* graphics);
void sdl_graphics_clear(SDLGraphics* graphics, Color color);
void sdl_graphics_draw_rect(
    SDLGraphics* graphics, int x, int y, int width, int height, Color color);
void sdl_graphics_set_color(SDLGraphics* graphics, Color color);

#endif
