#include "RNG.h"

RandomNumberGenerator RandomNumberGenerator::m_Generator;

void RandomNumberGenerator::Initialise(int s, int min, int max)
{
  gen = new Generator( Engine(s), Distribution( min, max ) );
}

int RandomNumberGenerator::Random()
{
  return (*gen)();
}
