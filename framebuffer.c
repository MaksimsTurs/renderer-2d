#include "framebuffer.h"
#include "type.h"

void framebuffer_clear(framebuffer_t* framebuffer)
{
  for(i32_t i = 0; i < framebuffer->height * framebuffer->width; i++)
  {
    framebuffer->pixels[i] = 0x000000ff;
  }
}

void framebuffer_draw_point(framebuffer_t *framebuffer, vec2f32_t point)
{
  PUT_PIXEL(framebuffer, (i32_t)point.x, (i32_t)point.y, 0xff0000ff);
}

// TODO Fix rotation bug.
void framebuffer_draw_line(framebuffer_t* framebuffer, vec2f32_t vertecies[2])
{
  i32_t x = (i32_t)vertecies[0].x;
  i32_t y = (i32_t)vertecies[0].y;
  i32_t dx = (i32_t)vertecies[1].x - x;
  i32_t dy = (i32_t)vertecies[1].y - y;
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
    
    while(x != (i32_t)vertecies[1].x) {
      PUT_PIXEL(frambuffer, x, y, 0xff0000ff);
      err += abs(b);
      
      if(err > 0) {
        y += step_y;
        err -= a;
      }

      x += step_x;
    }
  } else {
    err = -dy;
 
    while(y != (i32_t)vertecies[1].y) {
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

void framebuffer_draw_triangle(framebuffer_t* framebuffer, vec2f32_t vertecies[3])
{
  for(i32_t y = 0; y < framebuffer->height; y++)
  {
    for(i32_t x = 0; x < framebuffer->width; x++)
    {
      vec2i32_t p1 = {x,y};
      vec2i32_t p2 = {(i32_t)vertecies[0].x, (i32_t)vertecies[0].y};
      vec2i32_t p3 = {(i32_t)vertecies[1].x, (i32_t)vertecies[1].y};
      vec2i32_t p4 = {(i32_t)vertecies[2].x, (i32_t)vertecies[2].y};

      i32_t a = vec2i32_calc_determinant(p2, p3, p1);
      i32_t b = vec2i32_calc_determinant(p3, p4, p1);
      i32_t c = vec2i32_calc_determinant(p4, p2, p1);

      if(a >= 0 && b >= 0 && c >= 0)
      {
        PUT_PIXEL(fram_buffer, x, y, 0xff0000ff);
      }
    }
  }
}

void framebuffer_draw_rectangle(framebuffer_t* framebuffer, vec2f32_t vertecies[6])
{
  vec2f32_t a[3] = {vertecies[0], vertecies[1], vertecies[2]};
  vec2f32_t b[3] = {vertecies[3], vertecies[4], vertecies[5]};

  framebuffer_draw_triangle(framebuffer, a);
  framebuffer_draw_triangle(framebuffer, b);
}
