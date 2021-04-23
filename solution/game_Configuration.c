#include "game_Configuration.h"

#include "player.h"

#include "rand.h"

#include "sprites/fontTD.h"

struct player player_S;

unsigned int seed = 0;

void game_Core_Loop()
{
    player_Core_Loop(&player_S);

    performat_Delay(1);
}

// void initializeHUD()
// {
//     set_win_tiles(0, 0, 20, 2, headsUpDisplayMap);

//     move_win(7, 124);
// }

void performat_Delay(UINT8 _number_Of_Loops)
{
    UINT8 i;

    for (i = 0; i < _number_Of_Loops; i++) { wait_vbl_done(); }
}

void text_Load_Font() 
{ 
    set_bkg_data(0, 49, (unsigned char *)fontSprites); 

    UINT8 offset_X = 0;
    UINT8 offset_Y = 0;

    UINT16 clear_Background = 0;

    char blank_Tile = ' ';

    for(clear_Background = 0; clear_Background < 360; clear_Background++)
    {
        set_bkg_tiles(offset_X, offset_Y, 1, 1, (unsigned char *)blank_Tile);

        offset_X += 1;

        if(offset_X >= 20) { offset_X = 0; offset_Y += 1; }
    }
}

void text_Print_Char_Bkg_Or_Win(UINT8 _x, UINT8 _y, char _bkg_Or_Win, unsigned char _chr) 
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
    
    if(_bkg_Or_Win != 'b') { set_win_tiles(_x, _y, 1, 1, &tile); }
    else { set_bkg_tiles(_x, _y, 1, 1, &tile); }
}

void text_Print_String_Bkg_Or_Win(UINT8 _x, UINT8 _y, char _bkg_Or_Win, unsigned char *_string) 
{
    UINT8 offset_X = 0;
    UINT8 offset_Y = 0;

    while (_string[0]) 
    {
        if (_string[0] == '\n') {
            offset_X = 0;
            offset_Y += 1;
        } 
        else 
        {
            text_Print_Char_Bkg_Or_Win(_x + offset_X, _y + offset_Y, _bkg_Or_Win, (unsigned char) _string[0]);

            offset_X += 1;
        }

        _string += 1;
    }
}

void initialize_Game()
{
    UINT8 temporary_Counter = 0;
    for(; temporary_Counter < 40; temporary_Counter++) { set_sprite_tile(temporary_Counter, 0); }

    text_Load_Font();

    initrand(seed);

    SHOW_BKG;
    SHOW_SPRITES;
    SHOW_WIN;

    DISPLAY_ON;
}