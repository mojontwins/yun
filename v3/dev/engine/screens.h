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
	oam_hide_rest (0);
	music_stop ();
	fade_out ();
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
	p_s (10, 17, str_texts_01);
	p_s (5, 24, str_texts_00);
}

/*
void screen_game_over (void) {
}

void screen_game_ending (void) {
}
*/

void screen_event (void) {
	cls ();
	switch (rdb) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			// Level XX
			p_s (12, 15, str_texts_02);
			vram_put (level + 0x2b);
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
			p_s (10, 15, str_texts_03);
			break;

		case 0xfe:
			// Game over
			p_s (12, 15, str_texts_08);
			break;

		case 0xff:
			// Ending
			c_ts_tmaps = ts1_tmaps;
			c_ts_pals = ts1_pals;
			rdt = 0;
			for (rdy = 0; rdy < 28; rdy += 2) {
				if (rdy == 26) rdt = 6;
				if (rdy < 8 || rdy > 16) for (rdx = 0; rdx < 32; rdx += 2) {
					draw_tile ();
				}
			}

			p_s (6, 9, str_texts_04);
			p_s (5, 11, str_texts_05);
			p_s (6, 13, str_texts_06);
			p_s (5, 15, str_texts_07);
			break;
	}
}
