#include "Rect.h"

Rect makeRect(int X, int Y, int W, int H)
{
  Rect tmp = {X,Y,W,H}; 
  return tmp;
}

bool pointInside(Rect *r, int X, int Y)
{
  if(r->x < X && (r->x + r->w) > X)
  {
    if(r->y < Y && (r->y + r->h) > Y)
    {
      return true;
    }
  }
  return false;
}