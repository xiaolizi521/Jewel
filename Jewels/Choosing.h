#ifndef _CHOOSING_H
#define _CHOOSING_H

#include "SDL.h"
#include "State.h"
#include "Sprite.h"
#include "Game.h"

class Choosing : public State<Game>
{
public:
  void Enter(Game*);
	void Exit(Game*) ;
	
	void HandleEvents(Game * game);
	void Update(Game * game);
	void Draw(Game* game);

  // Not used
  void Pause(){}
  void Resume(){}

  // Singleton pattern
  static Choosing* Instance()
  {
    return &m_Choosing;
  }

protected:
  static Choosing m_Choosing;
	Choosing() {}
private:
  bool bUpdate;
  int iChoice;
  std::pair<int,int> chosen[2];
  Sprite * first;
  Sprite * second;
};

#endif