#include <Arduino.h>
#include <FastLED.h>
#include <IRLremote.h>

const uint8_t PIN_IR = 2;
const uint8_t PIN_RED = 6;
const uint8_t PIN_GREEN = 5;
const uint8_t PIN_BLUE = 3;

bool on = false;
float brightness = 1.0f;
enum class Mode
{
  SOLID,
  FLASH,
  STROBE,
  FADE,
  SMOOTH
};
Mode mode = Mode::SOLID;

enum Button
{
  NO_COMMAND = 1,
  ADDRESS = 65280,
  ON = 13,
  OFF = 31,
  BRIGHTNESS_DEC = 29,
  BRIGHTNESS_INC = 9,
  WHITE = 21,
  BLUE = 17,
  GREEN = 27,
  RED = 25,
  FLASH = 77,
  STROBE = 0,
  FADE = 26,
  SMOOTH = 12,
  LIGHT_BLUE = 22,
  LIME = 18,
  DARK_ORANGE = 23,
  DARK_PURPLE = 4,
  OLIVE = 76,
  ORANGE = 64,
  PURPLE = 14,
  TURQUOISE = 30,
  LIGHT_ORANGE = 10,
  PINK = 15,
  TEAL = 20,
  YELLOW = 28
};
uint32_t solid = Button::WHITE;

void colour(const CRGB& rgb)
{
  analogWrite(PIN_RED, rgb.r * brightness);
  analogWrite(PIN_GREEN, rgb.g * brightness);
  analogWrite(PIN_BLUE, rgb.b * brightness);
}

CNec remote;
uint8_t getIRCode()
{
  if (remote.available())
  {
    auto data = remote.read();

    if (data.address == 65280)
      return data.command;
  }

  return NO_COMMAND;
}

CRGB mapColour(Button button)
{
  switch (button)
  {
    case Button::RED:
      return CRGB::Red;
    case Button::GREEN:
      return CRGB::Green;
    case Button::BLUE:
      return CRGB::Blue;
    case Button::WHITE:
      return CRGB::White;
    case Button::DARK_ORANGE:
      return CRGB::DarkOrange;
    case Button::LIME:
      return CRGB::LimeGreen;
    case Button::LIGHT_BLUE:
      return CRGB::LightBlue;
    case Button::ORANGE:
      return CRGB::Orange;
    case Button::OLIVE:
      return CRGB::Olive;
    case Button::DARK_PURPLE:
      return 0x4A235A; // some dark purple thing
    case Button::LIGHT_ORANGE:
      return 0xF5B041;
    case Button::TURQUOISE:
      return CRGB::Turquoise;
    case Button::PURPLE:
      return CRGB::Purple;
    case Button::YELLOW:
      return CRGB::Yellow;
    case Button::TEAL:
      return CRGB::Teal;
    case Button::PINK:
      return CRGB::Pink;
    default:
      return CRGB::Black;
  }
}

void setup()
{
  Serial.begin(9600);

  if (!remote.begin(PIN_IR))
  {
    Serial.println("Failed to initailise IR");
    while (1);
  }

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  analogWrite(PIN_RED, 0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE, 0);
}

void loop()
{
  const uint8_t code = getIRCode();
  switch (code)
  {
    case Button::OFF:
      on = false;
    break;
    case Button::ON:
      on = true;
    break;
    case Button::BRIGHTNESS_INC:
      brightness = min(brightness + 0.25f, 1.0f);
    break;
    case Button::BRIGHTNESS_DEC:
      brightness = max(brightness - 0.25f, 0.25f);
    break;
    case Button::WHITE:
    case Button::BLUE:
    case Button::GREEN:
    case Button::RED:
    case Button::LIGHT_BLUE:
    case Button::LIME:
    case Button::DARK_ORANGE:
    case Button::DARK_PURPLE:
    case Button::OLIVE:
    case Button::ORANGE:
    case Button::PURPLE:
    case Button::TURQUOISE:
    case Button::LIGHT_ORANGE:
    case Button::PINK:
    case Button::TEAL:
    case Button::YELLOW:
      mode = Mode::SOLID;
      solid = code;
    break;
    case Button::FLASH:
      mode = Mode::FLASH;
    break;
    case Button::STROBE:
      mode = Mode::STROBE;
    break;
    case Button::FADE:
      mode = Mode::FADE;
    break;
    case Button::SMOOTH:
      mode = Mode::SMOOTH;
    break;
  }

  if (on)
  {
    switch (mode)
    {
      case Mode::SOLID:
        colour(mapColour(solid));
      break;
      case Mode::FLASH:
        colour(ColorFromPalette(LavaColors_p, millis() / 50, 255, LINEARBLEND));
      break;
      case Mode::FADE:
      {
        CHSV colours[] = {
          CHSV(HUE_GREEN, 255, 255),
          CHSV(HUE_GREEN, 255, 255),
          CHSV(HUE_BLUE, 255, 255),
          CHSV(HUE_BLUE, 255, 255),
          CHSV(HUE_PURPLE, 255, 255),
          CHSV(HUE_PURPLE, 255, 255),
          CHSV(HUE_BLUE, 0, 255),
          CHSV(HUE_BLUE, 0, 255)
        };

        const uint32_t period = 1000;
        const uint32_t now = millis() % (8 * period); // number of colours
        const uint8_t progress = map(now % period, 0, 999, 0, 255);
        const uint32_t point = now / period;

        const CHSV current = colours[point];
        const CHSV next = colours[(point+1) % 8];

        colour(CHSV(lerp8by8(current.h, next.h, progress),
            lerp8by8(current.s, next.s, progress),
            lerp8by8(current.v, next.v, progress)
          )
        );
      }
      break;
      case Mode::SMOOTH:
        CHSV col(inoise8(millis() / 16), 255, 255);
        colour(col);
      break;
      default:
      break;
    }
  }
  else
  {
    colour(CRGB::Black);
  }
}
