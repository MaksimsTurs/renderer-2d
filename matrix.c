#include "matrix.h"

void mat3x3f32_apply_to_shape(mat3x3f32_t *matrix, vec2f32_t origin, vec2f32_t* vertecies, vec2f32_t* buffer, i8_t length)
{
  for(i16_t index = 0; index < length; index++)
  {
    buffer[index] = mat3x3f32_multiply_vec2f32(matrix, (vec2f32_t){
      .x = vertecies[index].x - origin.x,
      .y = vertecies[index].y - origin.y
    });
  }
}

vec2f32_t mat3x3f32_multiply_vec2f32(mat3x3f32_t* matrix, vec2f32_t vector)
{
  return(vec2f32_t){
    matrix->x.x * vector.x + matrix->x.y * vector.y + matrix->x.z,
    matrix->y.x * vector.x + matrix->y.y * vector.y + matrix->y.z
  };
}

mat3x3f32_t mat3x3f32_multiply_mat3x3f32(mat3x3f32_t *a, mat3x3f32_t *b)
{
  return(mat3x3f32_t){
    {
      a->x.x * b->x.x + a->x.y * b->y.x + a->x.z * b->z.x,
      a->x.x * b->x.y + a->x.y * b->y.y + a->x.z * b->z.y,
      a->x.x * b->x.z + a->x.y * b->y.z + a->x.z * b->z.z
    },
    {
      a->y.x * b->x.x + a->y.y * b->y.x + a->y.z * b->z.x,
      a->y.x * b->x.y + a->y.y * b->y.y + a->y.z * b->z.y,
      a->y.x * b->x.z + a->y.y * b->y.z + a->y.z * b->z.z
    },
    {
      a->z.x * b->x.x + a->z.y * b->y.x + a->z.z * b->z.x,
      a->z.x * b->x.y + a->z.y * b->y.y + a->z.z * b->z.y,
      a->z.x * b->x.z + a->z.y * b->y.z + a->z.z * b->z.z
    }
  };
}

// TODO This thing break the entire rendering, think about NDC (Normalized Device Coordinate). 
mat3x3f32_t mat3x3f32_orthographic(f32_t left, f32_t right, f32_t top, f32_t bottom)
{
  // f32_t cx = (left + right) / 2.0f;
  // f32_t cy = (top + bottom) / 2.0f;
  // f32_t sx = (right - left) / 2.0f;
  // f32_t sy = (bottom - top) / 2.0f;

  UNUSED(left);
  UNUSED(right);
  UNUSED(top);
  UNUSED(bottom);

  f32_t cx = 0.0f;
  f32_t cy = 0.0f;
  f32_t sx = 1.0f;
  f32_t sy = 1.0f;

  return(mat3x3f32_t){
    { sx,   0.0f, -cx },
    { 0.0f, sy,   -cy },
    { 0.0f, 0.0f, 1.0f }
  };
}

mat3x3f32_t mat3x3f32_view(vec2f32_t translation, f32_t rotation)
{
  mat3x3f32_t rotated = mat3x3f32_rotation(rotation);
  mat3x3f32_t translated = mat3x3f32_translation(translation);
  mat3x3f32_t transform = mat3x3f32_multiply_mat3x3f32(&translated, &rotated);
  
  return mat3x3f32_inverse(&transform);
}

mat3x3f32_t mat3x3f32_inverse(mat3x3f32_t *matrix)
{
  f32_t inv_determinant = 1.0f / (matrix->x.x * (matrix->y.y * matrix->z.z - matrix->y.z * matrix->z.y)
                      - matrix->x.y * (matrix->y.x * matrix->z.z - matrix->y.z * matrix->z.x)
                      + matrix->x.z * (matrix->y.x * matrix->z.y - matrix->y.y * matrix->z.x));
  return(mat3x3f32_t){
    {
      (matrix->y.y * matrix->z.z - matrix->y.z * matrix->z.y) * inv_determinant,
      -(matrix->x.y * matrix->z.z - matrix->x.z * matrix->z.y) * inv_determinant,
      (matrix->x.y * matrix->y.z - matrix->x.z * matrix->y.y) * inv_determinant
    },
    {
      -(matrix->y.x * matrix->z.z - matrix->y.z * matrix->z.x) * inv_determinant,
      (matrix->x.x * matrix->z.z - matrix->x.z * matrix->z.x) * inv_determinant,
      (matrix->x.x * matrix->y.z - matrix->x.z * matrix->y.x) * inv_determinant
    },
    {
      (matrix->y.x * matrix->z.y - matrix->y.y * matrix->z.x) * inv_determinant,
      -(matrix->x.x * matrix->z.y - matrix->x.y * matrix->z.x) * inv_determinant,
      (matrix->x.x * matrix->y.y - matrix->x.y * matrix->y.x) * inv_determinant
    }
  };
}

mat3x3f32_t mat3x3f32_translation(vec2f32_t translation)
{
  return(mat3x3f32_t){
    {1.0f, 0.0f, translation.x},
    {0.0f, 1.0f, translation.y},
    {0.0f, 0.0f, 1.0f}
  };
}

mat3x3f32_t mat3x3f32_rotation(f32_t angle)
{
  float c = cosf(angle);
  float s = sinf(angle);

  return (mat3x3f32_t){
    { c,     -s,   0.0f },
    { s,     c,    0.0f },
    { 0.0f,  0.0f, 1.0f }
  };
}
