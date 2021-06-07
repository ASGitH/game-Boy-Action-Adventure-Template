#include "player.h"

#include "backgrounds/headsUpDisplayMB.h"
#include "backgrounds/overworldMB.h"

#include "headsUpDisplay.h"

#include "sceneConfiguration.h"

#include "sprites/playerTD.h"

#include "stdio.h"

BOOLEAN hasPlayerBeenIntialized = FALSE;

UINT8 reinitalizationTimer = 0;

void initializePlayer(struct player *_player)
{
    hasPlayerBeenIntialized = TRUE;

    _player->attackRechargeCycle = 0;

    _player->damageDelayTimer = 0;

    _player->hasAttacked = FALSE;

    _player->isAbleToTakeDamage = TRUE;

    _player->lifeCounter = 3;

    _player->acquiredUnitsOfHealth = _player->lifeCounter;

    _player->movementDelayCycle = 0;

    // 4 - Default (No direction has been set)
    _player->playerDirection = /* 0 */ 4;

    _player->playerPosition[0] = _player->indexTopLeftX * 8 + 8; _player->playerPosition[1] = _player->indexTopLeftY * 8 + 16;

    _player->selectedSprite = 1;

    _player->tileIndexTopLeft = 0;

    set_sprite_data(0, 13, (unsigned char *)playerSprites);

    set_sprite_tile(0, 1);

    move_sprite(0, _player->playerPosition[0] % 160, _player->playerPosition[1] % 144);
}

void playerAttack(struct player *_player)
{
    if(!_player->hasAttacked)
    {
        // play_fx(0);

        _player->hasAttacked = 1;
        
        switch(_player->playerDirection)
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
    else
    {
        _player->attackRechargeCycle += 1;

        if(_player->attackRechargeCycle > 16)
        {
            _player->attackRechargeCycle = 0;

            _player->hasAttacked = 0;

            set_sprite_tile(1, 0);
        }
    }
}

void playerHealthManagement(char _action, struct player *_player)
{
    switch(_action)
    {
        // Take Damage
        case 'd':
            if(_player->isAbleToTakeDamage) 
            { 
                _player->isAbleToTakeDamage = FALSE;
                _player->lifeCounter -= 1;

                removeHeartFromHUD();

                set_sprite_tile(0, 11);
            } 
        break;
    }

    // Game Over State
    if(_player->lifeCounter == 0) 
    {
        reinitalizationTimer += 1;

        set_sprite_tile(0, 12);

        if(reinitalizationTimer > 128)
        {
            UINT8 lifeIndexCounter = 0;

            for(lifeIndexCounter = 0; lifeIndexCounter < _player->acquiredUnitsOfHealth; lifeIndexCounter++) { set_win_tiles(12 + lifeIndexCounter, 1, 1, 1, &headsUpDisplayMap[42]); } 
    
            hasPlayerBeenIntialized = FALSE;

            reinitalizationTimer = 0;
        } 
    }
    // Invincibility State if Damagaed
    else if(!_player->isAbleToTakeDamage)
    {
        _player->damageDelayTimer += 1;

        if(_player->damageDelayTimer >= 128) 
        {
            _player->damageDelayTimer = 0;
            _player->isAbleToTakeDamage = TRUE;
        }
    }
}

void playerMovement(struct player *_player)
{
    BOOLEAN canThePlayerMove = FALSE;

    switch(joypad())
    {
        case J_DOWN:
            if(_player->playerDirection != 0) 
            {
                _player->movementDelayCycle = 0;

                _player->selectedSprite = 1; 
            }

            _player->movementDelayCycle += 1;

            _player->playerDirection = 0;

            if(!sceneCollision(overworldMap, _player->tileIndexTopLeft, 0, 60)) 
            {
                canThePlayerMove = TRUE;

                _player->playerPosition[1] += 1; 
            }
            
            if(_player->movementDelayCycle >= 8) 
            {
                _player->movementDelayCycle = 0;

                if(_player->selectedSprite > 2) { _player->selectedSprite = 2; }
                else { _player->selectedSprite += 1; }
            }
        break;
        case J_LEFT:
            if(_player->playerDirection != 1) 
            {
                _player->movementDelayCycle = 0;
                
                _player->selectedSprite = 4; 
            }
            
            _player->movementDelayCycle += 1;

            _player->playerDirection = 1;

            if(!sceneCollision(overworldMap, _player->tileIndexTopLeft, 1, 60)) 
            {
                canThePlayerMove = TRUE;

                _player->playerPosition[0] -= 1; 
            }

            if(_player->movementDelayCycle >= 8) 
            {
                _player->movementDelayCycle = 0;

                if(_player->selectedSprite > 4) { _player->selectedSprite = 4; }
                else { _player->selectedSprite += 1; }
            }

            set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
        break;
        case J_RIGHT:
            if(_player->playerDirection != 2) 
            {
                _player->movementDelayCycle = 0;

                _player->selectedSprite = 4; 
            }
            
            _player->movementDelayCycle += 1;

            _player->playerDirection = 2;

            if(!sceneCollision(overworldMap, _player->tileIndexTopLeft, 2, 60)) 
            {
                canThePlayerMove = TRUE;

                _player->playerPosition[0] += 1; 
            }

            if(_player->movementDelayCycle >= 8) 
            {
                _player->movementDelayCycle = 0;

                if(_player->selectedSprite > 4) { _player->selectedSprite = 4; }
                else { _player->selectedSprite += 1; }
            }

            set_sprite_prop(0, get_sprite_prop(0) | S_FLIPX);
        break;
        case J_UP:
            if(_player->playerDirection != 3) 
            {
                _player->movementDelayCycle = 0;
                
                _player->selectedSprite = 7; 
            }

            _player->movementDelayCycle += 1;

            _player->playerDirection = 3;

            if(!sceneCollision(overworldMap, _player->tileIndexTopLeft, 3, 60)) 
            {
                canThePlayerMove = TRUE;

                _player->playerPosition[1] -= 1; 
            }

            if(_player->movementDelayCycle >= 8) 
            {
                _player->movementDelayCycle = 0;

                if(_player->selectedSprite > 7) { _player->selectedSprite = 7; }
                else { _player->selectedSprite += 1; }
            }
        break;
    }

    if(_player->isAbleToTakeDamage) { set_sprite_tile(0, _player->selectedSprite); }
                
    if(canThePlayerMove) { move_sprite(0, _player->playerPosition[0] % 160, _player->playerPosition[1] % 144); }
}

void updatePlayer(struct player *_player)
{
    _player->indexTopLeftX = (_player->playerPosition[0] - 8) / 8;     
    _player->indexTopLeftY = (_player->playerPosition[1] - 16) / 8; 

    _player->tileIndexTopLeft = /* Map Width -> */ (60 * _player->indexTopLeftY + _player->indexTopLeftX) + 1;
}

void playerCoreLoop(struct player *_player)
{
    if(!hasPlayerBeenIntialized) { initializePlayer(_player); }
    else
    {
        if(_player->lifeCounter != 0)
        {
            if(joypad() & J_B || _player->hasAttacked) { playerAttack(_player); }

            playerMovement(_player);
        
            updatePlayer(_player);
        }

        playerHealthManagement(' ', _player);
        
        if(joypad() & J_A) { playerHealthManagement('d', _player); }
    }
}