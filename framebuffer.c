#include "framebuffer.h"

bound_box_t framebuffer_get_bound_box(framebuffer_t* framebuffer, vec2f32_t *vertecies, i16_t length)
{
  bound_box_t bound_box = {vertecies[0].x, vertecies[0].y, vertecies[1].x, vertecies[1].y};

  for(i16_t index = 0; index < length; index++)
  {
    bound_box.x = MAX(MIN(bound_box.x, vertecies[index].x), 0);
    bound_box.y = MAX(MIN(bound_box.y, vertecies[index].y), 0);
    bound_box.width = MAX(MIN(MAX(bound_box.width, vertecies[index].x), framebuffer->width), 0);
    bound_box.height = MAX(MIN(MAX(bound_box.height, vertecies[index].y), framebuffer->height), 0);
  }

  return bound_box;
}

bool_t framebuffer_is_point_outside(framebuffer_t *framebuffer, i32_t x, i32_t y)
{
  return((x < 0 || x >= framebuffer->width) || (y < 0 || y >= framebuffer->height));
}

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

void framebuffer_draw_line(framebuffer_t* framebuffer, vec2f32_t vertecies[2])
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
      if(!framebuffer_is_point_outside(framebuffer, x, y))
        PUT_PIXEL(frambuffer, x, y, 0xff0000ff);
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
      if(!framebuffer_is_point_outside(framebuffer, x, y))
        PUT_PIXEL(frambuffer, x, y, 0xff0000ff);
      err += a;
      
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
  bound_box_t bound_box = framebuffer_get_bound_box(framebuffer, vertecies, 3);

  for(i32_t y = bound_box.y; y < bound_box.height; y++)
  {
    for(i32_t x = bound_box.x; x < bound_box.width; x++)
    {
      vec2i32_t p1 = {x,y};
      vec2i32_t p2 = {(i32_t)vertecies[0].x, (i32_t)vertecies[0].y};
      vec2i32_t p3 = {(i32_t)vertecies[1].x, (i32_t)vertecies[1].y};
      vec2i32_t p4 = {(i32_t)vertecies[2].x, (i32_t)vertecies[2].y};

      i32_t a = vec2i32_determinant(p2, p3, p1);
      i32_t b = vec2i32_determinant(p3, p4, p1);
      i32_t c = vec2i32_determinant(p4, p2, p1);

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
