#include "Choosing.h"
#include <iostream>
#include "defines.h"

void Choosing::Enter(Game* pGame)
{
  bFirstChosen = false;
  jewelOne = std::make_pair(NO_SLOT, NO_SLOT);
  jewelTwo = std::make_pair(NO_SLOT, NO_SLOT);
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
         std::cout << "Mouse Press x" << event.button.x << ", y " << event.button.y << "\n";
         int col = -1;
         int row = -1;
         if(pGame->MouseInGrid(event.button.x, event.button.y, &col, &row))
         {
           if( !bFirstChosen )
           {
             jewelOne.first = col;
             jewelOne.second = row;
             bFirstChosen = true;
           }
           else
           {
             jewelTwo.first = col;
             jewelTwo.second = row;

             if(pGame->PrepareToSwap(jewelOne, jewelTwo))
             {
               
             }
           }
         }
      }
      break;
      default:
        break;
    }
  }
}

void Choosing::Update(Game* pGame)
{
  if(bFirstChosen)
  {
    // change the 
  }
}

// Blit any sprites for this state
void Choosing::Draw(Game *pGame)
{
  
}

Choosing Choosing::m_Choosing;