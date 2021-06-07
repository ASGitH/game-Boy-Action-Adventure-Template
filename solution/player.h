#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>

struct player
{
    BOOLEAN hasAttacked;
    BOOLEAN isAbleToTakeDamage;

    UINT16 indexTopLeftX;
    UINT16 indexTopLeftY;
    UINT16 tileIndexTopLeft;

    UINT16 playerPosition[2];

    UINT8 acquiredUnitsOfHealth;
    UINT8 attackRechargeCycle;
    UINT8 damageDelayTimer;
    UINT8 lifeCounter;
    UINT8 movementDelayCycle;
    // 0 - Down, 1 - Left, 2 - Right, 3 - Up
    UINT8 playerDirection;
    UINT8 selectedSprite;
};

extern BOOLEAN hasPlayerBeenIntialized;

void initializePlayer(struct player *_player);

void playerAttack(struct player *);

void playerHealthManagement(char _action, struct player *_player);

void playerMovement(struct player *_player);

void updatePlayer(struct player *_player);

void playerCoreLoop(struct player *_player);

#endif