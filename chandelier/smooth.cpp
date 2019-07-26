#include "chandelier.h"

void smooth(const uint32_t now)
{
  for (size_t r = 0; r < 4; ++r)
  {
    Ring& ring = rings[r];
    for (size_t i = 0; i < ring.length; ++i)
      ring.leds[i] = CHSV(0, 0, inoise8(static_cast<uint16_t>(ring.perc(i) * 255) << 1, r << 9, now / 8));
  }
}
