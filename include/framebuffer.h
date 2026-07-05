#ifndef H_RENDERER2D_FRAMEBUFFER
#define H_RENDERER2D_FRAMEBUFFER

#include <stdlib.h>
#include <math.h>

#include "type.h"
#include "vector.h"
#include "camera2d.h"
#include "utils.h"

#define PUT_PIXEL(frambuffer, x, y, color) do {\
  (framebuffer)->pixels[(y * (framebuffer)->height + x)] = color;\
} while(0)

typedef struct {
  u32_t*  pixels;
  i32_t   width, height;
} framebuffer_t;

typedef struct {
  i32_t x, y, width, height;
} bound_box_t;

bound_box_t framebuffer_get_bound_box(framebuffer_t* framebuffer, vec2f32_t* vertecies, i16_t length);
bound_box_t framebuffer_get_bound_circle(framebuffer_t* framebuffer, vec2f32_t vertecies[1], f32_t radius);
bool_t      framebuffer_is_point_outside(framebuffer_t* framebuffer, i32_t x, i32_t y);

void framebuffer_clear(framebuffer_t* framebuffer);
void framebuffer_draw_point(framebuffer_t* framebuffer, vec2f32_t point);
void framebuffer_draw_line(framebuffer_t* framebuffer, vec2f32_t vertecies[2]);
void framebuffer_draw_triangle(framebuffer_t* framebuffer, vec2f32_t vertecies[3]);
void framebuffer_draw_rectangle(framebuffer_t* framebuffer, vec2f32_t vertecies[6]);
void framebuffer_draw_circle(framebuffer_t* framebuffer, vec2f32_t vertecies[1], f32_t radius);

#endif
