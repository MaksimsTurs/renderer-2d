#ifndef H_RENDERER2D_TRANSFORM2D
#define H_RENDERER2D_TRANSFORM2D

#include "type.h"
#include "matrix.h"
#include "vector.h"

typedef struct {
  vec2u32_t   translation;
  mat2x2f32_t basis;
} transform2d_t;

void transform2d_apply(transform2d_t* transform, vec2u32_t* vertecies, i8_t length);
void transform2d_rotate(f32_t radiants);
void transform2d_scale(vec2f32_t* scale);

#endif
