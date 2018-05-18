// Cutscene
// Churrera for NES 1.0
// Copyleft Mojon Twins 2013

// pres.h
// Game Over, Game Ending & other special screens

void entersandman (void) {
	ppu_on_all ();
	fade_in ();
}

void shutdownproperly (void) {
	oam_hide_rest (0);
	fade_out ();
	ppu_off ();
}

void common_pres_a (void) {
	pal_bg (mypal_title);
	un_rle_screen ((unsigned char *) scr_rle_1);
}

void common_pres_b (const unsigned char *music) {
	entersandman ();

	if (music) music_play (music);

	rda = (pad_poll (0) != 0);
	while (1) {
		i = pad_poll (0);
		if (i & (PAD_A | PAD_START | PAD_B)) {
			if (i & PAD_DOWN) game_mode = GM_LIMITE; break;
			if (!rda) break;
		}

		ppu_waitnmi ();
	}
	
	music_stop ();
	if (rdb == 0x66) {
		sfx_play (0, 1);
		wait_for (50);
	} else while (pad_poll (0));
	
	shutdownproperly ();
}

void game_over_screen (void) {
	common_pres_a ();
	pr_str (12, 14, str_strings_09);
	pr_str (11, 16, str_strings_0a);
	common_pres_b (0);
}

void game_ending (void) {
	common_pres_a ();		
	pal_spr (mypal_game_fg0);
	if (game_mode == GM_YUN) {
		pr_str (6, 12, str_strings_05);
		pr_str (5, 14, str_strings_06);
		pr_str (6, 16, str_strings_07);
		pr_str (5, 18, str_strings_08);
		spr_id = 10;
	} else {
		pr_str (6, 14, str_strings_0b);
		spr_id = 27;
	}
	entersandman ();

	rda = 120; rdb = 144; rdc = 0;
	while (!pad_poll (0)) {
		oam_meta_spr (rda, 120 + sine64x16 [(rdc + 16) & 63], 0, spr_en4_01);
		oam_meta_spr (rdb, 120 + sine64x16 [rdc & 63], 16, spr_player [spr_id]);

		rda --; rdb --; rdc ++;
		
		ppu_waitnmi ();
	}

	shutdownproperly ();
}

void level_screen (void) {
	cls ();
	pal_bg (mypal_game_bg0);

	pr_str (12, 15, str_strings_03);
	vram_put (level + 11);

	common_pres_b (0);
}

void stage_clear_screen (void) {
	pr_str (10, 15, str_strings_04);
	common_pres_b (0); 
}

void title (void) {
	un_rle_screen ((unsigned char *) scr_rle_0);
	pal_bright (0);
	pal_bg (mypal_title);
		
	pr_str (10, 18, str_strings_02);
	pr_str (5, 26, str_strings_00);

	rdb = 0x66; 
	common_pres_b (m_title);
	rdb = 0;
}

void credits (void) {
	pal_bg (mypal_mt);
	pal_spr (mypal_mt);

	pr_str (5, 26, str_strings_00);
	pr_str (4, 27, str_strings_01);

	entersandman ();

	rdy = 240; gpit = 255;
	while (gpit --) {
		if (pad_poll (0)) break;
		if (rdy == 121) sfx_play (0, 0);
		if (rdy > 120) rdy --;
		oam_meta_spr (102, rdy, 0, spr_mt_logo_00);
		ppu_waitnmi ();
	}
	shutdownproperly ();
}

void cutscene (void) {
	bank_bg (1);

	tsmap = (unsigned char *) (cuts_tmaps);
	tileset_pals = (unsigned char *) (cuts_pals);
	pal_bg (mypal_cuts);
	
	cls ();
	rdx = 8; rdy = 6;
	for (rdt = 0; rdt < 48; rdt ++) {
		draw_tile (); rdx += 2; if (rdx == 24) {
			rdx = 8; rdy += 2;
			if (rdy == 14 || rdy == 18) rdy += 2;
		}
	}
	vram_write (attr_table, 0x23c0, 64);

	common_pres_b (0);
	bank_bg (0);
}
