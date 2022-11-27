#include "sdl_env.h"
#include "common.h"
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
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void create_sdl_env(SDLEnv* env)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        PANIC("failed to initialize sdl: %s", SDL_GetError());

    if (SDL_CreateWindowAndRenderer(1280, 720, 0, &env->window, &env->renderer) < 0)
        PANIC("failed to initialize window and renderer: %s", SDL_GetError());

    SDL_SetWindowTitle(env->window, "EUD Platformer");

    if (TTF_Init() < 0)
        PANIC("couldn't initialize SDL_ttf: %s", SDL_GetError());

    env->font = TTF_OpenFont("assets/font.ttf", 36);
    if (!env->font) {
        PANIC("couldn't load font: %s", SDL_GetError());
    }
}

void destroy_sdl_env(SDLEnv* env)
{
    TTF_CloseFont(env->font);
    TTF_Quit();
    SDL_DestroyRenderer(env->renderer);
    SDL_DestroyWindow(env->window);
    SDL_Quit();
}

void sdl_env_delay(SDLEnv* env, uint32_t ms)
{
    (void)env;
    SDL_Delay(ms);
}

void create_sdl_graphics(SDLGraphics* graphics, SDLEnv* env)
{
    *graphics = (SDLGraphics) {
        .present = sdl_graphics_present,
        .clear = sdl_graphics_clear,
        .draw_rect = sdl_graphics_draw_rect,
        .env = env,
    };
}
void destroy_sdl_graphics(SDLGraphics* graphics) { (void)graphics; }

void sdl_graphics_present(SDLGraphics* graphics) { SDL_RenderPresent(graphics->env->renderer); }

void sdl_graphics_clear(SDLGraphics* graphics, Color color)
{
    sdl_graphics_set_color(graphics, color);
    SDL_RenderClear(graphics->env->renderer);
}

void sdl_graphics_draw_rect(SDLGraphics* graphics, int x, int y, int width, int height, Color color)
{
    sdl_graphics_set_color(graphics, color);
    SDL_RenderFillRect(graphics->env->renderer, &(SDL_Rect) { x, y, width, height });
}

void sdl_graphics_set_color(SDLGraphics* graphics, Color color)
{

    SDL_SetRenderDrawColor(
        graphics->env->renderer, color.red, color.green, color.blue, color.alpha);
}
