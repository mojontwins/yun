// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// player.h
// Player movement & stuff

void player_init (void) {
	// Init player data

	px = (signed int) (((level == 2) ? 13 : PLAYER_INI_X) << 4) << 6;
	py = (signed int) (PLAYER_INI_Y << 4) << 6;
	
	pvx = pvy = 0;
	pfacing = 0;
	pfr = pctfr = 0;
	pj = pctj = 0;
	psprid = 6;
	pobjs = pkeys = 0;
	pgotten = 0;
	pfiring = 0;
	pstate = EST_NORMAL;
	pkilled = 0;

	px_safe = px;
	py_safe = py;
	n_pant_safe = n_pant;
}

void __fastcall__ kill_player (void) {
	plife --;
	pstate = EST_PARP;
	pctstate = 100;	
	sfx_play (4, 0);
	px = px_safe;
	py = py_safe;
	n_pant = n_pant_safe;
	music_pause (1);
	/*
	gpit = 60;
	while (gpit --) {
		ppu_waitnmi ();
	}
	*/
	wait_for (60);
	pvx = pvy = pj = 0;
	music_pause (0);
}

void process_tile (x0, y0) {
	if (pkeys) {
		map_set (x0, y0, 0);
		clear_cerrojo ((x0 << 4) + (y0 & 15));
		pkeys --;
		sfx_play (1, 1);
	} else {
		no_on = 1; no_ct = 100;
		oam_meta_spr ((x0 << 4) + 8, (y0 << 4) - 13 + SPRITE_ADJUST, OAM_NO, spr_hs_03);
	}
}


void player_move (void) {
	i = pad_poll (0);

	// ********
	// Vertical
	// ********

	// gravity
	if (!pj) { if (pvy < PLAYER_VY_FALLING_MAX) pvy += PLAYER_G; else pvy = PLAYER_VY_FALLING_MAX; }
	if (pgotten) pvy = 0;			

	// Move
	py += pvy;
	
	// Collision
	prx = px >> 6;
	pry = py >> 6;
	
	ptx1 = (prx + 4) >> 4;
	ptx2 = (prx + 11) >> 4;
	if (pvy + pgtmy < 0) {
		pty1 = (pry + 8) >> 4;
		at1 = attr (ptx1, pty1); at2 = attr (ptx2, pty1);
		if ((at1 & 8) || (at2 & 8)) {
			pvy = 0;
			pry = ((pty1 + 1) << 4) - 8;
			py = pry << 6;
			pgotten = 0;
		} else if ((at1 & 2) || (at2 & 2)) {
			if (pctj > 2) pj = 0;
		}
	} else if (pvy + pgtmy > 0)	{
		pty1 = (pry + 15) >> 4;
		at1 = attr (ptx1, pty1); at2 = attr (ptx2, pty1);
 		if (((pry - 1) & 15) < 8)		
			if ((at1 & 12) || (at2 & 12)) {
				pvy = 0;
				pry = ((pty1 - 1) << 4);
				py = pry << 6;
				pgotten = 0;
			} else if ((at1 & 2) || (at2 & 2)) {
				pvy = QUICKSANDS_SINK_VY;
			}
	}

	pty1 = (pry + 16) >> 4;
	at1 = attr (ptx1, pty1); at2 = attr (ptx2, pty1);
	ppossee = ((at1 & 14) || (at2 & 14));
	pice = (ppossee && ((at1 & 64) || (at2 & 64)));
	pconveyor = (ppossee && ((at1 & 32) || (at2 & 32)));
	pconvd1 = at1 & 1; pconvd2 = at2 & 2; 

	// Jump: PAD_A
	if (i & PAD_A) { 
		if (!pjb) {
			pjb = 1;
			if (!pj) {
				if (pgotten || ppossee) {
					pj = 1; 
					pctj = 0;
					sfx_play (7, 0);
					pvy = -PLAYER_VY_JUMP_INITIAL;
					if (!pgotten) {
						px_safe = px;
						py_safe = py;
						n_pant_safe = n_pant;
					}
				}
			} 
		}
		if (pj) {
			if (pctj < PLAYER_AY_JUMP) pvy -= (PLAYER_AY_JUMP - (pctj));
			if (pvy < -PLAYER_VY_JUMP_MAX) pvy = -PLAYER_VY_JUMP_MAX;
			pctj ++; if (pctj == 16) pj = 0;	
		}
	} else {
		pj = 0; pjb = 0;
	}

	// **********
	// Horizontal
	// **********
	
	// Conveyors
	if (pconveyor) {
		pgotten = 1;
		pgtmx = 0;
		if (pconvd1) pgtmx = 64; else pgtmx = -64;
		if (pconvd2) pgtmx = 64; else pgtmx = -64;
	}
	
	// Poll pad
	if (!(i & PAD_LEFT || i & PAD_RIGHT)) {
		if (pvx > 0) {
			pvx -= pice ? ICE_RX : PLAYER_RX;
			if (pvx < 0)
				pvx = 0;
		} else if (pvx < 0) {
			pvx += pice ? ICE_RX : PLAYER_RX;
			if (pvx > 0)
				pvx = 0;
		}
	}
	
	if (i & PAD_LEFT) {
		if (pvx > -PLAYER_VX_MAX) {
			pvx -= pice ? ICE_AX : PLAYER_AX;			
		}
		pfacing = CELL_FACING_LEFT;
	}
	
	if (i & PAD_RIGHT) {
		if (pvx < PLAYER_VX_MAX) {
			pvx += pice ? ICE_AX : PLAYER_AX;
		}
		pfacing = CELL_FACING_RIGHT;		
	}
	
	// Move
	if (py >= 0) {
		px += pvx;
		if (px < 0) px = 0;
		if (px > 15360) px = 15360;
		if (pgotten) px += pgtmx;
	}
	
	// Collision
	prx = px >> 6;

	pty1 = (pry + 8) >> 4;
	pty2 = (pry + 15) >> 4;
	if (pvx + pgtmx < 0) {
		ptx1 = (prx + 4) >> 4;
		at1 = attr (ptx1, pty1);
		if ((at1 & 8) || (attr (ptx1, pty2) & 8)) {
			pvx = 0;
			prx = ((ptx1 + 1) << 4) - 4;
			px = prx << 6;
			if (at1 == 10) process_tile (ptx1, pty1);
		}
	} else if (pvx + pgtmx > 0) {
		ptx1 = (prx + 11) >> 4;
		at1 = attr (ptx1, pty1);
		if ((at1 & 8) || (attr (ptx1, pty2) & 8)) {
			pvx = 0;
			prx = ((ptx1 - 1) << 4) + 4;
			px = prx << 6;
			if (at1 == 10) process_tile (ptx1, pty1);
		}
	}

	// *************
	// Killing tiles
	// *************
	prx = px >> 6;
	pry = py >> 6;

	if (attr ((prx + 8) >> 4, (pry + 8) >> 4) == 1) {
		kill_player ();
	}

	// ********
	// Fabolees
	// ********
	if (i & PAD_B) {
		if (!pfiring) fabolee_new ();
		pfiring = 1;
	} else pfiring = 0;

	// facing = 0 || 8
	// frame = 0 standing, 1 2 3 4 running, 5 jumping, 6 7 falling
	if (ppossee || pgotten) {
		if (pvx > PLAYER_VX_MIN || pvx < -PLAYER_VX_MIN) {
			psprid = pfacing + CELL_WALK_BASE + ((prx >> 4) & 3);
		} else {
			psprid = pfacing;
		}
	} else {
		psprid = pfacing + (pvy >= (PLAYER_VY_FALLING_MAX >> 3) ? CELL_DESCENDING : CELL_ASCENDING);
	}
}

void render_player (void) {
	if (pstate == EST_NORMAL || half_life) {
		oam_meta_spr (prx, pry + SPRITE_ADJUST, OAM_PLAYER, spr_player [psprid]);	
	} else {
		oam_meta_spr (0, 240, OAM_PLAYER, spr_pl_empty);
	}
}
