#include "vector.h"

i32_t vec2u32_calc_determinant(vec2u32_t a, vec2u32_t b, vec2u32_t c)
{
  const i32_t abx = (i32_t)b.x - a.x;
  const i32_t aby = (i32_t)b.y - a.y;
  const i32_t acx = (i32_t)c.x - a.x;
  const i32_t acy = (i32_t)c.y - a.y;

  return acx * aby - acy * abx;
}
