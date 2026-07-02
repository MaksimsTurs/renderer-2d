#ifndef H_RENDERER2D_FRAMEBUFFER
#define H_RENDERER2D_FRAMEBUFFER

#include <stdlib.h>
#include <math.h>

#include "type.h"
#include "vector.h"

#define PUT_PIXEL(fram_buffer, x, y, color) do {\
  (frame_buffer)->pixels[(y * (frame_buffer)->height + x)] = color;\
} while(0)

typedef struct {
  u32_t*  pixels;
  u32_t   width, height;
} framebuffer_t;

void framebuffer_clear(framebuffer_t* framebuffer);
void framebuffer_draw_line(framebuffer_t* framebuffer, vec2u32_t vertecies[2]);
void framebuffer_draw_triangle(framebuffer_t* framebuffer, vec2u32_t vertecies[3]);
void framebuffer_draw_rectangle(framebuffer_t* framebuffer, vec2u32_t vertecies[6]);

#endif
