#include "include/transform2d.h"

transform2d_t transform2d_create_from_vertecies(vec2f32_t *vertecies, i8_t length)
{
  transform2d_t transform = {
    { 0.0f, 0.0f },
    { 0.0f, 0.0f },
    { 1.0f, 1.0f },
    0.0f
  };

  for(i16_t index = 0; index < length; index++)
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
  f32_t cos = cosf(transform->rotation);
  f32_t sin = sinf(transform->rotation);

  return(mat3x3f32_t){
    { cos * transform->scale.x, -sin * transform->scale.y, transform->translation.x },
    { sin * transform->scale.x, cos * transform->scale.y,  transform->translation.y },
    { 0.0f,                     0.0f,                      1.0f }
  };
}
