// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// Uses neslib and related tools by Shiru

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

// Music
extern const unsigned char m_ingame_0 [];
extern const unsigned char m_ingame_1 [];
extern const unsigned char m_ingame_2 [];
const unsigned char * const m_ingame [] = { m_ingame_0, m_ingame_1, m_ingame_2 };
extern const unsigned char m_title [];
extern const unsigned char m_gover [];

// RAM
#include "ram/zp.h"
#include "ram/bss.h"
// Update list
#define UPDATE_LIST_SIZE 32
unsigned char update_list [UPDATE_LIST_SIZE * 3];


// *************
// Main includes
// *************

void enems_kill (void); // Sorry

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
	
	while (1) {
		tsmap = (unsigned char *) (ts1_tmaps);
		
		tileset_pals = (unsigned char *) (ts1_pals);
		game_mode = GM_YUN;
		title ();
		plife = PLAYER_LIFE;

		if (game_mode == GM_YUN) cutscene ();
		game_over = 0;
		level = 0;

		while (1) {
			tsmap = (unsigned char *) (ts1_tmaps);
			tileset_pals = (unsigned char *) (ts1_pals);
			c_map = (unsigned char *) (l_c_map [level]);
			c_locks = (unsigned char *) (l_c_locks [level]);
			c_max_bolts = l_c_max_bolts [level];
			c_enems = (unsigned char *) (l_c_enems [level]);
			c_hotspots = (unsigned char *) (l_c_hotspots [level]);
			c_pal_bg = (unsigned char *) l_c_pal_bg [game_mode ? 3 + level : level];
			c_pal_fg = (unsigned char *) l_c_pal_fg [game_mode ? 3 + level : level];
			tmap_level_offset = l_tmap_level_offset [level];
			tmap_level_altbg = 48 + level;
			base_for_sprites = level << 2;
			n_pant = l_n_pant [level];
			pobjs = l_max_objs [level];
			
			level_screen ();

			scroll (0, 8);

			pal_bg (c_pal_bg);
			pal_spr (c_pal_fg);

			pplayeroffs = game_mode ? CELL_LIMITE_BASE : CELL_YUN_BASE; // Cheese

			cls ();

			draw_game_frame ();

			on_pant = 99;

			hotspots_load ();
			bolts_load ();
			player_init ();
			enems_persistent_load ();
			enems_persistent_deaths_load ();
	
			half_life = 0;
			oobjs = olife = okeys = 0xff;
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

			scroll (0, 0);

			if (game_over) {
				game_over_screen (); 
				break;
			} else {
				stage_clear_screen ();

				if (level < 2) {
					level ++;
				} else {
					game_ending ();
					break;
				}
			}
		}
	}
}
