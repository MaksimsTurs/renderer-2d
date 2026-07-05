#ifndef H_RENDERER2D_TRANSFORM2D
#define H_RENDERER2D_TRANSFORM2D

#include <math.h>

#include "type.h"
#include "matrix.h"
#include "vector.h"

typedef struct {
  vec2f32_t   translation;
  vec2f32_t   origin;
  vec2f32_t   scale;
  f32_t       rotation;
} transform2d_t;

transform2d_t transform2d_create_from_vertecies(vec2f32_t* vertecies, i8_t length);
mat3x3f32_t   transform2d_to_mat3x3f32(transform2d_t* transform);

#endif
