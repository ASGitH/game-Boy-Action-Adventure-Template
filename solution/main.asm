;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.7 #12016 (MINGW64)
;--------------------------------------------------------
	.module main
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _initialize_Game
	.globl _game_Core_Loop
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	G$main$0$0	= .
	.globl	G$main$0$0
	C$main.c$5$0_0$86	= .
	.globl	C$main.c$5$0_0$86
;main.c:5: int main(){
;	---------------------------------
; Function main
; ---------------------------------
_main::
	C$main.c$6$1_0$86	= .
	.globl	C$main.c$6$1_0$86
;main.c:6: initialize_Game();
	call	_initialize_Game
	C$main.c$8$1_0$86	= .
	.globl	C$main.c$8$1_0$86
;main.c:8: while (TRUE) { game_Core_Loop(); }
00102$:
	call	_game_Core_Loop
	C$main.c$9$1_0$86	= .
	.globl	C$main.c$9$1_0$86
;main.c:9: return 0;
	C$main.c$10$1_0$86	= .
	.globl	C$main.c$10$1_0$86
;main.c:10: }
	C$main.c$10$1_0$86	= .
	.globl	C$main.c$10$1_0$86
	XG$main$0$0	= .
	.globl	XG$main$0$0
	jr	00102$
	.area _CODE
	.area _CABS (ABS)
