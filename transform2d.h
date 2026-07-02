#ifndef H_RENDERER2D_TRANSFORM2D
#define H_RENDERER2D_TRANSFORM2D

#include <math.h>

#include "type.h"
#include "matrix.h"
#include "vector.h"

typedef struct {
  vec2i32_t   translation;
  vec2i32_t   origin;
  vec2f32_t   scale;
  f32_t       rotation;
} transform2d_t;

mat3x3f32_t   transform2d_to_mat3x3f32(transform2d_t* transform);
transform2d_t transform2d_create(vec2i32_t* vertecies, i8_t length);

#endif
