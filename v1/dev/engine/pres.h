// Cutscene
// Churrera for NES 1.0
// Copyleft Mojon Twins 2013

// pres.h
// Game Over, Game Ending & other special screens

void common_pres_a (void) {
	pal_bg (mypal_title);
	un_rle_screen ((unsigned char *) scr_rle_1);
}

void common_pres_b (void) {
	ppu_on_all ();
	fade_in ();
	
	if (rda) music_play (m_gover);
	
	while (1) {
		i = pad_poll (0);
		if (i & PAD_A || i & PAD_B || i & PAD_START) break;
	}
	
	music_stop ();
	
	fade_out ();
	ppu_off ();
}

void game_over_screen (void) {
	common_pres_a ();
	pr_str (12, 14, str_strings_09);
	pr_str (11, 16, str_strings_0a);

	rda = 0; common_pres_b ();
}

void game_ending (void) {
	common_pres_a ();		
	pr_str (6, 12, str_strings_05);
	pr_str (5, 14, str_strings_06);
	pr_str (6, 16, str_strings_07);
	pr_str (5, 18, str_strings_09);

	rda = 1; common_pres_b ();
}

void level_screen (void) {
	cls ();
	pal_bg (mypal_game_bg0);

	pr_str (12, 15, str_strings_03);
	vram_put (level + 11);

	rda = 0; common_pres_b ();
}

unsigned char title (void) {
	un_rle_screen ((unsigned char *) scr_rle_0);
	pal_bright (0);
	pal_bg (mypal_title);
		
	pr_str (10, 18, str_strings_02);
	pr_str (5, 26, str_strings_00);

	ppu_on_all ();
	fade_in ();
	
	music_play (m_title);

	while (1) {
		i = pad_poll (0); if (i & PAD_START) break;
	}
	while (pad_poll (0));
	
	music_stop (); 
	sfx_play (0, 1);
	wait_for (50);
	
	fade_out ();
	oam_clear ();
	ppu_off ();
	
	return 0; // fixed level 0 
}

signed int lower_end;
void credits (void) {
	pal_spr (mypal_game_fg1);
	pal_bg (mypal_title);
	
	oam_clear (); scroll (0, 0);
	
	lower_end = 0; rdy = 240;

	pr_str (5, 26, str_strings_00);
	pr_str (4, 27, str_strings_01);
	
	pal_bright (0);
	ppu_on_all ();
	fade_in ();

	while (!(pad_poll (0) & PAD_START) && lower_end < 300) {
		oam_meta_spr (102, rdy, 0, spr_mt_logo_00);
		if (rdy > 112) rdy --;
		ppu_waitnmi ();
		lower_end ++;
	};
	fade_out ();
	
	ppu_off ();
	oam_clear ();
}

void cutscene (void) {
	scroll (0, 0);
	bank_bg (1);

	tsmap = (unsigned char *) (cuts_tmaps);
	tileset_pals = (unsigned char *) (cuts_pals);
	pal_bg (mypal_cuts);
	
	cls ();
	rdx = 8; rdy = 6;
	for (gpit = 0; gpit < 48; gpit ++) {
		draw_tile (rdx, rdy, gpit); rdx += 2; if (rdx == 24) {
			rdx = 8; rdy += 2;
			if (rdy == 14 || rdy == 18) rdy += 2;
		}
	}
	vram_write (attr_table, 0x23c0, 64);

	rda = 0; common_pres_b ();
	bank_bg (0);
	scroll (0, 8);
}
