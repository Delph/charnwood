#if 0
CRGB colours[] = {
  0xff6961, // red
  0xff7333, // orange
  0xdddd33, // yellow
  0x37dd37, // green
  0x9ea6cf, // blue
  0xb16ca9  // purple
};
size_t col = 0;
size_t pos = 0;

void update()
{
  leds[pos++] = colours[col];
  if (pos == NUM_LEDS)
  {
    pos = 0;
    col = (col + 1) % 6;
  }
}
#endif
