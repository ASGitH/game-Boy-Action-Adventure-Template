#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include <gb/gb.h>

void game_Core_Loop();

void performat_Delay(UINT8 _number_Of_Loops);

void text_Load_Font();

void text_Print_Char_Bkg_Or_Win(UINT8 _x, UINT8 _y, char _bkg_Or_Win, unsigned char _chr);

void text_Print_String_Bkg_Or_Win(UINT8 _x, UINT8 _y, char _bkg_Or_Win, unsigned char *_string);

void initialize_Game();

void initialize_HUD();

#endif