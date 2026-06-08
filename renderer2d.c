#include "renderer2d.h"

void renderer2d_clear(framebuffer_t* framebuffer)
{
  const unsigned int resolution = framebuffer->height * framebuffer->width;

  for(unsigned int index = 0; index < resolution; index++)
  {
    framebuffer->pixels[index] = 0x000000ff;
  }
}

void renderer2d_draw_rect(framebuffer_t* framebuffer, vec2f_t verticies[4])
{
  vec2f_t vertex = {0};
  pixel_t pixel = 0;

  for(unsigned char index = 0; index < 4; index++)
  {
    vertex = verticies[index];
    pixel = ((pixel_t)(vertex.x) + framebuffer->height * (pixel_t)(vertex.y));

    if(pixel < framebuffer->height * framebuffer->width)
    {
      framebuffer->pixels[pixel] = 0xff0000ff;
    }
  }
}
