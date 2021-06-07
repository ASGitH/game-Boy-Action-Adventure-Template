#include "gameConfiguration.h"

#include "backgrounds/headsUpDisplayMB.h"
#include "backgrounds/overworldMB.h"

#include "headsUpDisplay.h"

#include "player.h"

#include "rand.h"

#include "sprites/fontTD.h"
#include "sprites/overworldTD.h"

#include "stdio.h"

struct player playerS;

UINT16 mapStartingPosition;

UINT8 mapPosition[2];

unsigned int seed = 0;

void performatDelay(UINT8 _numberOfLoops)
{
    UINT8 i;

    for (i = 0; i < _numberOfLoops; i++) { wait_vbl_done(); }
}

void textLoadFont() 
{ 
    set_bkg_data(0, 50, (unsigned char *)fontSprites); 

    UINT8 offsetX = 0;
    UINT8 offsetY = 0;

    UINT16 clearBackground = 0;

    char blankTile = ' ';

    for(clearBackground = 0; clearBackground < 360; clearBackground++)
    {
        set_bkg_tiles(offsetX, offsetY, 1, 1, (unsigned char *)blankTile);

        offsetX += 1;

        if(offsetX >= 20) { offsetX = 0; offsetY += 1; }
    }
}

void textPrintCharBkgOrWin(UINT8 _x, UINT8 _y, char _bkgOrWin, unsigned char _chr) 
{
    UINT8 tile = 46;

    if (_chr >= 'a' && _chr <= 'z') { tile = 1 + _chr - 'a'; } 
    else if (_chr >= 'A' && _chr <= 'Z') { tile = 1 + _chr - 'A'; } 
    else if (_chr >= '0' && _chr <= '9') { tile = 27 + _chr - '0'; } 
    else {
        switch (_chr) 
        {
            case ' ': tile = 0; break;
            case ':': tile = 41; break;
            case '!': tile = 42; break;
            case ')': tile = 45; break;
        }
    }
    
    if(_bkgOrWin != 'b') { set_win_tiles(_x, _y, 1, 1, &tile); }
    else { set_bkg_tiles(_x, _y, 1, 1, &tile); }
}

void textPrintStringBkgOrWin(UINT8 _x, UINT8 _y, char _bkgOrWin, unsigned char *_string) 
{
    UINT8 offsetX = 0;
    UINT8 offsetY = 0;

    while (_string[0]) 
    {
        if (_string[0] == '\n') {
            offsetX = 0;
            offsetY += 1;
        } 
        else 
        {
            textPrintCharBkgOrWin(_x + offsetX, _y + offsetY, _bkgOrWin, (unsigned char) _string[0]);

            offsetX += 1;
        }

        _string += 1;
    }
}

void initializeHUD()
{
    set_win_tiles(0, 0, 20, 3, headsUpDisplayMap);

    move_win(7, 128);
}

void initializeGame()
{
    UINT8 temporaryCounter = 0; UINT8 temporaryYCounter = 0;

    textLoadFont();

    set_bkg_data(51, 33, overworldSprites);

    playerS.indexTopLeftX = 25 /* 9 */;     
    playerS.indexTopLeftY = 10 /* 2 */; 

    // 187 = Starting index top left tile
    // 187 + 60 = 247

    mapPosition[0] = playerS.indexTopLeftX / 20;
    mapPosition[1] = playerS.indexTopLeftY / 18;

    mapStartingPosition = (/* Map Width -> */ 60 * (18 * mapPosition[1])) + 20 * mapPosition[0];

    set_bkg_submap(0, 0, 20, 18, overworldMap + mapStartingPosition, 60);

    initrand(seed);

    initializeHUD();

    SHOW_BKG;
    SHOW_SPRITES;
    SHOW_WIN;

    DISPLAY_ON;
}

void gameCoreLoop()
{
    playerCoreLoop(&playerS);

    // updateHUD();

    performatDelay(1);
}