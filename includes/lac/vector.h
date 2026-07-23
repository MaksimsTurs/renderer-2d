#ifndef H_LAC_VECTOR
#define H_LAC_VECTOR

// Not sure that vectors of i8, u8, i16 and u16 are useful.

#include <math.h>

#include "type.h"

#define INLINE __attribute((always_inline)) static inline
// Structures declaration macros.
#define DECLARE_VEC2_STRUCT(type, name) typedef struct { type x, y;    } name
#define DECLARE_VEC3_STRUCT(type, name) typedef struct { type x, y, z; } name
// Functions definition macros.
#define DEFINE_VEC2_FUNC(type, prefix, subtype) \
  INLINE f64_t      prefix##_length(type a)             { return sqrt(a.x * a.x + a.y * a.y); } \
  INLINE type       prefix##_add(type a, type b)        { return(type){(subtype)(a.x + b.x), (subtype)(a.y + b.y)}; } \
  INLINE type       prefix##_sub(type a, type b)        { return(type){(subtype)(a.x - b.x), (subtype)(a.y - b.y)}; } \
  INLINE type       prefix##_scale(type a, f64_t scale) { return(type){(subtype)(a.x * scale), (subtype)(a.y * scale)}; } \
  INLINE f64_t      prefix##_dot(type a, type b)        { return a.x * b.x + a.y * b.y; } \
  INLINE vec2f64_t  prefix##_normalize(type a)          { f64_t length = prefix##_length(a); return(vec2f64_t){a.x / length, a.y / length}; }
#define DEFINE_VEC2_FUNC_CONST(type, prefix, subtype) \
  INLINE f64_t      prefix##_length(const type* a)             { return sqrt((a)->x * (a)->x + (a)->y * (a)->y); } \
  INLINE type       prefix##_add(const type* a, const type* b) { return(type){(subtype)((a)->x + (b)->x), (subtype)((a)->y + (b)->y)}; } \
  INLINE type       prefix##_sub(const type* a, const type* b) { return(type){(subtype)((a)->x - (b)->x), (subtype)((a)->y - (b)->y)}; } \
  INLINE type       prefix##_scale(const type* a, f64_t scale) { return(type){(subtype)((a)->x * scale), (subtype)((a)->y * scale)}; } \
  INLINE f64_t      prefix##_dot(const type* a, const type* b) { return (a)->x * (b)->x + (a)->y * (b)->y; } \
  INLINE vec2f64_t  prefix##_normalize(const type* a)          { f64_t length = prefix##_length(a); return(vec2f64_t){(a)->x / length, (a)->y / length}; }
#define DEFINE_VEC3_FUNC(type, prefix, subtype) \
  INLINE f64_t      prefix##_length(type a)             { return sqrt(a.x * a.x + a.y * a.y + a.z * a.z); }\
  INLINE type       prefix##_add(type a, type b)        { return(type){(subtype)(a.x + b.x), (subtype)(a.y + b.y), (subtype)(a.z + b.z)}; } \
  INLINE type       prefix##_sub(type a, type b)        { return(type){(subtype)(a.x - b.x), (subtype)(a.y - b.y), (subtype)(a.z - b.z)}; } \
  INLINE type       prefix##_scale(type a, f64_t scale) { return(type){(subtype)(a.x * scale), (subtype)(a.y * scale), (subtype)(a.z * scale)}; } \
  INLINE f64_t      prefix##_dot(type a, type b)        { return a.x * b.x + a.y * b.y + a.z * b.z; } \
  INLINE type       prefix##_cross(type a, type b)      { return(type){(subtype)(a.y * b.z - a.z * b.y), (subtype)(a.z * b.x - a.x * b.z), (subtype)(a.x * b.y - a.y * b.x)}; } \
  INLINE vec3f64_t  prefix##_normalize(type a)          { f64_t length = prefix##_length(a); return(vec3f64_t){a.x / length, a.y / length, a.z / length}; }
#define DEFINE_VEC3_FUNC_CONST(type, prefix, subtype) \
  INLINE f64_t      prefix##_length(const type* a)             { return sqrt((a)->x * (a)->x + (a)->y * (a)->y + (a)->z * (a)->z); } \
  INLINE type       prefix##_add(const type* a, const type* b) { return(type){(subtype)((a)->x + (b)->x), (subtype)((a)->y + (b)->y), (subtype)((a)->z + (b)->z)}; } \
  INLINE type       prefix##_sub(const type* a, const type* b) { return(type){(subtype)((a)->x - (b)->x), (subtype)((a)->y - (b)->y), (subtype)((a)->z - (b)->z)}; } \
  INLINE type       prefix##_scale(const type* a, f64_t scale) { return(type){(subtype)((a)->x * scale), (subtype)((a)->y * scale), (subtype)((a)->z * scale)}; } \
  INLINE f64_t      prefix##_dot(const type* a, const type* b) { return (a)->x * (b)->x + (a)->y * (b)->y + (a)->z * (b)->z; } \
  INLINE type       prefix##_cross(const type* a, const type* b) { return(type){(subtype)((a)->y * (b)->z - (a)->z * (b)->y), (subtype)((a)->z * (b)->x - (a)->x * (b)->z), (subtype)((a)->x * (b)->y - (a)->y * (b)->x)}; } \
  INLINE vec3f64_t  prefix##_normalize(const type* a)          { f64_t length = prefix##_length(a); return(vec3f64_t){(a)->x / length, (a)->y / length, (a)->z / length}; }

DECLARE_VEC2_STRUCT(i8_t,  vec2i8_t);
DECLARE_VEC2_STRUCT(u8_t,  vec2u8_t);
DECLARE_VEC2_STRUCT(i16_t, vec2i16_t);
DECLARE_VEC2_STRUCT(u16_t, vec2u16_t);
DECLARE_VEC2_STRUCT(i32_t, vec2i32_t);
DECLARE_VEC2_STRUCT(u32_t, vec2u32_t);
DECLARE_VEC2_STRUCT(i64_t, vec2i64_t);
DECLARE_VEC2_STRUCT(u64_t, vec2u64_t);
DECLARE_VEC2_STRUCT(f32_t, vec2f32_t);
DECLARE_VEC2_STRUCT(f64_t, vec2f64_t);

DECLARE_VEC3_STRUCT(i8_t,  vec3i8_t);
DECLARE_VEC3_STRUCT(u8_t,  vec3u8_t);
DECLARE_VEC3_STRUCT(i16_t, vec3i16_t);
DECLARE_VEC3_STRUCT(u16_t, vec3u16_t);
DECLARE_VEC3_STRUCT(i32_t, vec3i32_t);
DECLARE_VEC3_STRUCT(u32_t, vec3u32_t);
DECLARE_VEC3_STRUCT(i64_t, vec3i64_t);
DECLARE_VEC3_STRUCT(u64_t, vec3u64_t);
DECLARE_VEC3_STRUCT(f32_t, vec3f32_t);
DECLARE_VEC3_STRUCT(f64_t, vec3f64_t);

DEFINE_VEC2_FUNC(vec2i8_t,        vec2i8, i8_t);
DEFINE_VEC2_FUNC(vec2u8_t,        vec2u8, u8_t);
DEFINE_VEC2_FUNC(vec2i16_t,       vec2i16, i16_t);
DEFINE_VEC2_FUNC(vec2u16_t,       vec2u16, u16_t);
DEFINE_VEC2_FUNC_CONST(vec2i32_t, vec2i32, i32_t);
DEFINE_VEC2_FUNC_CONST(vec2u32_t, vec2u32, u32_t);
DEFINE_VEC2_FUNC_CONST(vec2i64_t, vec2i64, i64_t);
DEFINE_VEC2_FUNC_CONST(vec2u64_t, vec2u64, u64_t);
DEFINE_VEC2_FUNC_CONST(vec2f32_t, vec2f32, f32_t);
DEFINE_VEC2_FUNC_CONST(vec2f64_t, vec2f64, f64_t);

DEFINE_VEC3_FUNC(vec3i8_t,        vec3i8, i8_t);
DEFINE_VEC3_FUNC(vec3u8_t,        vec3u8, u8_t);
DEFINE_VEC3_FUNC(vec3i16_t,       vec3i16, i16_t);
DEFINE_VEC3_FUNC(vec3u16_t,       vec3u16, u16_t);
DEFINE_VEC3_FUNC_CONST(vec3i32_t, vec3i32, i32_t);
DEFINE_VEC3_FUNC_CONST(vec3u32_t, vec3u32, u32_t);
DEFINE_VEC3_FUNC_CONST(vec3i64_t, vec3i64, i64_t);
DEFINE_VEC3_FUNC_CONST(vec3u64_t, vec3u64, u64_t);
DEFINE_VEC3_FUNC_CONST(vec3f32_t, vec3f32, f32_t);
DEFINE_VEC3_FUNC_CONST(vec3f64_t, vec3f64, f64_t);
#endif
