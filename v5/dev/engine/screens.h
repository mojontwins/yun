// MT MK2 NES v0.8y - Yun Edition
// Copyleft 2017 by The Mojon Twins

// Code for fixed screens

void enter_screen (const unsigned char *pal, void (*func) (void)) {
	//scroll (0, 472);
	
	cls ();
	
	pal_bg (pal);
	(*func) ();
	
	ppu_on_all ();
	fade_in ();
}

void exit_cleanly (void) {
	//set_vram_update (0);
	music_stop ();
	fade_out ();
	oam_hide_rest (0);
	ppu_off ();	
}

void wait_time_or_input (void) {
	rda = (pad_poll (0) != 0);
	while (game_time) {
		ticker ++; if (ticker == ticks) {
			ticker = 0;
			game_time --;
		}

		if (pad_poll (0)) {
			if (!rda) break;
		} else {
			rda = 0;
		}

		ppu_wait_nmi ();
	}
}

void do_screen (unsigned char seconds) {
	game_time = seconds; ticker = 0;
	wait_time_or_input ();
	exit_cleanly ();
}

void screen_title (void) {
	vram_adr (NAMETABLE_A);
	vram_unrle (title_rle);
}

/*
void screen_game_over (void) {
}

void screen_game_ending (void) {
}
*/

void screen_draw_stars (void) {
	c_ts_pals = tsstars_pals;
	c_ts_tmaps = tsstars_tmaps;
	rdx = 9; rdy = 14; 
	for (gpit = 0; gpit < 7; gpit ++) {
		rdt = pstars [gpit]; draw_tile_advance ();
	}
}

void screen_event (void) {
	cls ();
	switch (rdb) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			// Level XX
			if (level < 7) {
				p_s (12, 12, "LEVEL 0");
				vram_put (level + 17);
				screen_draw_stars ();
			} else {
				p_s (10, 14, "SECRET LEVEL");
			}
			break;

		case 0xfb:
			vram_adr (NAMETABLE_A);
			vram_unrle (ending_rle);
			oam_hide_rest (oam_meta_spr (82, 88, 0, ssending_00));
			break;

		case 0xfc:
			// Cutscene
			bank_bg (1);
			pal_bg (palcuts);
			vram_adr (NAMETABLE_A);
			vram_unrle (cuts_rle);
			break;

		case 0xfd:
			// Stage clear
			if (level < 7) {
				screen_draw_stars ();
				rda = 12;
			} else rda = 14;
			p_s (10, rda, "STAGE CLEAR!");
			break;

		case 0xfe:
			// Game over
			if (level && pcontinues) {
				#ifdef LANG_ES		
					#ifdef SEVERAL_CONTINUES
						p_s (11, 14, "CONTINUA "); vram_put (DIGIT (pcontinues));
					#else
						p_s (11, 14, "CONTINUAR?");
					#endif
					p_s (12, 15, "SI<  >NO");
				#else	
					#ifdef SEVERAL_CONTINUES
						p_s (11, 14, "CONTINUE "); vram_put (DIGIT (pcontinues));
					#else
						p_s (11, 14, "CONTINUE ?");
					#endif
					p_s (12, 15, "YES = NO");
				#endif		
				rda = 10;
			} else rda = 14;
			p_s (11, rda, "GAME  OVER");

			break;

		case 0xff:
			// Ending
			vram_adr (NAMETABLE_A);
			vram_unrle (endingcuts_rle);

			if (rde) {
				p_s (6, 9, "CONGRATULATIONS, YUN!");
				p_s (5, 11, "YOU CLEARED ALL STAGES");
				p_s (5, 13, "AND COLLECTED ALL STARS");
				p_s (5, 15, "YOU GOT THE GOOD ENDING");
			} else {
				p_s (6, 9, "CONGRATULATIONS, YUN!");
				p_s (5, 11, "YOU HAVE DONE WELL, NOW");
				p_s (6, 13, "MAKE A BUBBLE AND FLY");
				p_s (5, 15, "ELSEWHERE!! OFF YOU GO!");
			}
			break;
	}
}
