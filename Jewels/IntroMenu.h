#ifndef _INTROMENU_H_
#define _INTROMENU_H_

#include "SDL.h"
#include "State.h"
#include "Sprite.h"
#include "Game.h"

class IntroMenu : public State<Game>
{
public:
  void Enter(Game*);
	void Exit(Game*) ;
	
	void HandleEvents(Game*);
	void Update(Game*);
	void Draw(Game*);

  // Not used
  void Pause(){}
  void Resume(){}

  // Singleton pattern
  static IntroMenu* Instance()
  {
    return &m_IntroMenu;
  }

protected:
  static IntroMenu m_IntroMenu;
	IntroMenu() {}

  // state specific sprites
  Sprite * intro;
};

#endif