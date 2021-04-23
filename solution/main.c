#include <gb/gb.h>

#include "game_Configuration.h"

int main(){
    initialize_Game();

    while (TRUE) { game_Core_Loop(); }
    return 0;
}