#ifndef _DROPPING_JEWELS_H_
#define _DROPPING_JEWELS_H_

#include "GameObject.h"
#include "SDL.h"

class DroppingJewels : public GameObject
{
public:
  DroppingJewels(){}
  DroppingJewels::DroppingJewels(SDL_Surface * pSurf, 
                                 std::deque<Sprite *> sprites, 
                                 std::deque<Vertex> startcoords,
                                 std::deque<Vertex> endcoords,
                                 int iDropFrom);

  void Start() { bStarted = true; }

  void Update(int iElapsedMS);
  void Draw();
  
  bool Completed() { return (bStarted && bDropped); }

private:
  int  iHeight;
  bool bDropped;
  bool bStarted;
  int iTargetY;
  int iVisibleFromY;

  std::deque<Vertex> targets;
  std::deque<int> visibility;
};

#endif