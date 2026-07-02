#include "transform2d.h"

transform2d_t transform2d_create(vec2i32_t *vertecies, i8_t length)
{
  transform2d_t transform = {
    {0, 0},
    {0, 0},
    {1.0f, 1.0f},
    0.0f
  };

  for(i8_t index = 0; index < length; index++)
  {
    transform.origin.x += vertecies[index].x;
    transform.origin.y += vertecies[index].y;
  }

  transform.origin.x /= length;
  transform.origin.y /= length;

  return transform;
}

mat3x3f32_t transform2d_to_mat3x3f32(transform2d_t* transform)
{
  return(mat3x3f32_t){
    {cosf(transform->rotation) * transform->scale.x, -sinf(transform->rotation) * transform->scale.y, transform->translation.x},
    {sinf(transform->rotation) * transform->scale.x,  cosf(transform->rotation) * transform->scale.y, transform->translation.y},
    {1.0f,                                            1.0f,                                           1.0f}
  };
}
