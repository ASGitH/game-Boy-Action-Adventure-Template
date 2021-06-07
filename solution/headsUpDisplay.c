#include "headsUpDisplay.h"

#include "backgrounds/headsUpDisplayMB.h"

#include "gameConfiguration.h"

#include "player.h"

void addHeartToHUD() { set_win_tiles(12 + playerS.lifeCounter, 1, 1, 1, &headsUpDisplayMap[41]); }

void removeHeartFromHUD() { set_win_tiles(12 + playerS.lifeCounter, 1, 1, 1, &headsUpDisplayMap[41]); }

void updateHUD() { }