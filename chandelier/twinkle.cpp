#include "chandelier.h"

void twinkle(const uint32_t now)
{
  for (size_t i = 0; i < NUM_LEDS; ++i)
    leds[i].fadeToBlackBy(8);

  leds[random(NUM_LEDS)] = CRGB::White;
  leds[random(NUM_LEDS)] = CRGB::Blue;
}
