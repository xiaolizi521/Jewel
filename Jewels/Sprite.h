#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>
#include "TextureMgr.h"
#include "Rect.h"

// A sprite has no knowledge of where on screen it actually is - it only knows local information,
// about it's texture, the rect within that texture that it must render, and what it's anchor point 
// within that rect is ( i.e. does the sprite treat x and y as the centre or top left of the rect ).
class Sprite
{
public:

  // Create a Sprite which is a rect extracted from the texture passed in, at the coordinates x, y and of width w and height h
  Sprite(HTEXTURE texture, int x, int y, int width, int height);
  Sprite(const Sprite& s);

  ~Sprite(){}; // don't need to call SDL_FreeSurface because we reference Surfaces stored elsewhere.

  // Anchor point is 0,0 by default. Anchor point used for positioning sprite on screen.
  void SetAnchorPoint(int x, int y);

  // Blit the sprite to the specified surface at the coords x, y
  bool Blit(SDL_Surface* dest, int x, int y);

  // Update the sprite's texture ( and texture rect )
  void SetTexture(HTEXTURE texture, int x, int y, int w, int h);

  void SetTextureRect(int x, int y, int w, int h);

  Rect GetBoundingBox(float x, float y) const;

private:
  int iAnchorX;
  int iAnchorY;
  Rect rect;
  HTEXTURE texture;
};

#endif