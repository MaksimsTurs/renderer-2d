#ifndef H_RENDERER2D_FRAMEBUFFER
#define H_RENDERER2D_FRAMEBUFFER

#include <stdlib.h>
#include <math.h>

#include "type.h"
#include "utils.h"
#include "lac/vector.h"

#define PIXEL_GET_R(pixel) ((pixel >> 16) & 0xff)
#define PIXEL_GET_G(pixel) ((pixel >> 8) & 0xff)
#define PIXEL_GET_B(pixel) ((pixel >> 0) & 0xff)
#define PIXEL_GET_A(pixel) ((pixel >> 24) & 0xff)
#define PIXEL_PACK_RGBA(r, g, b, a) ((r << 16) | (g << 8) | (b << 0) | (a << 24))
#define GET_PIXEL(framebuffer, x, y) (framebuffer)->pixels[(y * (framebuffer)->w + x)] 
#define PUT_PIXEL(frambuffer, x, y, color) do {\
  (framebuffer)->pixels[(y * (framebuffer)->w + x)] = color;\
} while(0)
#define IS_PIXEL_IN_FRAMEBUFFER(framebuffer, x, y) (((x >= 0) || (x < (framebuffer)->w)) || ((y >= 0) || (y <= (framebuffer)->h)))\

typedef struct {
  u32_t* pixels;
  i32_t w, h;
} framebuffer_t;

void framebuffer_create(framebuffer_t* framebuffer, i32_t width, i32_t height);
void framebuffer_destroy(framebuffer_t* framebuffer);
void framebuffer_resize(framebuffer_t* framebuffer, i32_t width, i32_t height);

void framebuffer_clear(framebuffer_t* framebuffer, u32_t color);
void framebuffer_draw_point(framebuffer_t* framebuffer, vec2f32_t point, u32_t color);
void framebuffer_draw_line(framebuffer_t* framebuffer, const vec2f32_t vertecies[2], u32_t color);
void framebuffer_draw_triangle(framebuffer_t* framebuffer, const vec2f32_t vertecies[3], u32_t color);
void framebuffer_draw_rectangle(framebuffer_t* framebuffer, const vec2f32_t vertecies[6], u32_t color);
void framebuffer_draw_circle(framebuffer_t* framebuffer, vec2f32_t vertex, f32_t radius, u32_t color);
void framebuffer_draw_image(framebuffer_t* framebuffer, vec2i32_t src_size, const u32_t* buffer, const vec2f32_t vertecies[6]);
void framebuffer_draw_image_triangle(framebuffer_t* framebuffer, vec2i32_t src_size, const u32_t* buffer, const vec2f32_t uv[3], const vec2f32_t vertecies[3]);

u32_t framebuffer_alpha_blending(u32_t pixel_color, u32_t new_color);
#endif
