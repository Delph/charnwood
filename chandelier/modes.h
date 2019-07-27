#ifndef MODE_H_INCLUDE
#define MODE_H_INCLUDE

enum class Mode
{
  CHASER,
  SIMPLEX,
  SMOOTH,
  SPIRAL,
  WHITE
};

void chaser(const uint32_t now);
void simplex(const uint32_t now);
void smooth(const uint32_t now);
void spiral(const uint32_t now);

#endif
