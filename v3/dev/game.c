// MT MK2 NES v0.8y - Yun Edition
// Copyleft 2017 by The Mojon Twins

//#define STANDALONE	// Comment when assembling to main ROM.

// Shiru's

#include "neslib.h"

// Some needed stuff...

#include "definitions.h"

// Main const includes

#include "assets/palettes.h"
#include "assets/precalcs.h"
#include "assets/enems0.h"
#include "assets/map0.h"
#include "assets/enems1.h"
#include "assets/map1.h"
#include "assets/enems2.h"
#include "assets/map2.h"
#include "assets/enems3.h"
#include "assets/map3.h"
#include "assets/enems4.h"
#include "assets/map4.h"
#include "assets/tiledata.h"
#include "assets/metasprites.h"
#include "assets/behs.h"
#include "assets/levelset.h"
#include "assets/texts.h"
// #include "assets/script_texts.h"
// #include "assets/talk_scripts.h"
#include "assets/title_rle.h"
//#include "assets/event_rle.h"
#include "assets/hud_rle.h"
#include "assets/cuts_rle.h"

// Some variables

#pragma bss-name (push,"ZEROPAGE")
#pragma data-name(push,"ZEROPAGE")

#include "ram/zp.h"

#pragma bss-name (push,"BSS")
#pragma data-name(push,"BSS")

#include "ram/bss.h"

// Engine functions

#include "someprotos.h"
#include "engine/printer.h"
#include "engine/screens.h"
#include "engine/general.h"
#ifdef ENABLE_SPRINGS
#include "engine/spring.h"
#endif
#ifdef ENABLE_PROPELLERS
#include "engine/propellers.h"
#endif
#ifdef SCRIPTING_ON
#ifdef ENABLE_EXTERN_CODE
#include "engine/extern.h"
#endif
#include "engine/mscnes.h"
#endif
#ifdef SHOOTING_DRAINS
#include "engine/flower.h"
#endif
#ifdef BREAKABLE_WALLS
#include "engine/breakable.h"
#endif
#ifdef PLAYER_CAN_FIRE
#include "engine/bullets.h"
#endif
#ifndef DISABLE_HOTSPOTS
#include "engine/hotspots.h"
#endif
#ifdef HOTSPOT_TYPE_KEY
#include "engine/bolts.h"
#endif
#ifdef ENABLE_FUMETTOS
#include "engine/fumettos.h"
#endif
#ifdef ENABLE_PUAS
#include "engine/puas.h"
#endif
// CUSTOM {
// #include "engine/hitter.h"
// } END_OF_CUSTOM
#include "engine/hud.h"
#ifdef ENABLE_CONTAINERS
#include "engine/containers.h"
#endif
#ifdef ENABLE_FABOLEES
#include "engine/fabolee_int.h"
#endif
#include "engine/player.h"
#ifdef ENABLE_COCOS
#include "engine/simplecoco.h"
#endif
#include "engine/enems.h"
#include "engine/mapper11.h"
// #include "engine/talkbox.h"
#include "engine/game.h"

// Functions

void main (void) {

#ifndef STANDALONE	
	m11_handle_reset ();		// If bad checksum, this jumps to PRG 0 / CHR 0 (main menu)
	//level = COMM_GAME_SELECT;
#else
	//level = 1;
#endif	
	
#ifdef MAP_ENABLE_AUTOSHADOWS	
	mapmode_autoshadows = 1;
#endif
	
	bank_bg (0);
	bank_spr (1);
			
	ticks = ppu_system () ? 60 : 50;
	halfticks = ticks >> 1;

	oam_size (0);
	pal_bright (0);

	scroll (0, SCROLL_Y);
	
	// CUSTOM {
	pal_cycle [0] = 0x11;
	pal_cycle [1] = 0x21;
	pal_cycle [2] = 0x31;
	// } END_OF_CUSTOM

	// Run the game here.
	while (1) {
		game_title ();

		rdb = 0xfc; game_event ();

		plife = LIFE_INI;
		level = 0;

		while (1) {
			rdb = level; game_event ();
			hud_draw ();
			game_init ();
			game_loop ();

			if (pkilled) {
				rdb = 0xfe; game_event ();
				break;
			} else {
				rdb = 0xfd; game_event ();
				level ++;
				plife ++;
				if (level == 5) {
					game_ending ();
					break;
				}
				delay (10);
			}
		}
	}
}
