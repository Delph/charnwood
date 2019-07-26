#include "chandelier.h"

void simplex(const uint32_t now)
{
  for (size_t r = 0; r < 4; ++r)
  {
    Ring& ring = rings[r];
    for (size_t i = 0; i < ring.length; ++i)
      ring.leds[i] = CHSV(inoise8(static_cast<uint16_t>(ring.perc(i) * 255) << 3, (r*255), now / 8), 255, 255);
  }
}
