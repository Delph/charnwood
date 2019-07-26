#include "chandelier.h"

struct Chaser
{
  float pos;
  float speed;
  CRGB colour;
};

Chaser chasers[8] = {
  {0.0f,  0.3f, CRGB::Blue}, {10.0f, 0.5f, CRGB::LightBlue},
  {0.0f,  0.95f, CRGB::Aqua}, {20.0f,  0.4f, CRGB::LightBlue},
  {0.0f,  0.7f, CRGB::DarkBlue}, {15.0f,  0.4f, CRGB::LightBlue},
  {0.0f, 0.2f, CRGB::Turquoise}, { 5.0f, 0.9f, CRGB::LightBlue}
};


void chaser(const uint32_t now)
{
  for (size_t r = 0; r < 4; ++r)
  {
    Ring& ring = rings[r];
    for (size_t i = 0; i < ring.length; ++i)
      ring.leds[i].fadeToBlackBy(2);

    Chaser& chaser1 = chasers[r*2];
    Chaser& chaser2 = chasers[r*2+1];
    if (ring.leds[static_cast<size_t>(chaser1.pos)].getAverageLight() < 4)
      ring.leds[static_cast<size_t>(chaser1.pos)] = chaser1.colour;
    else
      ring.leds[static_cast<size_t>(chaser1.pos)] = ring.leds[static_cast<size_t>(chaser1.pos)].lerp8(chaser1.colour, 128);
    if (ring.leds[static_cast<size_t>(chaser2.pos)].getAverageLight() < 4)
      ring.leds[static_cast<size_t>(chaser2.pos)] = chaser2.colour;
    else
      ring.leds[static_cast<size_t>(chaser2.pos)] = ring.leds[static_cast<size_t>(chaser2.pos)].lerp8(chaser2.colour, 128);

    chaser1.pos = chaser1.pos + chaser1.speed;
    if (chaser1.pos < 0.0f)
      chaser1.pos += ring.length;
    else if (chaser1.pos >= ring.length)
      chaser1.pos -= ring.length;

    chaser2.pos = chaser2.pos + chaser2.speed;
    if (chaser2.pos < 0.0f)
      chaser2.pos += ring.length;
    else if (chaser2.pos >= ring.length)
      chaser2.pos -= ring.length;
  }
}
