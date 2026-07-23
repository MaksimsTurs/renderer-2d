#include "framebuffer.h"

// TODO framebuffer_clear:       fill multiple pixels in single iteration.
// TODO framebuffer_draw_circle: get rid of vec2f32_length(&d) call.
// TODO framebuffer_resize:      copy the prev pixels into the new buffer?

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
  vec2i32_t p = {vertecies[0].x, vertecies[0].y};
  vec2i32_t pe = {vertecies[1].x, vertecies[1].y};
  vec2i32_t d = vec2i32_sub(&pe, &p);
  vec2i32_t step = {1, 1};
  i32_t a = 0;
  i32_t b = 0;
  i32_t err = 0;

  if(d.x < 0) {
    d.x = -d.x;
    step.x = -1;
  }

  if(d.y < 0) {
    d.y = -d.y;
    step.y = -1;
  }

  a = d.x + d.x;
  b = d.y + d.y;

  if(d.y <= d.x) {
    err = -d.x;

    while(p.x != pe.x) {
      if(IS_PIXEL_IN_FRAMEBUFFER(framebuffer, p.x, p.y))
      {
        PUT_PIXEL(frambuffer, p.x, p.y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, p.x, p.y), color));
      }
      err += b;
      
      if(err > 0) {
        p.y += step.y;
        err -= a;
      }

      p.x += step.x;
    }
  } else {
    err = -d.y;

    while(p.y != pe.y) {
      if(IS_PIXEL_IN_FRAMEBUFFER(framebuffer, p.x, p.y))
      {
        PUT_PIXEL(frambuffer, p.x, p.y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, p.x, p.y), color));
      }
      err += a;
      
      if(err > 0) {
        p.x += step.x;
        err -= b;
      }

      p.y += step.y;
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
        PUT_PIXEL(framebuffer, p1.x, p1.y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, p1.x, p1.y), color));
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
  vec2f32_t d = {0.0f, 0.0f};
  vec2f32_t p = {0.0f, 0.0f};

  radius *= radius;

  for(i32_t y = 0; y < framebuffer->h; y++)
  {
    for(i32_t x = 0; x < framebuffer->w; x++) {
      p = (vec2f32_t){x, y};
      d = vec2f32_sub(&p, &vertex);

      if(vec2f32_length(&d) <= radius)
      {
        PUT_PIXEL(frambuffer, x, y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, x, y), color));
      }
    }
  }
}

void framebuffer_draw_image_triangle(framebuffer_t* framebuffer, vec2i32_t dimension, vec2i32_t src_size, vec2i32_t src_offset, const u32_t* buffer, const vec2f32_t uv[3], const vec2f32_t vertecies[3])
{
  vec2i32_t pt = {0};
  vec2i32_t p1 = {0};
  vec2i32_t p2 = {(i32_t)vertecies[0].x, (i32_t)vertecies[0].y};
  vec2i32_t p3 = {(i32_t)vertecies[1].x, (i32_t)vertecies[1].y};
  vec2i32_t p4 = {(i32_t)vertecies[2].x, (i32_t)vertecies[2].y};

  u8_t cr = 0;
  u8_t cg = 0;
  u8_t cb = 0;
  u8_t ca = 0;

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

        pt.x = (i32_t)(u * (src_size.x - 1));
        pt.y = (i32_t)(v * (src_size.y - 1));

        pt.x = MIN(pt.x + src_offset.x, dimension.x);
        pt.y = MIN(pt.y + src_offset.y, dimension.y);

        cr = PIXEL_GET_R(buffer[pt.y * dimension.x + pt.x]);
        cg = PIXEL_GET_G(buffer[pt.y * dimension.x + pt.x]);
        cb = PIXEL_GET_B(buffer[pt.y * dimension.x + pt.x]);
        ca = PIXEL_GET_A(buffer[pt.y * dimension.x + pt.x]);
        PUT_PIXEL(frambuffer, p1.x, p1.y, framebuffer_alpha_blending(GET_PIXEL(framebuffer, p1.x, p1.y), PIXEL_PACK_RGBA(ca, cb, cg, cr)));
      }
    }
  }
}

void framebuffer_draw_image(framebuffer_t* framebuffer, vec2i32_t dimension, vec2i32_t src_size, vec2i32_t src_offset, const u32_t* buffer, const vec2f32_t vertecies[6])
{  
  const vec2f32_t t1[3] = {vertecies[0], vertecies[1], vertecies[2]};
  const vec2f32_t t2[3] = {vertecies[3], vertecies[4], vertecies[5]};
  static const vec2f32_t uv1[3] = {{0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};
  static const vec2f32_t uv2[3] = {{0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}};

  framebuffer_draw_image_triangle(framebuffer, dimension, src_size, src_offset, buffer, uv1, t1);
  framebuffer_draw_image_triangle(framebuffer, dimension, src_size, src_offset, buffer, uv2, t2);
}

u32_t framebuffer_alpha_blending(u32_t pixel_color, u32_t new_color)
{
  const f32_t pr = (f32_t)PIXEL_GET_R(pixel_color) / 255;
  const f32_t pg = (f32_t)PIXEL_GET_G(pixel_color) / 255;
  const f32_t pb = (f32_t)PIXEL_GET_B(pixel_color) / 255;
  const f32_t nr = (f32_t)PIXEL_GET_R(new_color) / 255;
  const f32_t ng = (f32_t)PIXEL_GET_G(new_color) / 255;
  const f32_t nb = (f32_t)PIXEL_GET_B(new_color) / 255;
  const f32_t na = (f32_t)PIXEL_GET_A(new_color) / 255;

  if(PIXEL_GET_A(new_color) == 255)
  {
    return new_color;
  }

  return PIXEL_PACK_RGBA(
    (u8_t)((((1.0f - na) * pr) + (na * nr)) * 255), 
    (u8_t)((((1.0f - na) * pg) + (na * ng)) * 255), 
    (u8_t)((((1.0f - na) * pb) + (na * nb)) * 255),
    PIXEL_GET_A(new_color)
  );
}
