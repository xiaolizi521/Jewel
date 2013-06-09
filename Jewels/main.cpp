#include "Engine.h"
#include "defines.h"

int main(int argc, char* argv[])
{
  Engine engine;
  engine.Start(GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, false);
  return 0;
}