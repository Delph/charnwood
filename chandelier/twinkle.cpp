#if 0

void update()
{
  for (size_t i = 0; i < NUM_LEDS; ++i)
    leds[i].fadeToBlackBy(8);

  leds[random(NUM_LEDS)] = CRGB::White;
  leds[random(NUM_LEDS)] = CRGB::Blue;
}

#endif
