#ifndef H_LINEARALGEBRA_VECTOR
#define H_LINEARALGEBRA_VECTOR

// Not sure that vectors of i8, u8, i16 and u16 are useful.

#include <math.h>

#include "type.h"

// Structures declaration macros.
#define DECLARE_VEC2_STRUCT(type, name) typedef struct { type x, y;    } name
#define DECLARE_VEC3_STRUCT(type, name) typedef struct { type x, y, z; } name
// Functions declaration macros.
#define DECLARE_VEC2_FUNC(type, prefix) \
  f64_t     prefix##_length(type a); \
  type      prefix##_add(type a, type b); \
  type      prefix##_sub(type a, type b); \
  type      prefix##_scale(type a, f64_t scale); \
  f64_t     prefix##_dot(type a, type b); \
  vec2f64_t prefix##_normalize(type a);
#define DECLARE_VEC2_FUNC_CONST(type, prefix) \
  f64_t     prefix##_length(const type* a); \
  type      prefix##_add(const type* a, const type* b); \
  type      prefix##_sub(const type* a, const type* b); \
  type      prefix##_scale(const type* a, f64_t scale); \
  f64_t     prefix##_dot(const type* a, const type* b); \
  vec2f64_t prefix##_normalize(const type* a);
#define DECLARE_VEC3_FUNC(type, prefix) \
  f64_t     prefix##_length(type a); \
  type      prefix##_add(type a, type b); \
  type      prefix##_sub(type a, type b); \
  type      prefix##_scale(type a, f64_t scale); \
  f64_t     prefix##_dot(type a, type b); \
  vec3f64_t prefix##_normalize(type a);
#define DECLARE_VEC3_FUNC_CONST(type, prefix) \
  f64_t     prefix##_length(const type* a); \
  type      prefix##_add(const type* a, const type* b); \
  type      prefix##_sub(const type* a, const type* b); \
  type      prefix##_scale(const type* a, f64_t scale); \
  f64_t     prefix##_dot(const type* a, const type* b); \
  vec3f64_t prefix##_normalize(const type* a);
// Functions definition macros.
#define DEFINE_VEC2_FUNC(type, prefix, subtype) \
  f64_t     prefix##_length(type a)             { return sqrtl(a.x * a.x + a.y * a.y); } \
  type      prefix##_add(type a, type b)        { return(type){(subtype)(a.x + b.x), (subtype)(a.y + b.y)}; } \
  type      prefix##_sub(type a, type b)        { return(type){(subtype)(a.x - b.x), (subtype)(a.y - b.y)}; } \
  type      prefix##_scale(type a, f64_t scale) { return(type){(subtype)(a.x * scale), (subtype)(a.y * scale)}; } \
  f64_t     prefix##_dot(type a, type b)        { return a.x * b.x + a.y * b.y; } \
  vec2f64_t prefix##_normalize(type a)          { f64_t length = prefix##_length(a); return(vec2f64_t){a.x / length, a.y / length}; }
#define DEFINE_VEC2_FUNC_CONST(type, prefix, subtype) \
  f64_t     prefix##_length(const type* a)             { return sqrtl((a)->x * (a)->x + (a)->y * (a)->y); } \
  type      prefix##_add(const type* a, const type* b) { return(type){(subtype)((a)->x + (b)->x), (subtype)((a)->y + (b)->y)}; } \
  type      prefix##_sub(const type* a, const type* b) { return(type){(subtype)((a)->x - (b)->x), (subtype)((a)->y - (b)->y)}; } \
  type      prefix##_scale(const type* a, f64_t scale) { return(type){(subtype)((a)->x * scale), (subtype)((a)->y * scale)}; } \
  f64_t     prefix##_dot(const type* a, const type* b) { return (a)->x * (b)->x + (a)->y * (b)->y; } \
  vec2f64_t prefix##_normalize(const type* a)          { f64_t length = prefix##_length(a); return(vec2f64_t){(a)->x / length, (a)->y / length}; }
#define DEFINE_VEC3_FUNC(type, prefix, subtype) \
  f64_t     prefix##_length(type a)             { return sqrtl(a.x * a.x + a.y * a.y + a.z * a.z); }\
  type      prefix##_add(type a, type b)        { return(type){(subtype)(a.x + b.x), (subtype)(a.y + b.y), (subtype)(a.z + b.z)}; } \
  type      prefix##_sub(type a, type b)        { return(type){(subtype)(a.x - b.x), (subtype)(a.y - b.y), (subtype)(a.z - b.z)}; } \
  type      prefix##_scale(type a, f64_t scale) { return(type){(subtype)(a.x * scale), (subtype)(a.y * scale), (subtype)(a.z * scale)}; } \
  f64_t     prefix##_dot(type a, type b)        { return a.x * b.x + a.y * b.y + a.z * b.z; } \
  vec3f64_t prefix##_normalize(type a)          { f64_t length = prefix##_length(a); return(vec3f64_t){a.x / length, a.y / length, a.z / length}; }
#define DEFINE_VEC3_FUNC_CONST(type, prefix, subtype) \
  f64_t     prefix##_length(const type* a)             { return sqrtl((a)->x * (a)->x + (a)->y * (a)->y + (a)->z * (a)->z); } \
  type      prefix##_add(const type* a, const type* b) { return(type){(subtype)((a)->x + (b)->x), (subtype)((a)->y + (b)->y), (subtype)((a)->z + (b)->z)}; } \
  type      prefix##_sub(const type* a, const type* b) { return(type){(subtype)((a)->x - (b)->x), (subtype)((a)->y - (b)->y), (subtype)((a)->z - (b)->z)}; } \
  type      prefix##_scale(const type* a, f64_t scale) { return(type){(subtype)((a)->x * scale), (subtype)((a)->y * scale), (subtype)((a)->z * scale)}; } \
  f64_t     prefix##_dot(const type* a, const type* b) { return (a)->x * (b)->x + (a)->y * (b)->y + (a)->z * (b)->z; } \
  vec3f64_t prefix##_normalize(const type* a)          { f64_t length = prefix##_length(a); return(vec3f64_t){(a)->x / length, (a)->y / length, (a)->z / length}; }

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

DECLARE_VEC2_FUNC(vec2i8_t,         vec2i8);
DECLARE_VEC2_FUNC(vec2u8_t,         vec2u8);
DECLARE_VEC2_FUNC(vec2i16_t,        vec2i16);
DECLARE_VEC2_FUNC(vec2u16_t,        vec2u16);
DECLARE_VEC2_FUNC_CONST(vec2i32_t,  vec2i32);
DECLARE_VEC2_FUNC_CONST(vec2u32_t,  vec2u32);
DECLARE_VEC2_FUNC_CONST(vec2i64_t,  vec2i64);
DECLARE_VEC2_FUNC_CONST(vec2u64_t,  vec2u64);
DECLARE_VEC2_FUNC_CONST(vec2f32_t,  vec2f32);
DECLARE_VEC2_FUNC_CONST(vec2f64_t,  vec2f64);

DECLARE_VEC3_FUNC(vec3i8_t,         vec3i8);
DECLARE_VEC3_FUNC(vec3u8_t,         vec3u8);
DECLARE_VEC3_FUNC(vec3i16_t,        vec3i16);
DECLARE_VEC3_FUNC(vec3u16_t,        vec3u16);
DECLARE_VEC3_FUNC_CONST(vec3i32_t,  vec3i32);
DECLARE_VEC3_FUNC_CONST(vec3u32_t,  vec3u32);
DECLARE_VEC3_FUNC_CONST(vec3i64_t,  vec3i64);
DECLARE_VEC3_FUNC_CONST(vec3u64_t,  vec3u64);
DECLARE_VEC3_FUNC_CONST(vec3f32_t,  vec3f32);
DECLARE_VEC3_FUNC_CONST(vec3f64_t,  vec3f64);
#endif
