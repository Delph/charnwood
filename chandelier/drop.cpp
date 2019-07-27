#if 0
class Drop
{
public:
  Drop() : colour(255, 255, 255), ring(4) {}
  CHSV colour;
  size_t ring;
  size_t led;
  uint32_t last;
  uint32_t speed;
  uint8_t fade;
};

Drop drops[30];


void update()
{
  for (size_t i = 0; i < 30; ++i)
  {
    Drop& drop = drops[i];
    if (drop.ring == 4)
    {
      drop.colour = 0xFFFFFF;
      drop.ring = 0;
      drop.led = random(rings[0].length);
      drop.last = now;
      drop.speed = 500;
      drop.fade = 8;
    }
    else
    {
      drop.colour.v -= drop.fade;
    }

    // move down
    if (drop.last + drop.speed > drop.now)
    {
      Ring& current = rings[drop.ring++];
      // nothing more to do
      if (drop.ring >= 4)
        continue;
      Ring& target = rings[drop.ring];
      drop.led = static_cast<size_t>(current.perc(drop.led) * current.length + 0.5f);
      drop.last = now;
    }

    rings[drop.ring].leds[drop.led] = drop.colour;
  }
}
#endif
