#include "player.h"

#include "sprites/playerTD.h"

BOOLEAN has_Player_Been_Intialized = FALSE;

void initialize_Player(struct player *_player)
{
    has_Player_Been_Intialized = TRUE;

    // 4 - Default (No direction has been set)
    _player->player_Direction = /* 0 */ 4;

    _player->index_Top_Left_X = 0;
    _player->index_Top_Left_Y = 0;
    
    _player->movement_Delay_Cycle = 0;

    _player->player_Position[0] = 80; _player->player_Position[1] = 72;
    
    _player->selected_Sprite = 1;

    _player->tile_Index_Top_Left = 0;

    set_sprite_data(0, 10, (unsigned char *)playerSprites);

    set_sprite_tile(0, 1);
    move_sprite(0, _player->player_Position[0], _player->player_Position[1]);
}

void player_Movement(struct player *_player)
{
    switch(joypad())
    {
        case J_DOWN:
            if(_player->player_Direction != 0) 
            {
                _player->movement_Delay_Cycle = 0;

                _player->selected_Sprite = 1; 
            }

            _player->movement_Delay_Cycle += 1;

            _player->player_Direction = 0;

            if(_player->index_Top_Left_Y < 17) { _player->player_Position[1] += 1; } 
            
            if(_player->movement_Delay_Cycle >= 8) 
            {
                _player->movement_Delay_Cycle = 0;

                if(_player->selected_Sprite > 2) { _player->selected_Sprite = 2; }
                else { _player->selected_Sprite += 1; }
            }
        break;
        case J_LEFT:
            if(_player->player_Direction != 1) 
            {
                _player->movement_Delay_Cycle = 0;
                
                _player->selected_Sprite = 4; 
            }
            
            _player->movement_Delay_Cycle += 1;

            _player->player_Direction = 1;

            if(_player->index_Top_Left_X > 0) { _player->player_Position[0] -= 1; }

            if(_player->movement_Delay_Cycle >= 8) 
            {
                _player->movement_Delay_Cycle = 0;

                if(_player->selected_Sprite > 5) { _player->selected_Sprite = 5; }
                else { _player->selected_Sprite += 1; }
            }

            set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
        break;
        case J_RIGHT:
            if(_player->player_Direction != 2) 
            {
                _player->movement_Delay_Cycle = 0;

                _player->selected_Sprite = 4; 
            }
            
            _player->movement_Delay_Cycle += 1;

            _player->player_Direction = 2;

            if(_player->index_Top_Left_X < 18) { _player->player_Position[0] += 1; } 

            if(_player->movement_Delay_Cycle >= 8) 
            {
                _player->movement_Delay_Cycle = 0;

                if(_player->selected_Sprite > 5) { _player->selected_Sprite = 5; }
                else { _player->selected_Sprite += 1; }
            }

            set_sprite_prop(0, get_sprite_prop(0) | S_FLIPX);
        break;
        case J_UP:
            if(_player->player_Direction != 3) 
            {
                _player->movement_Delay_Cycle = 0;
                
                _player->selected_Sprite = 7; 
            }

            _player->movement_Delay_Cycle += 1;

            _player->player_Direction = 3;

            if(_player->index_Top_Left_Y > 0) { _player->player_Position[1] -= 1; }

            if(_player->movement_Delay_Cycle >= 8) 
            {
                _player->movement_Delay_Cycle = 0;

                if(_player->selected_Sprite > 8) { _player->selected_Sprite = 8; }
                else { _player->selected_Sprite += 1; }
            }
        break;
    }

    set_sprite_tile(0, _player->selected_Sprite);
            
    move_sprite(0, _player->player_Position[0], _player->player_Position[1]);
}

void update_Player(struct player *_player)
{
    _player->index_Top_Left_X = (_player->player_Position[0] - 8) / 8;
    _player->index_Top_Left_Y = (_player->player_Position[1] - 16) / 8;
    _player->tile_Index_Top_Left = 32 * _player->index_Top_Left_Y + _player->index_Top_Left_X;
}

void player_Core_Loop(struct player *_player)
{
    if(!has_Player_Been_Intialized) { initialize_Player(_player); }
    else
    {
        player_Movement(_player);
        
        update_Player(_player);
    }
}