#include "DisappearAndDropTests.h"
#include <iostream>
#include "defines.h"
#include "Sprite.h"

void DisappearAndDropTest::Enter(Game* pGame)
  
{
  bNewChoice = false;
  bCalculateDrop = false;
}

void DisappearAndDropTest::Exit(Game* pGame)
{
  std::cout << "DisappearAndDropTest Exit Successful\n";
}

// Just pressing the mouse button will start the game 
void DisappearAndDropTest::HandleEvents(Game * pGame)
{
  SDL_Event event;
  
  if(SDL_PollEvent(&event))
  {
    //std::cout << "DisappearAndDropTest handle event\n";
    switch(event.type)
	  {
      case SDL_MOUSEBUTTONDOWN:
      {
        if( event.button.button == SDL_BUTTON_LEFT)
        {
          std::cout << "Mouse Press x" << event.button.x << ", y " << event.button.y << "\n";
          int col = -1;
          int row = -1;
          if(pGame->MouseInGrid(event.button.x, event.button.y, &col, &row))
          {
            std::pair<int,int> p = std::make_pair(col, row);
            chosen.push_back(p);
            it = chosen.rbegin();
            bNewChoice = true;
          }
          else
          {
            bNewChoice = false;
          }
        }
        else
        {
          if( event.button.button == SDL_BUTTON_RIGHT)
          {
            std::cout << "Right button - removing jewels";
            // remove the selected jewels from the grid
            pGame->RemoveJewels(chosen);

            bCalculateDrop = true;
          }
        }
      }
      break;


      default:
        break;
    }
  }
}

/**********************************************************************/

void DisappearAndDropTest::Update(Game* pGame)
{
  if( bCalculateDrop )
  {
         
  }
}


/**********************************************************************/
// Blit any sprites for this state
void DisappearAndDropTest::Draw(Game *pGame)
{
  // Draw any highlights
  if( bNewChoice )
  {
    Sprite * s = pGame->GetHighlight();
    s->Blit(pGame->GetGameScreen(), pGame->GetCoordX(it->first, it->second), pGame->GetCoordY(it->first, it->second));
    bNewChoice = false;
  }
}

/**********************************************************************/

DisappearAndDropTest DisappearAndDropTest::m_DisappearAndDropTest;