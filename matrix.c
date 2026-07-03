#include "matrix.h"
#include "type.h"

void mat3x3f32_apply(mat3x3f32_t *matrix, vec2i32_t origin, vec2i32_t* vertecies, vec2i32_t* buffer, i8_t length)
{
  i32_t x = 0;
  i32_t y = 0;

  for(i8_t index = 0; index < length; index++)
  {
    x = (matrix->x.x * (vertecies[index].x - origin.x)) +
        (matrix->x.y * (vertecies[index].y - origin.y)) +
        matrix->x.z;
    y = (matrix->y.x * (vertecies[index].x - origin.x)) +
        (matrix->y.y * (vertecies[index].y - origin.y)) +
        matrix->y.z;
    buffer[index].x = x;
    buffer[index].y = y;
  }
}

mat3x3f32_t mat3x3f32_orthographic(f32_t left, f32_t right, f32_t top, f32_t bottom)
{
  const f32_t cx = (right - left) / 2.0f;
  const f32_t cy = (bottom - top) / 2.0f;

  return(mat3x3f32_t){
    { 1.0f, 0.0f, cx },
    { 0.0f, 1.0f, cy },
    { 0.0f, 0.0f, 1.0f }
  };
}

mat3x3f32_t mat3x3f32_multiply(mat3x3f32_t *a, mat3x3f32_t *b)
{
  mat3x3f32_t matrix = {0};

  matrix.x.x = a->x.x * b->x.x + a->x.y * b->y.x + a->x.z * b->z.x;
  matrix.x.y = a->x.x * b->x.y + a->x.y * b->y.y + a->x.z * b->z.z;
  matrix.x.z = a->x.x * b->x.z + a->x.y * b->y.z + a->x.z * b->z.z;
  matrix.y.x = a->y.x * b->x.x + a->y.y * b->y.x + a->y.z * b->z.x;
  matrix.y.y = a->y.x * b->x.y + a->y.y * b->y.y + a->y.z * b->z.y;
  matrix.y.z = a->y.x * b->x.z + a->y.y * b->y.z + a->y.z * b->z.z;
  matrix.z.x = a->z.x * b->x.x + a->z.y * b->y.x + a->z.z * b->z.x;
  matrix.z.y = a->z.x * b->x.y + a->z.y * b->y.y + a->z.z * b->z.y;
  matrix.z.z = a->z.x * b->x.z + a->z.y * b->y.z + a->z.z * b->z.z;

  return matrix;
}

mat3x3f32_t mat3x3f32_inverse(mat3x3f32_t *matrix)
{
  mat3x3f32_t inverse = {0};
  f32_t determinant = 1.0f / (matrix->x.x * (matrix->y.y * matrix->z.z - matrix->y.z * matrix->z.y)
                      - matrix->x.y * (matrix->y.x * matrix->z.z - matrix->y.z * matrix->z.x)
                      + matrix->x.z * (matrix->y.x * matrix->z.y - matrix->y.y * matrix->z.x));

  inverse.x.x =  (matrix->y.y * matrix->z.z - matrix->y.z * matrix->z.y) * determinant;
  inverse.x.y = -(matrix->x.y * matrix->z.z - matrix->x.z * matrix->z.y) * determinant;
  inverse.x.z =  (matrix->x.y * matrix->y.z - matrix->x.z * matrix->y.y) * determinant;
  inverse.y.x = -(matrix->y.x * matrix->z.z - matrix->y.z * matrix->z.x) * determinant;
  inverse.y.y =  (matrix->x.x * matrix->z.z - matrix->x.z * matrix->z.x) * determinant;
  inverse.y.z = -(matrix->x.x * matrix->y.z - matrix->x.z * matrix->y.x) * determinant;
  inverse.z.x =  (matrix->y.x * matrix->z.y - matrix->y.y * matrix->z.x) * determinant;
  inverse.z.y = -(matrix->x.x * matrix->z.y - matrix->x.y * matrix->z.x) * determinant;
  inverse.z.z =  (matrix->x.x * matrix->y.y - matrix->x.y * matrix->y.x) * determinant;

  return inverse;
}
