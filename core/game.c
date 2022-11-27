#include "game.h"
#include "common.h"
#include <stdlib.h>

void create_game(Game* game)
{
    *game = (Game) {
        .add_object = game_add_object,
        .objects = malloc(sizeof(Object*) * GAME_OBJECTS_CHUNK),
    };
}

void destroy_game(Game* game)
{
    if (game->objects)
        free(game->objects);
}

void game_update(Game* game, double delta)
{
    for (size_t i = 0; i < game->objects_size; i++)
        CALL_VIRTUAL(game->objects[i], update, (Context*)game, delta);
}

void game_add_object(Game* game, Object* object)
{
    if (game->objects_size >= game->objects_capacity) {
        game->objects_capacity += GAME_OBJECTS_CHUNK;
        game->objects = realloc(game->objects, game->objects_capacity);
        if (game->objects == NULL)
            PANIC("allocation error, 'realloc' failed");
    }
    game->objects[game->objects_size] = object;
    game->objects_size++;
}
