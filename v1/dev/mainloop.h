		while (1) {
			half_life = 1 - half_life; frame_counter ++;
			
			if (pstate == EST_PARP) {
				pctstate --;
				if (!pctstate) pstate = EST_NORMAL;
			}

			if (no_on) {
				if (no_ct) {
					no_ct --;
				} else {
					oam_meta_spr (0, 240, OAM_NO, spr_empty);
					no_on = 0;
				}
			}

			player_move ();

			pgotten = 0;
			pgtmx = 0;
			pgtmy = 0;

			fabolee_do ();

			enems_move ();

			simplecoco_do ();

			render_player ();

			#include "mainloop/cheat.h"

			#include "mainloop/pause.h"

			#include "mainloop/flickscreen.h"

			#include "mainloop/hud.h"

			#include "mainloop/hotspots.h"

			// Sync
			ppu_waitnmi ();
			clear_update_list ();
			update_index = 0;
			
			// Change screen
			if (on_pant != n_pant) {
				prepare_scr ();
				on_pant = n_pant;
			}

			// Conditions
			if (plife == 0) {					
				game_over = 1;
				break;
			}

			if (pkilled == baddies_count) {
				music_stop ();
				pr_str_upd (10, 12, str_strings_04);
				sfx_play (3, 1);
				wait_for (150);
				clear_update_list ();
				break;
			}
		}
