// MT MK2 NES v0.8y - Yun Edition
// Copyleft 2017 by The Mojon Twins

// Hud. Of course, this has to be customized for each game
/*
void p_t1 (unsigned char x, unsigned char y, unsigned char n) {
	gp_addr = NAMETABLE_A + (y << 5) + x;
	*ul ++ = MSB (gp_addr);
	*ul ++ = LSB (gp_addr);
	*ul ++ = DIGIT (n);
}
*/
void hud_update (void) {
	if (pbodycount != opbodycount) {
		p_t2 (23, 26, l_max_killable_enems [level] - pbodycount);
		opbodycount = pbodycount;
	}

	if (plife != oplife) {
		p_t2 (29, 26, plife);
		oplife = plife;
	}

	if (pkeys != opkeys) {
		p_t2 (17, 26, pkeys);
		opkeys = pkeys;
	}
}

void hud_draw (void) {
	vram_adr (NAMETABLE_A);
	vram_unrle (hud_rle);
}
