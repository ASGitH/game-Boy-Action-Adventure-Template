#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include <gb/gb.h>

extern struct player playerS;

void performatDelay(UINT8 _numberOfLoops);

void textLoadFont();

void textPrintCharBkgOrWin(UINT8 _x, UINT8 _y, char _bkgOrWin, unsigned char _chr);

void textPrintStringBkgOrWin(UINT8 _x, UINT8 _y, char _bkgOrWin, unsigned char *_string);

void initializeHUD();

void initializeGame();

void gameCoreLoop();

#endif