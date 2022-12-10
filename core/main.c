
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "env_lua.h"
#include "common.h"
#include "game.h"
#include "graphics.h"
#include "sdl_env.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    srand((uint32_t)time(NULL));

    SDLEnv sdl_env;
    create_sdl_env(&sdl_env);

    SDLGraphics graphics;
    create_sdl_graphics(&graphics, &sdl_env);

    lua_State* lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
    if (luaL_loadfile(lua_state, "src/main.lua") != LUA_OK)
        PANIC("failed to load src/main.lua");
    if (lua_pcall(lua_state, 0, 1, 0) != LUA_OK)
        PANIC("failed run src/main.lua");
    lua_pop(lua_state, lua_gettop(lua_state));
    lua_getglobal(lua_state, "setup");
    if (lua_pcall(lua_state, 0, 1, 0) != LUA_OK)
        PANIC("failed run setup() in src/main.lua");
    lua_pushstring(lua_state, "onCreate");
    lua_gettable(lua_state, -2);
    if (lua_pcall(lua_state, 0, 0, 0) != LUA_OK)
        PANIC("failed run onCreate() in src/main.lua");

    Game game;
    create_game(&game);

    SDL_Event event;
    uint32_t time_before = SDL_GetTicks();
    bool running = true;
    while (running) {
        uint32_t time_now = SDL_GetTicks();
        double delta = (time_now - time_before) / (double)1000;
        (void)delta;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }

        game_update(&game, delta);

        sdl_graphics_clear(&graphics, rgb(0, 0, 0));
        sdl_graphics_draw_rect(&graphics, 128, 128, 512, 256, rgb(0, 0xFF, 0xFF));
        sdl_graphics_present(&graphics);
        sdl_env_delay(&sdl_env, 6);
    }

    lua_close(lua_state);
    destroy_game(&game);
    destroy_sdl_env(&sdl_env);
}
