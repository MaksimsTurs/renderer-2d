#ifndef H_RENDERER2D
#define H_RENDERER2D

#include <stdint.h>
#include <math.h>

#include "math.h"

typedef unsigned int pixel_t;
typedef unsigned int color_t;

typedef struct framebuffer_s {
  pixel_t* pixels;
  unsigned int width;
  unsigned int height;
} framebuffer_t;

#define RGBA_GET_R(color) (((color) >> 24) & 0xff)
#define RGBA_GET_G(color) (((color) >> 16) & 0xff)
#define RGBA_GET_B(color) (((color) >> 8)  & 0xff)
#define RGBA_GET_A(color) ((((color) >> 0) & 0xff))
#define RGBA_PACK(r, g, b, a) (((r) << 24) | ((g) << 16) | ((b) << 8) | ((a) << 0))

void renderer2d_clear(framebuffer_t* framebuffer);
void renderer2d_draw_rect(framebuffer_t* framebuffer, vec2f_t verticies[4]);

#endif
