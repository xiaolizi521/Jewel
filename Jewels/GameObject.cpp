#include "GameObject.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// author: bithika mookherjee
// email:  thumbelina@gmail.com
// date:   2013-06-09
// 
///////////////////////////////////////////////////////////////////////////////

/************************************************************/

GameObject::GameObject(SDL_Surface * pSurf, std::deque<Sprite *> sv):
  iXVel(0),
  iYVel(0),
  sprites(sv),
  coords(sv.size(), makeVertex(0,0)),
  pSurface(pSurf)
{
  // the coords are all set to 0
}

/************************************************************/

GameObject::GameObject(SDL_Surface * pSurf, std::deque<Sprite *> sv, std::deque<Vertex> cv):
  iXVel(0),
  iYVel(0),
  sprites(sv),
  coords(cv),
  pSurface(pSurf)
{
  
}

/************************************************************/

void GameObject::SetVelocity(float xvel, float yvel)
{
  iXVel = xvel;
  iYVel = yvel;
}

/************************************************************/

void GameObject::SetPosition(int x, int y, int which)
{
  coords[which].x = x;
  coords[which].y = y;
}

/************************************************************/

void GameObject::SetX(int x, int which)
{
  coords[which].x = x;
}

/************************************************************/

void GameObject::SetY(int y, int which)
{
  coords[which].y = y;
}

/************************************************************/

int GameObject::GetX(int which)
{
  return coords[which].x;
}

/************************************************************/

int GameObject::GetY(int which)
{
  return coords[which].y;
}

/************************************************************/

float GameObject::GetVelX()
{
  return iXVel;
}

/************************************************************/

float GameObject::GetVelY()
{
  return iYVel;
}

/************************************************************/

void GameObject::Update(int iElapsedMS)
{
  float distX = iElapsedMS * (iXVel/1000);
  float distY = iElapsedMS * (iYVel/1000);

  for(std::deque<Vertex>::size_type i = 0; i != coords.size(); i++)
  {
    coords[i].x += static_cast<int>(distX);
    coords[i].y += static_cast<int>(distY);
    //std::cout << "x, y = " << coords[i].x << " " << coords[i].y << "\n";
  }
 
}

/************************************************************/

void GameObject::Draw()
{
  for(std::deque<Sprite*>::size_type i = 0; i != sprites.size(); i++)
  {
    sprites[i]->Blit(pSurface, coords[i].x, coords[i].y);  
  } 
}
