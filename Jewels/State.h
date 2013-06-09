#ifndef _STATE_H_
#define _STATE_H_

#include "SDL.h"

template <class Type>
class State
{
public:
 
  virtual void Enter(Type*) = 0;
  virtual void Exit(Type*) = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;
  virtual void HandleEvents(Type *) = 0;
  virtual void Update(Type *) = 0;
  virtual void Draw(Type *) = 0; 

  void ChangeState(Type * pOwner, State* state)
  {
    pOwner->ChangeState(state);
  }

protected:
	State() {}
};


#endif