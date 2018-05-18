		while (1) {
			
			oam_index = 0;
			ul = update_list;

			// Change screen
			if (on_pant != n_pant) {
				prepare_scr ();
				on_pant = n_pant;
			}
			
			half_life = 1 - half_life; frame_counter ++;
			
			if (pstate == EST_PARP) {
				pctstate --;
				if (!pctstate) pstate = EST_NORMAL;
			}

			if (no_ct) {
				no_ct --;
				oam_index = oam_meta_spr (no_x, no_y, oam_index, spr_hs_05);
			}

			player_move ();

			pgotten = 0;
			pgtmx = 0;
			pgtmy = 0;

			fabolee_do ();

			enems_move ();

			simplecoco_do ();

			// Render hotspot
			if (hrt == HOTSPOT_TYPE_PROPELLER && half_life) oam_index = oam_meta_spr (hrx, hry + SPRITE_ADJUST - 8 - (frame_counter & 63), oam_index, spr_hs [4]); 
			if (hrt) oam_index = oam_meta_spr (hrx, hry + SPRITE_ADJUST, oam_index, spr_hs [hrt - 1]);			

			player_render ();

			#include "mainloop/cheat.h"

			#include "mainloop/pause.h"

			#include "mainloop/flickscreen.h"

			#include "mainloop/hud.h"

			#include "mainloop/hotspots.h"

			oam_hide_rest (oam_index);

			// Sync
			*ul = 0xff;
			ppu_waitnmi ();
			
			// Conditions
			if (pkilled) player_kill ();

			if (plife == 0) {					
				game_over = 1;
				break;
			}

			if (!baddies_count || !pobjs) {
				break;
			}
		}
