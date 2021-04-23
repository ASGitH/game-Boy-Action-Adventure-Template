#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>

struct player
{
    BOOLEAN is_Attacking;

    UINT16 index_Top_Left_X;
    UINT16 index_Top_Left_Y;
    UINT16 tile_Index_Top_Left;

    // Will keep track of the player's current position on screen
    UINT16 player_Position[2];

    UINT8 movement_Delay_Cycle;
    // 0 - Down, 1 - Left, 2 - Right, 3 - Up
    UINT8 player_Direction;
    UINT8 selected_Sprite;
};

extern BOOLEAN has_Player_Been_Intialized;

void initialize_Player(struct player *_player);

void player_Movement(struct player *_player);

void update_Player(struct player *_player);

void player_Core_Loop(struct player *_player);

#endif