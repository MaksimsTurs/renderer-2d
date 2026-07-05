#ifndef H_RENDERER2D_CAMERA2D
#define H_RENDERER2D_CAMERA2D

#include "matrix.h"
#include "transform2d.h"
#include "type.h"

typedef struct {
  transform2d_t transform;
  mat3x3f32_t   projection;
} camera2d_t;

camera2d_t camera2d_create(f32_t left, f32_t right, f32_t top, f32_t bottom);

#endif
