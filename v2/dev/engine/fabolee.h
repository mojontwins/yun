// Fabolee
// Simple bubbles

const unsigned char fabolee_frames [] = { 6, 7, 8, 7 };

void fabolee_init (void) {
	gpit = FABOLEES_MAX; while (gpit --) {
		fbl_ct [gpit] = 0; 
	}
}

void fabolee_new (void) {
	// Creates new fabolee at px, py.
	gpit = FABOLEES_MAX; while (gpit --) {
		if (!fbl_ct [gpit]) {
			fbl_y [gpit] = py; fbl_x [gpit] = px;
			fbl_vy [gpit] = 0; fbl_vx [gpit] = pfacing ? -FABOLEES_VX_INI : FABOLEES_VX_INI;
			fbl_ct [gpit] = 200; fbl_lock_on [gpit] = 0xff;
			sfx_play (5, 0);
			break;
		}
	}
}

void fabolee_do (void) {
	rdct = FABOLEES_MAX; while (rdct --) {
		if (fbl_ct [rdct]) {
			gpit = fbl_lock_on [rdct];

			if (gpit == 0xff) {
				if (half_life) {
					// Vertical
					fbl_vy [rdct] = saturate (fbl_vy [rdct] - FABOLEES_AY - FABOLEES_AY, FABOLEES_VY_MAX);
					if (fbl_y [rdct] <= 0) { fbl_y [rdct] = 0; fbl_vy [rdct] = 16 + (rand8 () & 31); }
					
					// Horizontal
					fbl_vx [rdct] = (abs (fbl_vx [rdct]) < FABOLEES_AX) ? 0 : fbl_vx [rdct] - add_sign (fbl_vx [rdct], FABOLEES_AX + FABOLEES_AX);

					if (fbl_x [rdct] < 0)		{ fbl_x [rdct] = 0;		fbl_vx [rdct] = -fbl_vx [rdct]; }
					if (fbl_x [rdct] > 15360)	{ fbl_x [rdct] = 15360;	fbl_vx [rdct] = -fbl_vx [rdct]; }
				}
				fbl_x [rdct] += fbl_vx [rdct];
				fbl_y [rdct] += fbl_vy [rdct];
			} else {	
				fbl_x [rdct] = en_x [gpit] << 6; fbl_y [rdct] = en_y [gpit] << 6;
				if (en_y [gpit] == 240) {
					fbl_lock_on [rdct] = 0xff;
					enems_kill ();
				}
			}	

			rdx = fbl_x [rdct] >> 6;
			rdy = fbl_y [rdct] >> 6;

			// Render
			if (fbl_ct [rdct] > 50 || half_life) oam_index = oam_meta_spr (rdx, rdy + SPRITE_ADJUST, oam_index, spr_hs [fabolee_frames [(frame_counter + rdct) & 3]]);

			// Collide
			if (gpit == 0xff) {
				if (half_life) {
					gpjt = 3; while (gpjt --) {
						if (en_t [gpjt] && en_t [gpjt] != 4 && (en_t [gpjt] != 9 || en_mx [gpjt] == 2) && !en_ud [gpjt]) {
							if (collide (rdx, rdy, en_x [gpjt], en_y [gpjt])) {
								en_ud [gpjt] = 1;
								fbl_lock_on [rdct] = gpjt;
								sfx_play (5, 0);
							}
						}
					}	
				}

				if (rdy > 16 && (!pj)) {
					if (prx + 11 >= rdx && prx <= rdx + 11) {
						if (pry + 17 >= rdy && pry + 12 <= rdy) {
							pgotten = 1; 
							pgtmy = fbl_vy [rdct]; pgtmx = fbl_vx [rdct];
							py = (rdy - 16) << 6; pry = py >> 6;
							pvy = 0;
						}
					}
				}
			}

			fbl_ct [rdct] --;

			// Free?
			if (!fbl_ct [rdct] && gpit != 0xff) {
				en_ud [gpit] = 0;
				if (en_t [gpit] == 9) enems_kill ();
			}
		} 
	}
}