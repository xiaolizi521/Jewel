#ifndef _DROPPING_JEWELS_H_
#define _DROPPING_JEWELS_H_

#include "GameObject.h"
#include "SDL.h"

class DroppingJewels : public GameObject
{
public:
  DroppingJewels(SDL_Surface * pSurf, std::vector<Sprite *> sv, std::vector<Vertex> cv,
                 std::vector<Vertex> tv, int iVis);

  void Start() { bRunning = true; }

  void Update(int iElapsedMS);
  void Draw();

  bool Completed() { return bDropped; }
private:
  bool bDropped;
  bool bRunning;
  int iTargetY;
  int iVisibleFromY;

  std::vector<Vertex> targets;
  std::vector<int> visibility;
};

#endif