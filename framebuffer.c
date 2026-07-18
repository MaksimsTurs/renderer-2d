#include "include/framebuffer.h"

// TODO Fill multiply pixels in framebuffer_clear.
// TODO Use better algorithm for drawing circles.
// TODO Better Alpha Blending (depth buffer/z index/layout?).

void framebuffer_create(framebuffer_t *framebuffer, i32_t width, i32_t height)
{
  framebuffer->w = width;
  framebuffer->h = height;
  framebuffer->pixels = (u32_t*)malloc(width * height * sizeof(u32_t));
}

void framebuffer_destroy(framebuffer_t *framebuffer)
{
  framebuffer->w = 0;
  framebuffer->h = 0;
  free(framebuffer->pixels);
  framebuffer->pixels = NULL;
}

void framebuffer_resize(framebuffer_t *framebuffer, i32_t width, i32_t height)
{
  framebuffer->w = width;
  framebuffer->h = height;
  free(framebuffer->pixels);
  framebuffer->pixels = NULL;
  framebuffer->pixels = (u32_t*)malloc(width * height * sizeof(u32_t));
}

void framebuffer_clear(framebuffer_t* framebuffer, u32_t color)
{
  const i32_t count = framebuffer->w * framebuffer->h;

  for(i32_t i = 0; i < count; i++)
  {
    framebuffer->pixels[i] = color;
  }
}

void framebuffer_draw_point(framebuffer_t *framebuffer, vec2f32_t point, u32_t color)
{
  PUT_PIXEL(framebuffer, (i32_t)point.x, (i32_t)point.y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, (i32_t)point.x, (i32_t)point.y), color));
}

void framebuffer_draw_line(framebuffer_t* framebuffer, const vec2f32_t vertecies[2], u32_t color)
{
  i32_t x = (i32_t)vertecies[0].x;
  i32_t y = (i32_t)vertecies[0].y;
  i32_t x_end = (i32_t)vertecies[1].x;
  i32_t y_end = (i32_t)vertecies[1].y;
  i32_t dx = x_end - x;
  i32_t dy = y_end - y;
  i32_t step_x = 1;
  i32_t step_y = 1;
  i32_t a = 0;
  i32_t b = 0;
  i32_t err = 0;

  if(dx < 0) {
    dx = -dx;
    step_x = -1;
  }

  if(dy < 0) {
    dy = -dy;
    step_y = -1;
  }

  a = dx + dx;
  b = dy + dy;

  if(dy <= dx) {
    err = -dx;

    while(x != x_end) {
      if(IS_PIXEL_IN_FRAMEBUFFER(framebuffer, x, y))
      {
        PUT_PIXEL(frambuffer, x, y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, x, y), color));
      }
      err += b;
      
      if(err > 0) {
        y += step_y;
        err -= a;
      }

      x += step_x;
    }
  } else {
    err = -dy;

    while(y != y_end) {
      if(IS_PIXEL_IN_FRAMEBUFFER(framebuffer, x, y))
      {
        PUT_PIXEL(frambuffer, x, y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, x, y), color));
      }
      err += a;
      
      if(err > 0) {
        x += step_x;
        err -= b;
      }

      y += step_y;
    }
  }
}

void framebuffer_draw_triangle(framebuffer_t* framebuffer, const vec2f32_t vertecies[3], u32_t color)
{
  vec2i32_t p1 = {0};
  vec2i32_t p2 = {(i32_t)vertecies[0].x, (i32_t)vertecies[0].y};
  vec2i32_t p3 = {(i32_t)vertecies[1].x, (i32_t)vertecies[1].y};
  vec2i32_t p4 = {(i32_t)vertecies[2].x, (i32_t)vertecies[2].y};

  i32_t a = 0;
  i32_t b = 0;
  i32_t c = 0;

  for(i32_t y = 0; y < framebuffer->h; y++)
  {
    for(i32_t x = 0; x < framebuffer->w; x++)
    {
      p1 = (vec2i32_t){x,y};

      a = triangle_edge(p2, p3, p1);
      b = triangle_edge(p3, p4, p1);
      c = triangle_edge(p4, p2, p1);

      if(a >= 0 && b >= 0 && c >= 0)
      {
        PUT_PIXEL(framebuffer, x, y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, x, y), color));
      }
    }
  }
}

void framebuffer_draw_rectangle(framebuffer_t* framebuffer, const vec2f32_t vertecies[6], u32_t color)
{
  const vec2f32_t a[3] = {vertecies[0], vertecies[1], vertecies[2]};
  const vec2f32_t b[3] = {vertecies[3], vertecies[4], vertecies[5]};

  framebuffer_draw_triangle(framebuffer, a, color);
  framebuffer_draw_triangle(framebuffer, b, color);
}

void framebuffer_draw_circle(framebuffer_t *framebuffer, vec2f32_t vertex, f32_t radius, u32_t color)
{
  f32_t dx = 0.0f;
  f32_t dy = 0.0f;

  radius *= radius;

  for(i32_t y = 0; y < framebuffer->h; y++)
  {
    for(i32_t x = 0; x < framebuffer->w; x++) {
      dx = x - vertex.x;
      dy = y - vertex.y;

      if(sqrtf(dx * dx + dy * dy) <= radius)
      {
        PUT_PIXEL(frambuffer, x, y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, x, y), color));
      }
    }
  }
}

void framebuffer_draw_image_triangle(framebuffer_t* framebuffer, vec2i32_t src_size, const u32_t* buffer, const vec2f32_t uv[3], const vec2f32_t vertecies[3])
{
  u8_t cr = 0;
  u8_t cg = 0;
  u8_t cb = 0;
  u8_t ca = 0;

  vec2i32_t p1 = {0};
  vec2i32_t p2 = {(i32_t)vertecies[0].x, (i32_t)vertecies[0].y};
  vec2i32_t p3 = {(i32_t)vertecies[1].x, (i32_t)vertecies[1].y};
  vec2i32_t p4 = {(i32_t)vertecies[2].x, (i32_t)vertecies[2].y};

  i32_t a = 0;
  i32_t b = 0;
  i32_t c = 0;
  i32_t area = triangle_edge(p2, p3, p4);
  f32_t w0 = 0.0f;
  f32_t w1 = 0.0f;
  f32_t w2 = 0.0f;
  f32_t u = 0.0f;
  f32_t v = 0.0f;

  for(i32_t y = 0; y < framebuffer->h; y++)
  {
    for(i32_t x = 0; x < framebuffer->w; x++)
    {
      p1 = (vec2i32_t){x,y};

      a = triangle_edge(p2, p3, p1);
      b = triangle_edge(p3, p4, p1);
      c = triangle_edge(p4, p2, p1);

      if(a >= 0 && b >= 0 && c >= 0)
      {
        w0 = (f32_t)a / area;
        w1 = (f32_t)b / area;
        w2 = (f32_t)c / area;
        
        u = w0 * uv[0].x + w1 * uv[1].x + w2 * uv[2].x;
        v = w0 * uv[0].y + w1 * uv[1].y + w2 * uv[2].y;

        cr = PIXEL_GET_R(buffer[(i32_t)(v * (src_size.y - 1)) * src_size.x + (i32_t)(u * (src_size.x - 1))]);
        cg = PIXEL_GET_G(buffer[(i32_t)(v * (src_size.y - 1)) * src_size.x + (i32_t)(u * (src_size.x - 1))]);
        cb = PIXEL_GET_B(buffer[(i32_t)(v * (src_size.y - 1)) * src_size.x + (i32_t)(u * (src_size.x - 1))]);
        ca = PIXEL_GET_A(buffer[(i32_t)(v * (src_size.y - 1)) * src_size.x + (i32_t)(u * (src_size.x - 1))]);
        PUT_PIXEL(frambuffer, x, y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, x, y), PIXEL_PACK_RGBA(ca, cb, cg, cr)));
      }
    }
  }
}

void framebuffer_draw_image(framebuffer_t* framebuffer, vec2i32_t src_size, const u32_t* buffer, const vec2f32_t vertecies[6])
{  
  const vec2f32_t t1[3] = {vertecies[0], vertecies[1], vertecies[2]};
  const vec2f32_t t2[3] = {vertecies[3], vertecies[4], vertecies[5]};
  static const vec2f32_t uv1[3] = {{0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};
  static const vec2f32_t uv2[3] = {{0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}}; 

  framebuffer_draw_image_triangle(framebuffer, src_size, buffer, uv1, t1);
  framebuffer_draw_image_triangle(framebuffer, src_size, buffer, uv2, t2);
}

u32_t framebuffer_alpha_blending(u32_t pixel_color, u32_t new_color)
{
  const f32_t pr = (f32_t)PIXEL_GET_R(pixel_color) / 255;
  const f32_t pg = (f32_t)PIXEL_GET_G(pixel_color) / 255;
  const f32_t pb = (f32_t)PIXEL_GET_B(pixel_color) / 255;
  const f32_t pa = (f32_t)PIXEL_GET_A(pixel_color) / 255;
  const f32_t nr = (f32_t)PIXEL_GET_R(new_color) / 255;
  const f32_t ng = (f32_t)PIXEL_GET_G(new_color) / 255;
  const f32_t nb = (f32_t)PIXEL_GET_B(new_color) / 255;
  const f32_t na = (f32_t)PIXEL_GET_A(new_color) / 255;

  if(na == 1.0f)
  {
    return new_color;
  }

  return PIXEL_PACK_RGBA(
    (i8_t)((pa * pr + (1.0f - pa) * pa * na * nr) * 255), 
    (i8_t)((pa * pg + (1.0f - pa) * pa * na * ng) * 255), 
    (i8_t)((pa * pb + (1.0f - pa) * pa * na * nb) * 255),
    (i8_t)((pa + na) * 255)
  );
}
