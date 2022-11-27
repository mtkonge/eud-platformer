#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct Object Object;

typedef struct Context {
    void (*add_object)(struct Context* context, Object* object);
} Context;

typedef struct Object {
    void (*create)(struct Object* object, Context* context);
    void (*destroy)(struct Object* object, Context* context);
    void (*update)(struct Object* object, Context* context, double delta);
    void (*render)(struct Object* object, Graphics* graphics);
} Object;

#define GAME_OBJECTS_CHUNK 8192

typedef struct Game {
    void (*add_object)(struct Game* context, Object* object);
    Object** objects;
    size_t objects_size, objects_capacity;
} Game;

void create_game(Game* game);
void destroy_game(Game* game);
void game_update(Game* game, double delta);
void game_add_object(Game* game, Object* object);

#endif
