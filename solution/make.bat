@echo off
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -o main.gb main.o backgrounds/headsUpDisplayMB.c backgrounds/overworldMB.c gameConfiguration.c headsUpDisplay.c player.c sceneConfiguration.c sprites/fontTD.c sprites/overworldTD.c sprites/playerTD.c