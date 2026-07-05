#include "include/camera2d.h"

camera2d_t camera2d_create(f32_t left, f32_t right, f32_t top, f32_t bottom)
{
  return(camera2d_t){
    {{ 0.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f },
    mat3x3f32_orthographic(left, right, top, bottom),
  };
}
