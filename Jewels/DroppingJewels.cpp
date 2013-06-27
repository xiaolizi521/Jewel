#include "DroppingJewels.h"
#include "defines.h"
#include <iostream>

const int VISIBLE = 1;

/************************************************************/

DroppingJewels::DroppingJewels(SDL_Surface * pSurf, 
                               std::deque<Sprite *> sprites, 
                               std::deque<Vertex> startcoords,
                               std::deque<Vertex> endcoords,
                               int iDropFrom):
      GameObject(pSurf, sprites, startcoords),
      targets(endcoords),
      iVisibleFromY(GRID_START_Y+(JEWELSIZE/2)),
      iHeight(sprites.size() * JEWELSIZE),
      bStarted(false),
      bDropped(false),
      visibility(coords.size(), 0)
{
  // base class part is now constructed.
  SetVelocity(0.0, DROP_SPEED);
}

/************************************************************/

// Update differs slightly from regular game object
// Sprites need to become visible/invisible depending 
// on their Y value
void DroppingJewels::Update(int iElapsedMS)
{
  if( !bDropped )
  {
    GameObject::Update(iElapsedMS);

    std::deque<Vertex>::iterator target_it = targets.begin();
    std::deque<int>::iterator vis_it = visibility.begin();

    foreach_(Vertex v, coords)
    {
      if(v.y > iVisibleFromY)
      {
        *vis_it = 1;
      }
      
      if( v.y >= target_it->y)
      {
        // bDropped = true;
        v.y = target_it->y;
      }
      vis_it++;
      target_it++;
    }

    if(coords.back().y >= targets.back().y)
    {
      bDropped = true;
      visibility.assign(sprites.size(), 1);
    }
  }

}

/************************************************************/

void DroppingJewels::Draw()
{
  int i = 0;
  foreach_(Sprite * s, sprites)
  {
    if( 1 == visibility[i] )
    {
      s->Blit(pSurface, coords[i].x, coords[i].y);
    }
    i++;
  }
}
