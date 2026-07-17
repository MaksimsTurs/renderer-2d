#ifndef H_RENDERER2D_UTILS
#define H_RENDERER2D_UTILS

#include "type.h"
#include "vector.h"

#define MIN(a, b) (a > b ? b : a)
#define MAX(a, b) (a > b ? a : b)
#define UNUSED(var) ((void)var)

i32_t triangle_edge(vec2i32_t a, vec2i32_t b, vec2i32_t c);

#endif
