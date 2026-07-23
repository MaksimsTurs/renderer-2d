#include "utils.h"

i32_t triangle_edge(vec2i32_t a, vec2i32_t b, vec2i32_t c)
{
  const vec2i32_t ab = vec2i32_sub(&b, &a);
  const vec2i32_t ac = vec2i32_sub(&c, &a);

  return ac.x * ab.y - ac.y * ab.x;
}
