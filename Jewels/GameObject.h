#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <SDL.h>
#include "Sprite.h"
#include "Vertex.h"
#include <vector>

class GameObject
{

  public:
    GameObject(SDL_Surface * pSurf, std::vector<Sprite*> sv);
    GameObject(SDL_Surface * pSurf, std::vector<Sprite*> sv, std::vector<Vertex> cv);

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
    
    std::vector<Vertex>     coords;
    std::vector<Sprite *> sprites;
  
  private:

    
};

#endif

