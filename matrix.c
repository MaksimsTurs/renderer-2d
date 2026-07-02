#include "matrix.h"

void mat3x3f32_apply(mat3x3f32_t *matrix, vec2i32_t origin, vec2i32_t* vertecies, vec2i32_t* buffer, i8_t length)
{
  i32_t x = 0;
  i32_t y = 0;

  for(i8_t index = 0; index < length; index++)
  {
    x = (matrix->x.x * (vertecies[index].x - origin.x)) +
        (matrix->x.y * (vertecies[index].y - origin.y)) +
        matrix->x.z;
    y = (matrix->y.x * (vertecies[index].x - origin.x)) +
        (matrix->y.y * (vertecies[index].y - origin.y)) +
        matrix->y.z;
    buffer[index].x = x;
    buffer[index].y = y;
  }
}
