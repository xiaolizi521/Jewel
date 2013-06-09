#include "Choosing.h"
#include <iostream>
#include "defines.h"

void Choosing::Enter(Game* pGame)
{
  
}

void Choosing::Exit(Game* pGame)
{
  std::cout << "Choosing Exit Successful\n";
}

// Just pressing the mouse button will start the game 
void Choosing::HandleEvents(Game * pGame)
{
  SDL_Event event;
  
  if(SDL_PollEvent(&event))
  {
    //std::cout << "Choosing handle event\n";
    switch(event.type)
	  {
      case SDL_MOUSEBUTTONDOWN:
      {
        
      }
      break;
      default:
        break;
    }
  }
}

void Choosing::Update(Game* pGame)
{
   
}

// Blit any sprites for this state
void Choosing::Draw(Game *pGame)
{
  
}

Choosing Choosing::m_Choosing;