#include "includes/matrix.h"

mat3x3f32_t mat3x3f32_mul_mat3x3f32(const mat3x3f32_t* a, const mat3x3f32_t* b)
{
  return(mat3x3f32_t){
    {
      a->data[0] * b->data[0] + a->data[1] * b->data[3] + a->data[2] * b->data[6],
      a->data[0] * b->data[1] + a->data[1] * b->data[4] + a->data[2] * b->data[7],
      a->data[0] * b->data[2] + a->data[1] * b->data[5] + a->data[2] * b->data[8],
      a->data[3] * b->data[0] + a->data[4] * b->data[3] + a->data[5] * b->data[6],
      a->data[3] * b->data[1] + a->data[4] * b->data[4] + a->data[5] * b->data[7],
      a->data[3] * b->data[2] + a->data[4] * b->data[5] + a->data[5] * b->data[8],
      a->data[6] * b->data[0] + a->data[7] * b->data[3] + a->data[8] * b->data[6],
      a->data[6] * b->data[1] + a->data[7] * b->data[4] + a->data[8] * b->data[7],
      a->data[6] * b->data[2] + a->data[7] * b->data[5] + a->data[8] * b->data[8]
    }
  };
}

void mat3x3f32_mul_vec2f32(const mat3x3f32_t* matrix, f32_t* x, f32_t* y)
{
  const f32_t _x = *x;
  const f32_t _y = *y;

  *x = matrix->data[0] * _x + matrix->data[1] * _y + matrix->data[2];
  *y = matrix->data[3] * _x + matrix->data[4] * _y + matrix->data[5];
}

mat3x3f32_t mat3x3f32_projection_orthographic(f32_t left, f32_t right, f32_t top, f32_t bottom)
{
  const f32_t cx = (left + right) / 2.0f;
  const f32_t cy = (top + bottom) / 2.0f;
  const f32_t sx = (right - left) / 2.0f;
  const f32_t sy = (bottom - top) / 2.0f;

  return(mat3x3f32_t){
    {
      sx,   0.0f, -cx,
      0.0f, sy,   -cy,
      0.0f, 0.0f, 1.0f
    }
  };
}

mat3x3f32_t mat3x3f32_view(f32_t x, f32_t y, f32_t rotation)
{
  const mat3x3f32_t rotated = mat3x3f32_rotation(rotation);
  const mat3x3f32_t translated = mat3x3f32_translation(x, y);
  const mat3x3f32_t transformed = mat3x3f32_mul_mat3x3f32(&translated, &rotated);
  
  return mat3x3f32_inverse(&transformed);
}

f32_t mat3x3f32_determinant(const mat3x3f32_t* matrix)
{
  return 1.0f / (matrix->data[0] * (matrix->data[4] * matrix->data[8] - matrix->data[5] * matrix->data[7])
              -  matrix->data[1] * (matrix->data[3] * matrix->data[8] - matrix->data[5] * matrix->data[6])
              +  matrix->data[2] * (matrix->data[3] * matrix->data[7] - matrix->data[4] * matrix->data[6]));
}

mat3x3f32_t mat3x3f32_inverse(const mat3x3f32_t *matrix)
{
  const f32_t inv_determinant = mat3x3f32_determinant(matrix);

  return(mat3x3f32_t){
    {
      (matrix->data[4] * matrix->data[8] - matrix->data[5] * matrix->data[7]) * inv_determinant, 
      -(matrix->data[1] * matrix->data[8] - matrix->data[2] * matrix->data[7]) * inv_determinant, 
      (matrix->data[1] * matrix->data[5] - matrix->data[2] * matrix->data[4]) * inv_determinant,
    
      -(matrix->data[3] * matrix->data[8] - matrix->data[5] * matrix->data[6]) * inv_determinant, 
      (matrix->data[0] * matrix->data[8] - matrix->data[2] * matrix->data[6]) * inv_determinant, 
      (matrix->data[0] * matrix->data[5] - matrix->data[2] * matrix->data[3]) * inv_determinant,

      (matrix->data[3] * matrix->data[7] - matrix->data[4] * matrix->data[6]) * inv_determinant, 
      -(matrix->data[0] * matrix->data[7] - matrix->data[1] * matrix->data[6]) * inv_determinant, 
      (matrix->data[0] * matrix->data[4] - matrix->data[1] * matrix->data[3]) * inv_determinant
    }
  };
}

mat3x3f32_t mat3x3f32_translation(f32_t x, f32_t y)
{
  return(mat3x3f32_t){
    {
      1.0f, 0.0f, x,
      0.0f, 1.0f, y,
      0.0f, 0.0f, 1.0f
    }
  };
}

mat3x3f32_t mat3x3f32_scale(f32_t x, f32_t y)
{
  return(mat3x3f32_t){
    {
      x,    0.0f, 0.0f,
      0.0f, y,    0.0f,
      0.0f, 0.0f, 1.0f
    }
  };
}

mat3x3f32_t mat3x3f32_rotation(f32_t angle)
{
  const float c = cosf(angle);
  const float s = sinf(angle);

  return(mat3x3f32_t){
    {
      c,     -s,   0.0f,
      s,     c,    0.0f,
      0.0f,  0.0f, 1.0f
    }
  };
}
