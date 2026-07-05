#include "include/vector.h"

i32_t vec2i32_determinant(vec2i32_t a, vec2i32_t b, vec2i32_t c)
{
  const i32_t abx = b.x - a.x;
  const i32_t aby = b.y - a.y;
  const i32_t acx = c.x - a.x;
  const i32_t acy = c.y - a.y;

  return acx * aby - acy * abx;
}
