#ifndef _DROP_SPRITE_H_
#define _DROP_SPRITE_H_

#include "SDL.h"
#include "defines.h"
#include "GameObject.h"
#include "Rect.h"
#include <vector>

class DropSprite : GameObject
{
  public:
    // Create a new DropSprite (wrapper around a game object) out of a vector of jewel types.
    DropSprite(std::vector<JewelType>& v, std::vector<Sprite *>& sprites, std::vector<Rect>& coords, std::vector<JewelType>& col);
    
  private:
    SDL_Surface * pImage;
    int iTargetRow;
    int iTargetY;
};

#endif