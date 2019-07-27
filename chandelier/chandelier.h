#ifndef CHANDELIER_H_INCLUDE
#define CHANDELIER_H_INCLUDE

#include <FastLED.h>

#include "modes.h"

class Ring
{
public:
  Ring(const size_t n, CRGB* const l) : length(n), leds(l) {}
  const size_t length;
  CRGB* const leds;

public:
  inline float perc(const size_t i) const
  {
    return static_cast<float>(i) / static_cast<float>(length);
  }
};

extern const size_t NUM_RING0_LEDS;
extern const size_t NUM_RING1_LEDS;
extern const size_t NUM_RING2_LEDS;
extern const size_t NUM_RING3_LEDS;
extern const size_t NUM_LEDS;

extern CRGB leds[];
extern Ring rings[4];

#endif
