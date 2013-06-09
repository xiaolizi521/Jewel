#include "DroppingJewels.h"
#include "defines.h"
#include <iostream>

const int VISIBLE = 1;

/************************************************************/

DroppingJewels::DroppingJewels(SDL_Surface * pSurf, std::vector<Sprite *> sv, std::vector<Vertex> cv, 
                std::vector<Vertex> tv, int iVis):
      GameObject(pSurf, sv, cv),
      iTargetY(tv.back().y),
      iVisibleFromY(iVis),
      visibility(sv.size(), 0),
      bDropped(false),
      bStarted(false),
      targets(tv)
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
  if( bStarted && !bDropped )
  {
    if(iTargetY > GetY(coords.size()-1) )
    {
      std::cout << "Updating Dropping Jewels\n";
      GameObject::Update(iElapsedMS);

      // now check visibility
      for(std::vector<Vertex>::size_type i = coords.size() - 1; 
        i != (std::vector<Vertex>::size_type)-1; i--) 
      {
        if( coords[i].y-(JEWELSIZE/2) >= iVisibleFromY )
        {
          visibility[i] = 1;
        }
      }
    }
    else
    {
      bDropped = true;

      // Put jewels in correct position ( in case we overshot )
      for(std::vector<Vertex>::size_type i = coords.size() - 1; 
        i != (std::vector<Vertex>::size_type)-1; i--) 
      {
        coords[i].y = targets[i].y;
        visibility[i] = 1;
      }
    }
  }
}

/************************************************************/

void DroppingJewels::Draw()
{
  for(std::vector<Vertex>::size_type i = coords.size() - 1; 
    i != (std::vector<Vertex>::size_type)-1; i--) 
  {
    if( VISIBLE == visibility[i] )
    {
      sprites[i]->Blit(pSurface, coords[i].x, coords[i].y);
    }
  }
}

/************************************************************/
