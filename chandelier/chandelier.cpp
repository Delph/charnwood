#include <Arduino.h>

#include <FastLED.h>

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
}


struct Chaser
{
  size_t pos;
  size_t dir;
  CRGB colour;
};

Chaser chasers[8] = {
  {0,  1, CRGB::Red}, {10, -1, CRGB::Yellow},
  {0, -1, CRGB::Orange}, {20,  1, CRGB::Green},
  {0,  1, CRGB::Blue}, {15,  -1, CRGB::White},
  {0, -1, CRGB::Purple}, { 5, 1, CRGB::Red}
};


uint32_t last = 0;
const uint32_t FPS = 40;
void loop()
{
  uint32_t now = millis();
  while (now < last + 1000 / FPS)
    now = millis();

  for (size_t r = 0; r < 4; ++r)
  {
    Ring& ring = rings[r];
    for (size_t i = 0; i < ring.length; ++i)
      ring.leds[i].fadeToBlackBy(32);

    Chaser& chaser1 = chasers[r*2];
    Chaser& chaser2 = chasers[r*2+1];
    if (ring.leds[chaser1.pos].getAverageLight() < 16)
      ring.leds[chaser1.pos] = chaser1.colour;
    else
      ring.leds[chaser1.pos] = ring.leds[chaser1.pos].lerp8(chaser1.colour, 128);
    if (ring.leds[chaser2.pos].getAverageLight() < 16)
      ring.leds[chaser2.pos] = chaser2.colour;
    else
      ring.leds[chaser2.pos] = ring.leds[chaser2.pos].lerp8(chaser2.colour, 128);

    chaser1.pos = (chaser1.pos + chaser1.dir + ring.length) % ring.length;
    chaser2.pos = (chaser2.pos + chaser2.dir + ring.length) % ring.length;
  }

  FastLED.show();

  last = millis();
}
