#include "math.h"

mat3x3f_t mat3x3f_new(vec3f_t translation, vec3f_t scale, float rotation)
{
  return (mat3x3f_t){
    .x = { 
      scale.x * cosf(rotation), 
      -scale.y * sin(rotation),
      translation.x 
    },
    .y = { 
      scale.x * sinf(rotation),
      scale.y * cosf(rotation),
      translation.y 
    },
    .z = { 0.0f, 0.0f, 1.0f }
  };
};


void mat3x3f_apply(mat3x3f_t* maxtrix, vec2f_t* verticies, unsigned char count)
{
  // TODO: Get center point from somewhere else.
  const float xc = 125.0f;
  const float yc = 125.0f;

  for(unsigned char index = 0; index < count; index++)
  {
    const float x = 
        (maxtrix->x->x * (verticies[index].x - xc)) + 
        (maxtrix->x->y * (verticies[index].y - yc)) +
        (maxtrix->x->z + xc);
    const float y = 
        (maxtrix->y->x * (verticies[index].x - xc)) + 
        (maxtrix->y->y * (verticies[index].y - yc)) +
        (maxtrix->y->z + yc);

    verticies[index].x = x;
    verticies[index].y = y;
  }
}
