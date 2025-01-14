// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// Uses neslib and related tools by Shiru

// Use 0 form ROM1, 2 for ROM2, 4 for ROM3
#define BASE_LEVEL		2

// Comment this when you are done
//#define DEBUG
#define DEBUG_LEVEL		1
#define DEBUG_SCR_INI	11
#define DEBUG_INI_X		11
#define DEBUG_INI_Y		1
//

#define MAX_GANCHOS		16 	// Plenty!

#define MSB(x)			(((x)>>8))
#define LSB(x)			(((x)&0xff))
#define FIXBITS			6
#define SPRITE_ADJUST	7
#define TOP_ADJUST		2
#define COMM_POOL		((unsigned char*)0x0300)

// Update list
#define UPDATE_LIST_SIZE 32
unsigned char update_index;
unsigned char update_list [UPDATE_LIST_SIZE * 3];

#include "neslib.h"

// **************
// * const data *
// **************

#include "definitions.h"
#include "config.h"
#include "assets/palettes.h"
#include "assets/metasprites.h"
#include "assets/tiledata1.h"
#include "assets/mapa0.h"
#include "assets/mapa1.h"
#include "assets/mapa2.h"
#include "assets/enems0.h"
#include "assets/enems1.h"
#include "assets/enems2.h"
#include "assets/screens.h"
#include "assets/leveldata.h"
#include "assets/cutscene.h"
#include "assets/precalcs.h"
#include "assets/strings.h"

#ifdef ACTIVATE_SCRIPTING
extern const unsigned char *e_scripts [];
extern const unsigned char *f_scripts [];
#endif

// Music
extern const unsigned char m_ingame_0 [];
extern const unsigned char m_ingame_1 [];
extern const unsigned char m_ingame_2 [];
const unsigned char *m_ingame [] = { m_ingame_0, m_ingame_1, m_ingame_2 };
extern const unsigned char m_title [];
extern const unsigned char m_gover [];

// RAM
#include "ram/zp.h"
#include "ram/bss.h"

// *************
// Main includes
// *************

#include "engine/printer.h"
#include "engine/general.h"
#include "engine/bolts.h"
#include "engine/hotspots.h"
#include "engine/fabolee.h"
#include "engine/player.h"
#include "engine/simplecoco.h"
#include "engine/enengine.h"	
#include "engine/frame.h"
#include "engine/pres.h"
#include "prepare_screen.h"

// ***
// Go!
// ***

void main(void) {
	bank_spr (1);
	bank_bg (0);

	ppu_off ();

	credits ();
	scroll (0, 8);
		
	while (1) {	// This while(1) is to make this NROM-compatible for testing purposes.
		
		// Decode shared RAM

		// Security code: *04 = *05 + *06 + 7
		/*
		rda = COMM_POOL [4];
		plife = COMM_POOL [5];
		pcontinues = COMM_POOL [6];
		level = COMM_POOL [7];

		if (rda != plife + pcontinues + 7) {
			plife = PLAYER_LIFE;
			pcontinues = 0;
#ifdef DEBUG
			level = DEBUG_LEVEL;
#else		
			level = 0;
#endif			
		}
		*/
		tsmap = (unsigned char *) (ts1_tmaps);
		tileset_pals = (unsigned char *) (ts1_pals);
		level = title ();
		plife = PLAYER_LIFE;

		cutscene ();

		// Decoding done
	
		game_over = 0;

		while (1) {
			tsmap = (unsigned char *) (ts1_tmaps);
			tileset_pals = (unsigned char *) (ts1_pals);
			c_map = (unsigned char *) (l_c_map [level]);
			c_locks = (unsigned char *) (l_c_locks [level]);
			c_max_bolts = l_c_max_bolts [level];
			c_enems = (unsigned char *) (l_c_enems [level]);
			c_hotspots = (unsigned char *) (l_c_hotspots [level]);
			c_pal_bg = (unsigned char *) l_c_pal_bg [level];
			c_pal_fg = (unsigned char *) l_c_pal_fg [level];
			tmap_level_offset = l_tmap_level_offset [level];
			tmap_level_altbg = 48 + level;
			base_for_sprites = level << 2;
			n_pant = l_n_pant [level];
			
			level_screen ();

			pal_bg (c_pal_bg);
			pal_spr (c_pal_fg);		
			cls ();

			draw_game_frame ();

			on_pant = 99;

			hotspots_load ();
			bolts_load ();
			player_init ();
			persistent_enems_load ();
			persistent_deaths_load ();
	
			half_life = 0;
			olife = okeys = 0xff;
			okilled = 0xff;

			music_play (m_ingame [level]);
			set_vram_update (UPDATE_LIST_SIZE, update_list);

			ft = 1;
			
			// MAIN LOOP

			pal_bright (0);
			ppu_on_all ();

			#include "mainloop.h"
		
			music_stop ();
			set_vram_update (0, 0);
			fade_out ();
			ppu_off ();
			cls ();
			oam_clear ();	

			//ppu_on_all (); // Why? Shall I remove this, the game hangs.
			
			// HERE
			// When the game is finished, set flags and jump ROMs upon the value of game_over

			/*
			if (game_over) {
				// Write 6 6 6 18 to $301 on, launch ROM0
				COMM_POOL [1] = 6;
				COMM_POOL [2] = 6;
				COMM_POOL [3] = 6;
				COMM_POOL [4] = 18;
			} else {
				// Write 1 2 3 6 to $301 on, launch ROM0
				COMM_POOL [1] = 1;
				COMM_POOL [2] = 2;
				COMM_POOL [3] = 3;
				COMM_POOL [4] = 6;
			}
			//
			COMM_POOL [5] = plife;
			COMM_POOL [6] = pcontinues;
			COMM_POOL [7] = BASE_LEVEL + level; 
			// PRG-ROM 0, CHR-ROM 0; $300 = 0b0000 (0x00)
			COMM_POOL [0] = 0x00;
			__asm__ ("jmp _change_rom");
			*/

			if (game_over) {
				game_over_screen (); 
				break;
			} else if (level < 2) {
				level ++;
			} else {
				game_ending ();
				break;
			}
		}
	}
}
