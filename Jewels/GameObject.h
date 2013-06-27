#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <SDL.h>
#include "Sprite.h"
#include "Vertex.h"
#include <deque>

class GameObject
{

  public:
    GameObject(SDL_Surface * pSurf, std::deque<Sprite*> sv);
    GameObject(SDL_Surface * pSurf, std::deque<Sprite*> sv, std::deque<Vertex> cv);

    virtual void SetVelocity(float xvel, float yvel);
    virtual void SetPosition(int x, int y, int which = 0);

    virtual void SetY(int y, int which = 0);
    virtual void SetX(int x, int which = 0);

    virtual int  GetX(int which = 0);
    virtual int  GetY(int which = 0);

    virtual float GetVelX();
    virtual float GetVelY();

    virtual void Update(int iElapsedMS);
    virtual void Draw();

  protected:
    GameObject(){};

    SDL_Surface * pSurface;

    float iXVel;
    float iYVel;
    
    std::deque<Vertex>     coords;
    std::deque<Sprite *> sprites;
  
  private:

    
};

#endif

