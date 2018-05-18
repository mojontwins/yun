// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// player.h
// Player movement & stuff

void player_set_safe (void) {
	px_safe = px;
	py_safe = py;
	n_pant_safe = n_pant;
}

void player_reset_movement (void) {
	pvx = pvy = 0;
	pfr = pctfr = 0;
	pj = pctj = 0;
	pgotten = 0;
	pfiring = 0;
	pkilled = 0;
	pfloat = 0;	
}

void player_init (void) {
	// Init player data

	px = (signed int) (((level == 2) ? 13 : PLAYER_INI_X) << 4) << 6;
	py = (signed int) (PLAYER_INI_Y << 4) << 6;
	
	pfacing = 0;
	pkeys = 0;
	pstate = EST_NORMAL;
	player_reset_movement ();

	player_set_safe ();
}

void player_kill (void) {
	plife --;
	pstate = EST_PARP;
	pctstate = 100;	
	sfx_play (4, 0);
	px = px_safe;
	py = py_safe;
	n_pant = n_pant_safe;
	music_pause (1);
	wait_for (60);
	player_reset_movement ();
	music_pause (0);
	pkilled = 0;
}

void player_process_tile (x0, y0) {
	if (pkeys) {
		map_set (x0, y0, tmap_level_offset);
		
		rda = (y0 << 4) | x0;
		gpit = c_max_bolts; while (gpit --) {
			if (n_pant == lknp [gpit] && rda == lkyx [gpit]) {
				lkact [gpit] = 0;
			}
		}

		pkeys --;
		sfx_play (1, 1);
	} else {
		no_ct = 100;
		no_x = (x0 << 4) + 8; no_y = (y0 << 4) - 13;
	}
}

void player_points_beneath (void) {
	cy1 = cy2 = (pry + 16) >> 4;
	cm_two_points ();
}

void player_move (void) {
	i = pad_poll (0);
	phit = 0;

	// ********
	// Vertical
	// ********

	cx1 = (prx + 4) >> 4;
	cx2 = (prx + 11) >> 4;

	// gravity / propellers
	player_points_beneath ();
	if ((at1 & 128) || (at2 & 128)) {
		pvy -= HOTSPOT_PROPELLER_AY;
		if (pvy < -HOTSPOT_PROPELLER_VY_MAX) pvy = -HOTSPOT_PROPELLER_VY_MAX;
	} else {
		if (!pj) { 
			if (pfloat) {
				if (pvy < PLAYER_VY_FALLING_MAX_FLOAT) pvy += PLAYER_G_FLOAT; else pvy = PLAYER_VY_FALLING_MAX_FLOAT; 
			} else {
				if (pvy < PLAYER_VY_FALLING_MAX) pvy += PLAYER_G; else pvy = PLAYER_VY_FALLING_MAX; 
			}
		}
		if (pgotten) pvy = 0;			
	}

	// Move
	py += pvy;
	
	// Collision
	prx = px >> 6;
	pry = py >> 6;
	
	rds16 = pvy + pgtmy;
	if (rds16 < 0) {
		cy1 = cy2 = (pry + 8) >> 4;
		cm_two_points ();
		if ((at1 & 8) || (at2 & 8)) {
			pvy = 0;
			pry = ((cy1 + 1) << 4) - 8;
			py = pry << 6;
			pgotten = 0;
		} else if ((at1 & 2) || (at2 & 2)) {
			if (pctj > 2) pj = 0;
		}
	} else if (rds16 > 0)	{
		cy1 = cy2 = (pry + 15) >> 4; 
		cm_two_points (); 
 		if (((pry - 1) & 15) < 8 && ((at1 & 12) || (at2 & 12))) {
			pvy = 0;
			pry = ((cy1 - 1) << 4);
			py = pry << 6;
			pgotten = 0;
		} else {
			phit = ((at1 & 1) || (at2 & 1));
			if ((at1 & 2) || (at2 & 2)) pvy = QUICKSANDS_SINK_VY;
		}
	}

	player_points_beneath ();
	ppossee = ((at1 & 14) || (at2 & 14));
	pice = (ppossee && ((at1 & 64) || (at2 & 64)));
	
	// Conveyors
	
	if (ppossee) {
		pconvd1 = at1 & 1; pconvd2 = at2 & 1; 
		if (at1 & 32) { if (pconvd1) pgtmx = 64; else pgtmx = -64; pgotten = 1; }
		if (at2 & 32) { if (pconvd2) pgtmx = 64; else pgtmx = -64; pgotten = 1; }
	}

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
					if (!pgotten) player_set_safe ();
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
		if (pgotten) px += pgtmx;
	}
	
	// Collision
	if (px < 0) prx = 0;
	else if (px > 15360) prx = 240;
	else prx = px >> 6;

	cy1 = (pry + 8) >> 4;
	cy2 = (pry + 15) >> 4;
	rds16 = pvx + pgtmx;
	if (rds16) {
		if (rds16 < 0) {
			cx1 = cx2 = (prx + 4) >> 4;
			rda = ((cx1 + 1) << 4) - 4;
		} else {
			cx1 = cx2 = (prx + 11) >> 4;
			rda = ((cx1 - 1) << 4) + 4;
		}
		cm_two_points ();
		if ((at1 & 8) || (at2 & 8)) {
			pvx = 0;
			prx = rda;
			px = prx << 6;
			if (at1 == 10) player_process_tile (cx1, cy1);
		}
	}

	// *************
	// Killing tiles
	// *************
	prx = px >> 6;
	pry = py >> 6;

	if (phit) {
		if (pstate == EST_NORMAL) pkilled = 1; else pvy = -PLAYER_VY_JUMP_MAX;
	}

	// ****************
	// Fabolees / Volar
	// ****************

	if (game_mode == GM_YUN) {
		if (i & PAD_B) {
			if (!pfiring) fabolee_new ();
			pfiring = 1;
		} else pfiring = 0;
	} else {
		if (!ppossee && !pj && (i & PAD_B)) {
			if (!pfloat) pvy = 0;
			pfloat = 1;
		} else pfloat = 0;
	}

	// facing = 0 || 8
	// frame = 0 standing, 1 2 3 4 running, 5 jumping, 6 7 falling
	if (pfloat) {
		psprid = CELL_FLOAT;
	} else if (ppossee || pgotten) {
		if (pvx > PLAYER_VX_MIN || pvx < -PLAYER_VX_MIN) {
			psprid = CELL_WALK_BASE + ((prx >> 4) & 3);
		} else {
			psprid = 0;
		}
	} else {
		psprid = (game_mode == GM_YUN && (pvy >= (PLAYER_VY_FALLING_MAX >> 3)) ? CELL_DESCENDING : CELL_ASCENDING);
	}

	psprid += pfacing + pplayeroffs;
}

void player_render (void) {
	if (pstate == EST_NORMAL || half_life) {
		oam_index = oam_meta_spr (prx, pry + SPRITE_ADJUST, oam_index, spr_player [psprid]);	
	} 
}
