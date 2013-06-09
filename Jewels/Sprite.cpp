#include "Sprite.h"
#include "SDL_image.h"
#include <iostream>


/*********************************************************/
/*********************************************************/
Sprite::Sprite(HTEXTURE tex, int x, int y, int w, int h):
  iAnchorX(0),
  iAnchorY(0),
  rect(makeRect(x,y,w,h)),
  texture(tex)
{
  
}

/*********************************************************/

Sprite::Sprite(const Sprite& s):
  iAnchorX(s.iAnchorX),
  iAnchorY(s.iAnchorY),
  rect(s.rect),
  texture(s.texture)
{
  
}

/*********************************************************/
// Anchor point is 0,0 by default. Anchor point used for positioning sprite.

void Sprite::SetAnchorPoint(int x, int y)
{
  iAnchorX = x;
  iAnchorY = y;
}

/*********************************************************/
// Blit the sprite to the specified surface at the coords x, y
bool Sprite::Blit(SDL_Surface* dest, int x, int y)
{
  //std::cout << "Sprite::Blit! " << x << "," << y << "\n";
  if(dest == NULL)
  {
    std::cout << "not blitting!\n";
    return false;
  }

  // Calculate what x,y coord on dest, given Anchor point of sprite.
  int iDestX = x-iAnchorX;
  int iDestY = y-iAnchorY;

  SDL_Rect rDest;
  rDest.x = iDestX;
  rDest.y = iDestY;

  SDL_Rect rSrc;
  rSrc.x = rect.x;
  rSrc.y = rect.y;
  rSrc.w = rect.w;
  rSrc.h = rect.h;

  SDL_BlitSurface(texture, &rSrc, dest, &rDest);

  return true;
};

/*********************************************************/

void Sprite::SetTexture(HTEXTURE t, int x, int y, int w, int h)
{
  texture = t;
  rect = makeRect(x,y,w,h);
}

/*********************************************************/

Rect Sprite::GetBoundingBox(float x, float y) const 
{ 
  int tlx = static_cast<int>(x)-iAnchorX;
  int tly = static_cast<int>(y)-iAnchorY;
  Rect r = makeRect(tlx, tly, tlx+rect.w, tly+rect.h); 
  return r; 
}

/*********************************************************/

void Sprite::SetTextureRect(int x, int y, int w, int h)
{
  rect = makeRect(x,y,w,h);
}