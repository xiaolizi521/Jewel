#include "Game.h"
#include "Util.h"
#include <iostream>
#include "AnimateFillingBoard.h"

/*************************************************************************/

Game::Game(SDL_Surface* pSurface):
    pGameScreen(pSurface),
    gridarea(makeRect(GRID_START_X, GRID_START_Y, JEWELSIZE*NUM_COLUMNS, JEWELSIZE*NUM_ROWS)),
    coords(NUM_COLUMNS, std::vector<Vertex>(NUM_ROWS, makeVertex(0,0))),
    board(NUM_COLUMNS, std::vector<JewelType>(NUM_ROWS, JEWELTYPE_NONE)),
    squares(NUM_COLUMNS, std::vector<Rect>(NUM_ROWS, makeRect(0,0,0,0))),
    dropColumns(NUM_COLUMNS),
    bBackgroundNeedsRedraw(true),
    bBoardNeedsRedraw(false),
    pBoardImage(makeRGBSurface(JEWELSIZE*NUM_COLUMNS, JEWELSIZE*NUM_ROWS)),
    pBlankBoardImage(makeRGBSurface(JEWELSIZE*NUM_COLUMNS, JEWELSIZE*NUM_ROWS)),
    iCurrentTime(0),
    iFrameTime(0)
{
  std::cout << "Creating new game";
  
  InitialiseBoardCoordinates();
  InitialiseBoardSquares();

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

  WipeBoard();
  ChangeState(AnimateFillingBoard::Instance());
}

/*************************************************************************/

void Game::WipeBoard()
{
  SDL_Rect src;
  src.h = (JEWELSIZE*NUM_ROWS);
  src.w = (JEWELSIZE*NUM_COLUMNS);
  src.x = GRID_START_X;
  src.y = GRID_START_Y;

  SDL_Rect dst;
  dst.x = 0;
  dst.y = 0;

  HTEXTURE bkg = TextureMgr::Instance()->GetTexture( BACKGROUND );
  SDL_BlitSurface(bkg, &src, pBoardImage, &dst);
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

void Game::InitialiseBoardSquares()
{
  for(int i = 0; i < NUM_COLUMNS; i++)
  {
    for(int j = 0; j < NUM_ROWS; j++)
    {
      squares[i][j].x = GRID_START_X + (i * JEWELSIZE); // centre of slot
      squares[i][j].y = GRID_START_Y + (j * JEWELSIZE);
      squares[i][j].w = JEWELSIZE;
      squares[i][j].h = JEWELSIZE;
    }
  }            
}

/*************************************************************************/

bool Game::MouseInGrid(int iScreenX, int iScreenY, int * col, int * row)
{
  if(pointInside(&gridarea, iScreenX, iScreenY))
  {
    for(int i = 0; i < NUM_COLUMNS; i++)
    {
      for(int j = 0; j < NUM_ROWS; j++)
      {
        if(pointInside(&squares[i][j], iScreenX, iScreenY))
        {
          *col = i; 
          *row = j;
          return true;
        }
      }
    }
  }
  return false;
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

  HTEXTURE tex = TextureMgr::Instance()->GetTexture(HIGH_JEWEL);
  pHighJewel = new Sprite(tex, 0, 0, tex->w, tex->h);
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

void Game::HighlightJewel(int i, int j)
{
  // Mark slot[i][j] as being highlighted.
  std::pair<int,int> choice = std::make_pair(i,j);
  chosen.push_back(choice);
}

/*************************************************************************/
std::vector<std::pair<int,int>> Game::GetChoices()
{
  return chosen;
}


/*************************************************************************/

void Game::CreateColumnsForDropping()
{
  for(int i = 0; i < NUM_COLUMNS; i++)
  {
    int iEmpty = 0;
    // count how many empty slots there are in this column.
    for(int j = NUM_ROWS-1; j >= 0; j--) 
    {
      if(board[i][j] == JEWELTYPE_NONE)
      {       
        iEmpty++;
      }
      else
      {
        if(iEmpty > 0 )
        {
          // the next non-empty slot goes into the drop column
          dropColumns[i].push_back(board[i][j]);

          // and we set this to NULL
          board[i][j] = JEWELTYPE_NONE;
        }
      }
    }

    // refill the empties from the other side.
    for(int iFill = 0; iFill < iEmpty; iFill++)
    {
      JewelType t = static_cast<JewelType>(rng->Random());
      dropColumns[i].push_back(t);
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
  bBoardNeedsRedraw = bRedraw;
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
  PrintBoard();
  WipeBoard();
  // Blit stationary jewels
  for(int i = 0; i < NUM_COLUMNS; i++)
  {
    for(int j = 0; j < NUM_ROWS; j++)
    {
      if(JEWELTYPE_NONE != board[i][j])
      {
        jewelSprites[static_cast<int>(board[i][j])]->Blit(pBoardImage, coords[i][j].x-GRID_START_X, coords[i][j].y-GRID_START_Y);
        //pTimeLeftSprite->Blit(pBoardImage, coords[i][j].x, coords[i][j].y);
      }
    }
  }

  // now blit pBoardImage to the screen
  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.h = JEWELSIZE*NUM_ROWS;
  src.w = JEWELSIZE*NUM_COLUMNS;

  SDL_Rect dst;
  dst.x = GRID_START_X;
  dst.y = GRID_START_Y;
  SDL_BlitSurface(pBoardImage, NULL, pGameScreen, &dst);
  //SDL_Flip(m_pCanvas);
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

Sprite * Game::GetHighlight()
{
  return pHighJewel;
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

/************************************************************/

void Game::RemoveJewels(std::vector<std::pair<int,int>> chosen)
{
  std::vector<std::pair<int,int>>::iterator it = chosen.begin();

  while(it != chosen.end())
  {
    board[it->first][it->second] = JEWELTYPE_NONE;
    it++;
  }

  bBoardNeedsRedraw = true;

}

/************************************************************/
bool Game::PrepareToSwap(std::pair<int,int>& one, std::pair<int,int>& two)
{
  return false;
}

/************************************************************/

void Game::PrintBoard()
{
  std::cout << "B O A R D \n";
  for(int i = 0; i < NUM_COLUMNS; i++)
  {
    for(int j = 0; j < NUM_ROWS; j++)
    { 
      std::cout << board[i][j] << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\n\n";
}

/************************************************************/

void Game::DropAllColumns()
{
  for(int i = 0; i < NUM_COLUMNS; i++)
  {
    if(!dropColumns[i].empty())
    {
      // work from the top down, find the first ocupied slot and 
      // drop the column on to it.
      std::vector<JewelType>::reverse_iterator it = board[i].rbegin();
      while(it != board[i].rend() && *it != JEWELTYPE_NONE)
      {
        it++;
      }
      std::vector<JewelType>::reverse_iterator it2 = board[i].rend();
      board[i].insert(it2, dropColumns[i].begin(), dropColumns[i].end());
    }
  }
}