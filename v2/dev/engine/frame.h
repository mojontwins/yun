// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// frame.h
// Custom game frame

const unsigned char game_frame [] = {
	0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3a,0x3a,0x3c,0x3a,0x3a,0x3d,0x3a,0x3e,
	0x3f,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x45,0x48,0x47,0x45,0x49,0x47,0x4a
};

void __fastcall__ draw_game_frame (void) {
	rdy = 26; rdx = 0; gp_gen = (unsigned char *) game_frame; rdit = 32; while (rdit --) {
		rdt = *gp_gen ++; draw_tile_advance ();
	}

	if (game_mode == GM_LIMITE) {
		rdx = 20; rdy = 26; rdt = 75; draw_tile (); rdy = 28; rdt = 76; draw_tile ();
	}

	for (rdit = 56; rdit < 64; rdit ++) attr_table [rdit] = 0xff;
}
