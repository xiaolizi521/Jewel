#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <boost/foreach.hpp>

#define foreach_ BOOST_FOREACH 

// Screen Dimensions
const char GAME_TITLE[] = "Jewel Game";
const int SCREEN_WIDTH = 755;
const int SCREEN_HEIGHT = 600;

// Image IDs
const int BACKGROUND = 0;
const int TIMELEFT = 1;
const int SCOREBOARD = 2;
const int NUMBERS = 3;
const int SELECTED_JEWEL = 4;
const int SWAPWIPER = 5;
const int STARTMENU = 6;
const int HIGH_JEWEL = 7;

// Jewel Defines
const int JEWEL_START_ID = 8;
const int NUMJEWELTYPES = 5;

typedef enum 
{
  JEWELTYPE_RED,
  JEWELTYPE_BLUE,
  JEWELTYPE_AMBER,
  JEWELTYPE_EMERALD,
  JEWELTYPE_PURPLE,
  JEWELTYPE_NONE
}JewelType;


typedef struct 
{
  const char * pFilename;
  int ID;
}TextureResource;

// Image Filenames
static TextureResource textures[] =
{
  {"BackGround.jpg", BACKGROUND},
  {"timeleft.png", TIMELEFT},
  {"score.png", SCOREBOARD},
  {"numbers.png", NUMBERS},
  {"chosen.png", SELECTED_JEWEL},
  {"menuState.png", STARTMENU},
  {"swap_wiper.png", SWAPWIPER},
  {"highlight.png", HIGH_JEWEL},
  {"Red.png", JEWEL_START_ID},
  {"Blue.png", JEWEL_START_ID+1},
  {"Yellow.png", JEWEL_START_ID+2},
  {"Green.png", JEWEL_START_ID+3},
  {"Purple.png",JEWEL_START_ID+4},
  {"",-1}
};

// Grid Positioning
const int NUM_COLUMNS = 8;
const int NUM_ROWS = 8;

const int SLOTS_OFFSET_X = 0;
const int SLOTS_OFFSET_Y = 0;

const int GRID_START_X = 320;
const int GRID_START_Y = 97;
const int SLOT_WIDTH = 43;
const int SLOT_HEIGHT = 43;

const int JEWELSIZE = 43;

const int NO_SLOT = -1;

// Animations
const float DROP_SPEED = 200.0;
const int   TIME_BETWEEN_DROPS = 100;

// Intro menu
const int INTRO_MENU_X = 49;
const int INTRO_MENU_Y = 49;


// Defines for the offsets 
// into the Numbers texture.
// (for getting indiv. digits )
const int digit_x_offset[10] = { 0, 17, 34, 51, 68, 84, 101, 118, 136, 152 };  
const int DIGIT_WIDTH = 17;
const int DIGIT_HEIGHT = 20;

// TIME stuff
const int MILLISECONDS_IN_AN_HOUR = 3600000;
const int MILLISECONDS_IN_A_MIN = 60000;
const int MILLISECONDS_IN_A_SECOND = 1000;


// countdown
const int TIMER_X = 127;
const int TIMER_Y = 236;
const int MAX_TIME = 60000; // in milliseconds

// Timer box coords
const int TIMELEFT_X = 17;
const int TIMELEFT_Y = 184;

// Score box coords
const int SCOREBOX_X = 17;
const int SCOREBOX_Y = 94;

// Animations
const float STAY_HORIZONTAL = 0.0;
const float STAY_VERTICAL = 0.0;

// Velocity is in pixels per tick.
//const float MOVE_UP = -200;
//const float MOVE_DOWN = 200;
//const float MOVE_RIGHT = 200;
//const float MOVE_LEFT = -200;

// slow
const float MOVE_UP = -200;
const float MOVE_DOWN = 200;
const float MOVE_RIGHT = 200;
const float MOVE_LEFT = -200;
#endif // DEFINES_H