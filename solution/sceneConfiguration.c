#include "sceneConfiguration.h"

// What constitutes the area the player can collide with 
const unsigned char collisionTiles[16] = {0x34, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4F, 0x50, 0x51, 0x52};

BOOLEAN sceneCollision(const unsigned char *_map, UINT16 _tileIndexTopLeft, UINT8 _direction, UINT8 _mapW)
{
    BOOLEAN hasCollided = FALSE;

    UINT8 collisionTileSize = 0;

    for(collisionTileSize = 0; collisionTileSize < 16; collisionTileSize++)
    {
        switch(_direction)
        {
            // Down
            case 0: if(_map[_tileIndexTopLeft + _mapW] == collisionTiles[collisionTileSize]) { hasCollided = TRUE; } break;
            // Left
            case 1: if(_map[_tileIndexTopLeft - 1] == collisionTiles[collisionTileSize]) { hasCollided = TRUE; } break;
            // Right
            case 2: if(_map[_tileIndexTopLeft] == collisionTiles[collisionTileSize]) { hasCollided = TRUE; } break;
            // Up
            case 3: if(_map[_tileIndexTopLeft] == collisionTiles[collisionTileSize]) { hasCollided = TRUE; } break;
        }
    }  

    return hasCollided;
}

/*
void screenTransition(UINT16 _tileIndexTopLeft, UINT8 _direction)
{
    switch(_direction)
        {
            // Down
            case 0:
                set_sprite_tile(1, 10);

                move_sprite(1, _player->playerPosition[0], _player->playerPosition[1] + 8);

                set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPY);
            break;
            // Left
            case 1:
                set_sprite_tile(1, 9);

                move_sprite(1, _player->playerPosition[0] - 8, _player->playerPosition[1]);
                
                set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
            break;
            // Right
            case 2:
                set_sprite_tile(1, 9);

                move_sprite(1, _player->playerPosition[0] + 8, _player->playerPosition[1]); 
                
                set_sprite_prop(1, get_sprite_prop(1) | S_FLIPX);
            break;
            // Up
            case 3:
                set_sprite_tile(1, 10);

                move_sprite(1, _player->playerPosition[0], _player->playerPosition[1] - 8); 
                
                set_sprite_prop(1, get_sprite_prop(1) | S_FLIPY);
            break;
        }
    }
}
*/