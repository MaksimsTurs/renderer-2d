#include "framebuffer.h"

void framebuffer_clear(framebuffer_t* frame_buffer)
{
  for(u32_t i = 0; i < frame_buffer->height * frame_buffer->width; i++)
  {
    frame_buffer->pixels[i] = 0x000000ff;
  }
}

void framebuffer_draw_line(framebuffer_t* frame_buffer, vec2u32_t vertecies[2])
{
  u32_t x = vertecies[0].x;
  u32_t y = vertecies[0].y;
  i32_t dx = vertecies[1].x - x;
  i32_t dy = vertecies[1].y - y;
  i32_t step_x = 1;
  i32_t step_y = 1;
  i32_t a = dx + dx;
  i32_t b = dy + dy;
  i32_t err = 0;

  if(dx < 0) {
    dx = -dx;
    step_x = -1;
  }

  if(dy < 0) {
    dy = -dy;
    step_y = -1;
  }

  if(dy <= dx) {
    err = -dx;
    
    while(x != vertecies[1].x) {
      PUT_PIXEL(fram_buffer, x, y, 0xff0000ff);
      err += abs(b);
      
      if(err > 0) {
        y += step_y;
        err -= a;
      }

      x += step_x;
    }
  } else {
    err = -dy;
 
    while(y != vertecies[1].y) {
      PUT_PIXEL(fram_buffer, x, y, 0xff0000ff);
      err += abs(a);
      
      if(err > 0) {
        x += step_x;
        err -= b;
      }

      y += step_y;
    }
  }
}

void framebuffer_draw_triangle(framebuffer_t* frame_buffer, vec2u32_t vertecies[3])
{
  for(u32_t y = 0; y < frame_buffer->height; y++)
  {
    for(u32_t x = 0; x < frame_buffer->width; x++)
    {
      vec2u32_t p = {x,y};

      i32_t a = vec2u32_calc_determinant(vertecies[0], vertecies[1], p);
      i32_t b = vec2u32_calc_determinant(vertecies[1], vertecies[2], p);
      i32_t c = vec2u32_calc_determinant(vertecies[2], vertecies[0], p);

      if(a >= 0 && b >= 0 && c >= 0)
      {
        PUT_PIXEL(fram_buffer, x, y, 0xff0000ff);
      }
    }
  }
}

void framebuffer_draw_rectangle(framebuffer_t* frame_buffer, vec2u32_t vertecies[6])
{
  vec2u32_t a[3] = {vertecies[0], vertecies[1], vertecies[2]};
  vec2u32_t b[3] = {vertecies[3], vertecies[4], vertecies[5]};

  framebuffer_draw_triangle(frame_buffer, a);
  framebuffer_draw_triangle(frame_buffer, b);
}
