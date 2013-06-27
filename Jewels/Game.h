#ifndef _GAME_H_
#define _GAME_H_

///////////////////////////////////////////////////////////////////////////////
//
// author: bithika mookherjee
// email:  thumbelina@gmail.com
// date:   2013-06-09
// 
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include "Sprite.h"
#include "defines.h"
#include "Rect.h"
#include "State.h"
#include "RNG.h"
#include "Vertex.h"
#include "DroppingJewels.h"
#include <deque>

class Engine;

class Game
{
public:
  Game(SDL_Surface * pSurface);

  void HandleEvents(Engine* pEngine);
	void Update(Engine* pEngine);
	void Draw();

  void ChangeState(State<Game>* state); // new function
	void PushState(State<Game>* state); // new function
	void PopState();


  // Jewel Game specific functions
  void InitialiseBoardCoordinates();
  void InitialiseBoardSquares();
  void InitialiseBoard();
  
  bool MouseInGrid(int iScreenX, int iScreenY, int * col, int * row);

  void HighlightJewel(int i, int j);
  std::deque<std::pair<int,int>> GetChoices();
  Sprite * GetHighlight();
  void RemoveJewels(std::deque<std::pair<int,int>> chosen);

  void PutJewel(int i, int j, JewelType t);
  void InsertDroppedJewels(int iWhichColumn);
  
  void CreateColumnsForDropping();
  std::deque<JewelType> GetDroppingColumn(int iWhichColumn);
  void CreateDropSprite(int iWhich);
  void PrintCoordCol( int iWhich );

  std::deque<Vertex> GetDropCoords(int iWhich);
  std::deque<Vertex> GetDropTargetCoords(int iWhich);
  void DropAllColumns();
  void CreateDropColumn(int iWhich);
  void PushRandomJewelToDropColumn( int iWhich );
  void UpdateAllDropColumns(int iTimeElapsed);
  bool AllColumnsDropped();
  void DrawAllDropColumns();
  void StartDropColumn( int iWhich );

  // Swapping
  bool PrepareToSwap(std::pair<int,int>&, std::pair<int,int>&);

  int GetCoordX(int col, int row){ return coords[col][row].x; }
  int GetCoordY(int col, int row){ return coords[col][row].y; }

  std::deque<Sprite*> GetJewelSprites();
  void CreateJewelSprites();
  void CreateBackgroundSprites();
  Sprite * GetGridWiper();

  // Drawing functions
  void SetBoardRedraw(bool);
  void DrawBoard();
  void DrawBackground();

  int  GetElapsedTime();

  SDL_Surface * GetGameScreen() { return pGameScreen; }

  void PrintBoard();
  void WipeBoard();
private:
  std::deque<State<Game>*> states;
  SDL_Surface * pGameScreen;
  RandomNumberGenerator * rng;

  // Timing
  int iCurrentTime;
  int iFrameTime;

  // Rectangle defining grid area
  Rect gridarea;

  // Each square in the grid can be defined using a rect.
  // Used to translate mouse presses.
  std::deque<std::deque<Rect>> squares;

  // The grid coordinates are stored in a deque of deque<Vertex>
  // coords are given as the centre of each slot.
  std::deque<std::deque<Vertex>> coords;

  // The board is a grid of JewelTypes.
  std::deque<std::deque<JewelType>> board; 

  // Columns of jewels type and sprites - used for animating drops
  std::deque<std::deque<JewelType>> dropColumns;
  std::deque<DroppingJewels *> dropSprites;
  int iEmpties;
  int iBottom;

  // Highlights
  std::deque<std::pair<int,int>> chosen;

  // Sprites 
  std::deque<Sprite *> jewelSprites;
  Sprite * pBkg;
  Sprite * pScoreSprite;
  Sprite * pTimeLeftSprite;
  Sprite * pMarker;
  Sprite * pEmpty;
  Sprite * pGridWiper;
  Sprite * pHighJewel;

  // Drawing 
  SDL_Surface * pBoardImage;
  SDL_Surface * pBlankBoardImage;
  bool bBackgroundNeedsRedraw;
  bool bBoardNeedsRedraw;
};

#endif