#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define CALL_VIRTUAL(SELF, FIELD_NAME, ...) (SELF->FIELD_NAME(SELF, __VA_ARGS__))

#define PANIC(...)                                                                                 \
    (printf("panic: "), printf(__VA_ARGS__), printf("\n  at ./%s:%d:", __FILE__, __LINE__), exit(1))

#endif
