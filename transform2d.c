#include "transform2d.h"

void transform2d_apply(transform2d_t* transform, vec2u32_t* vertecies, i8_t length)
{
  u32_t x = 0;
  u32_t y = 0;

  for(i8_t index = 0; index < length; index++)
  {
    x = (transform->basis.x.x * vertecies[index].x) +
        (transform->basis.x.y * vertecies[index].y) +
        transform->translation.x;
    y = (transform->basis.y.x * vertecies[index].x) +
        (transform->basis.y.y * vertecies[index].y) +
        transform->translation.x;
    vertecies[index].x = x;
    vertecies[index].y = y;
  }
}

void transform2d_scale(vec2f32_t *scale)
{}

void transform2d_rotate(f32_t radiants)
{}
