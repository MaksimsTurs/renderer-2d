#include "include/transform.h"

void transfrom2d_look_at(transform2d_t* transform, const vec2f32_t* position, const vec2f32_t* target)
{
  vec2f32_t distance = vec2f32_sub(target, position);

  transform->rotation = atan2f(distance.y, distance.x);
}

void transform2d_to_mat3x3f32(const transform2d_t *transform, f32_t buffer[9])
{
  const f32_t c = cosf(transform->rotation);
  const f32_t s = sinf(transform->rotation);

  buffer[0] = c * transform->scale.x;
  buffer[1] = -s * transform->scale.y;
  buffer[2] = transform->translation.x;
  buffer[3] = s * transform->scale.x;
  buffer[4] = c * transform->scale.y;
  buffer[5] = transform->translation.y;
  buffer[6] = 0.0f;
  buffer[7] = 0.0f;
  buffer[8] = 1.0f;
}
