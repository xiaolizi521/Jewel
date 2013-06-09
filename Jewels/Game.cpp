#include "Game.h"
#include "Util.h"
#include <iostream>
#include "AnimateFillingBoard.h"

/*************************************************************************/

Game::Game(SDL_Surface* pSurface):
  pGameScreen(pSurface),
    coords(NUM_COLUMNS, std::vector<Vertex>(NUM_ROWS, makeVertex(0,0))),
    board(NUM_COLUMNS, std::vector<JewelType>(NUM_ROWS, JEWELTYPE_NONE)),
    dropColumns(NUM_COLUMNS),
    bBackgroundNeedsRedraw(true),
    bBoardNeedsRedraw(false),
    pBoardImage(makeRGBSurface(JEWELSIZE*NUM_COLUMNS, JEWELSIZE*NUM_ROWS)),
    iCurrentTime(0),
    iFrameTime(0)
{
  std::cout << "Creating new game";
  
  InitialiseBoardCoordinates();
  
  rng = RandomNumberGenerator::Instance();  
  rng->Initialise(9999, 0, (NUMJEWELTYPES-1));

  // load textures
  int i = 0;
  while(textures[i].ID != -1)
  {
    TextureMgr::Instance()->LoadTexture(textures[i].pFilename, textures[i].ID);
    i++;
  }

  CreateJewelSprites();
  CreateBackgroundSprites();

  ChangeState(AnimateFillingBoard::Instance());
}

/*************************************************************************/
void Game::InitialiseBoardCoordinates()
{
  for(int i = 0; i < NUM_COLUMNS; i++)
  {
    for(int j = 0; j < NUM_ROWS; j++)
    {
      coords[i][j].x = GRID_START_X + (i * JEWELSIZE) + (JEWELSIZE/2); // centre of slot
      coords[i][j].y = GRID_START_Y + (j * JEWELSIZE) + (JEWELSIZE/2);
    }
  }            
}

/*************************************************************************/

void Game::CreateJewelSprites()
{
  for(int i = JEWEL_START_ID; i < JEWEL_START_ID+NUMJEWELTYPES; i++)
  {
    HTEXTURE tex = TextureMgr::Instance()->GetTexture(i);
    Sprite * jewel = new Sprite(tex, 0, 0, tex->w, tex->h);
    jewel->SetAnchorPoint((tex->w)/2, (tex->h)/2); // anchor at the centre
    jewelSprites.push_back(jewel);
  }
}


/*************************************************************************/

std::vector<Sprite*> Game::GetJewelSprites()
{
  return jewelSprites;  
}

/*************************************************************************/

void Game::CreateBackgroundSprites()
{
  HTEXTURE hBkg = TextureMgr::Instance()->GetTexture(BACKGROUND);
  pBkg = new Sprite(hBkg, 0, 0, hBkg->w, hBkg->h);
  pGridWiper = new Sprite(hBkg, GRID_START_X, GRID_START_Y, GRID_START_X+(JEWELSIZE*NUM_COLUMNS), GRID_START_Y+(JEWELSIZE*NUM_ROWS));

  HTEXTURE hScore = TextureMgr::Instance()->GetTexture(SCOREBOARD);
  pScoreSprite = new Sprite(hScore, 0, 0, hScore->w, hScore->h);

  HTEXTURE hTimeLeft = TextureMgr::Instance()->GetTexture(TIMELEFT);
  pTimeLeftSprite = new Sprite(hTimeLeft, 0, 0, hTimeLeft->w, hTimeLeft->h);  
}

/*************************************************************************/

void Game::PutJewel(int i, int j, JewelType t)
{
  board[i][j] = t;
}

/*************************************************************************/
void Game::CreateColumnsForDropping()
{
  for(int i = 0; i < NUM_COLUMNS; i++)
  {
    // scan for first empty slot from bottom up 
    for(int j = NUM_ROWS-1; j >= 0; j--) 
    {
      if(board[i][j] == JEWELTYPE_NONE)
      {
        JewelType t = static_cast<JewelType>(rng->Random());
        board[i][j] = t;
        dropColumns[i].push_back(t);
      }
    }
  }
}

/*************************************************************************/
std::vector<Sprite *> Game::MakeSpritesForDropping(std::vector<JewelType>& drop)
{
  std::vector<Sprite *> sprites;

  for(std::vector<JewelType*>::size_type i = 0; i != drop.size(); i++)
  {
    sprites.push_back(jewelSprites[drop[i]]);
  }
  return sprites;
}

/*************************************************************************/

std::vector<JewelType> Game::GetDroppingColumn(int iWhichColumn)
{
  return dropColumns[iWhichColumn];
}

/*************************************************************************/
void Game::HandleEvents(Engine * pEngine)
{
  states.back()->HandleEvents(this);
}

/*************************************************************************/

void Game::Update(Engine* pEngine)
{

  // Update the timing information
  int iOldTime = iCurrentTime;
  iCurrentTime = SDL_GetTicks();
  iFrameTime = (iCurrentTime - iOldTime);
  
  // update the clock - returns true if it needs redraw
  //bTimerUpdated = pClock->SubtractTimeElapsed(iFrameTime);
  
  states.back()->Update(this);
}

/*************************************************************************/

void Game::SetBoardRedraw(bool bRedraw)
{
  bBoardNeedsRedraw = false;
}

/*************************************************************************/

void Game::DrawBackground()
{
  pBkg->Blit(pGameScreen, 0, 0);
  //pTimeLeftSprite->Blit(m_pGameScreen, TIMELEFT_X, TIMELEFT_Y);
  //pScoreSprite->Blit(m_pGameScreen, SCOREBOX_X, SCOREBOX_Y);
  
}

/*************************************************************************/

void Game::DrawBoard()
{
  // Blit stationary jewels
  for(int i = 0; i < NUM_COLUMNS; i++)
  {
    for(int j = 0; j < NUM_ROWS; j++)
    {
      jewelSprites[static_cast<int>(board[i][j])]->Blit(pBoardImage, coords[i][j].x, coords[i][j].y);
    }
  }
}

/*************************************************************************/

void Game::Draw()
{
  if( bBackgroundNeedsRedraw )
  {
    DrawBackground();
    bBackgroundNeedsRedraw = false;
  }

  if(bBoardNeedsRedraw)
  {
    DrawBoard();
    bBoardNeedsRedraw = false;
  }

  states.back()->Draw(this);		
}

/************************************************************/
void Game::ChangeState(State<Game>* state)
{
	if( !states.empty() )
	{
		states.back()->Exit(this);
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Enter(this);
}
/************************************************************/
void Game::PushState(State<Game>* state)
{
	if(!states.empty())
	{
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Enter(this);
}

/************************************************************/

void Game::PopState()
{
  if(!states.empty())
  {
    states.back()->Exit(this);
	  states.pop_back();
  }

  if(!states.empty())
  {
    states.back()->Resume();
  }
}

/************************************************************/

int Game::GetElapsedTime()
{
  return iFrameTime;
}

/************************************************************/

Sprite * Game::GetGridWiper()
{
  return pGridWiper;
}

/************************************************************/

std::vector<Vertex> Game::GetDropCoords(int iWhich)
{
  std::vector<Vertex> dropCoords;
  
  int x = coords[iWhich][0].x;
  int length = static_cast<int>(dropColumns[iWhich].size());
  int height = length*JEWELSIZE;

  for(int i = 0; i < length; i++) 
  {
    dropCoords.push_back(makeVertex(x,(coords[iWhich][i].y-height)));
  }
  return dropCoords;
}

/************************************************************/

std::vector<Vertex> Game::GetDropTargetCoords(int iWhich)
{
   std::vector<Vertex> targetCoords;
  
  int x = coords[iWhich][0].x;
  int length = static_cast<int>(dropColumns[iWhich].size());

  for(int i = 0; i < length; i++) 
  {
    targetCoords.push_back(makeVertex(x,coords[iWhich][i].y));
  }
  return targetCoords; 
}

/************************************************************/

void Game::InsertDroppedJewels(int iWhichColumn)
{
  int j = dropColumns[iWhichColumn].size()-1;

  for(std::vector<JewelType>::reverse_iterator i = dropColumns[iWhichColumn].rbegin();
      i != dropColumns[iWhichColumn].rend(); i++)
  {
    PutJewel(iWhichColumn, j, *i);
    j--;
  }
}