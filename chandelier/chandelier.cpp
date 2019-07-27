#include "chandelier.h"

#include <Arduino.h>

const size_t NUM_RING0_LEDS = 48;
const size_t NUM_RING1_LEDS = 37;
const size_t NUM_RING2_LEDS = 29;
const size_t NUM_RING3_LEDS = 24;
const size_t NUM_LEDS = NUM_RING0_LEDS + NUM_RING1_LEDS + NUM_RING2_LEDS + NUM_RING3_LEDS;
CRGB leds[NUM_LEDS];
Ring rings[] = {
  Ring(NUM_RING0_LEDS, &(leds[0])),
  Ring(NUM_RING1_LEDS, &(leds[NUM_RING0_LEDS])),
  Ring(NUM_RING2_LEDS, &(leds[NUM_RING0_LEDS+NUM_RING1_LEDS])),
  Ring(NUM_RING3_LEDS, &(leds[NUM_RING0_LEDS+NUM_RING1_LEDS+NUM_RING2_LEDS]))
};

// if this is deemed not white enough, 0xDFFFDF may be better
// may also need adjusting for the tent
const uint32_t CORRECTION = 0xFFFFFF;

Mode mode;

void setup()
{
  size_t offset = 0;
  FastLED.addLeds<WS2812, 2, GRB>(leds, offset, rings[0].length).setCorrection(CORRECTION);
  offset += rings[0].length;
  FastLED.addLeds<WS2812, 3, GRB>(leds, offset, rings[1].length).setCorrection(CORRECTION);
  offset += rings[1].length;
  FastLED.addLeds<WS2812, 4, GRB>(leds, offset, rings[2].length).setCorrection(CORRECTION);
  offset += rings[2].length;
  FastLED.addLeds<WS2812, 5, GRB>(leds, offset, rings[3].length).setCorrection(CORRECTION);

  FastLED.setBrightness(255);

  mode = Mode::WHITE;
}


void update(const uint32_t now)
{
  switch (mode)
  {
    case Mode::CHASER:
      chaser(now);
    break;
    case Mode::SIMPLEX:
      simplex(now);
    break;
    case Mode::SMOOTH:
      smooth(now);
    break;
    case Mode::SPIRAL:
      spiral(now);
    break;
    case Mode::WHITE:
      fill_solid(leds, NUM_LEDS, CRGB::White);
    break;
  }
}

uint32_t last = 0;
const uint32_t FPS = 1;
void loop()
{
  uint32_t now = millis();
  while (now < last + 1000 / FPS)
    now = millis();

  update(now);

  FastLED.show();

  last = millis();
}
