// Fabolee
// Simple bubbles

const unsigned char fabolee_frames [] = { 4, 5, 6, 5 };

void fabolee_init (void) {
	gpit = FABOLEES_MAX; while (gpit --) {
		fbl_ct [gpit] = 0; 
		oam_meta_spr (0, 240, OAM_FABOLEE + (gpit << 4), spr_empty);
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
	gpit = FABOLEES_MAX; while (gpit --) {
		if (fbl_ct [gpit]) {

			if (fbl_lock_on [gpit] == 0xff) {
				// Vertical
				if (fbl_vy [gpit] > -FABOLEES_VY_MAX) fbl_vy [gpit] -= FABOLEES_AY; else fbl_vy [gpit] = -FABOLEES_VY_MAX;
				fbl_y [gpit] += fbl_vy [gpit];
				if (fbl_y [gpit] <= 0) { fbl_y [gpit] = 0; fbl_vy [gpit] = 16 + (rand8 () & 31); }
				
				// Horizontal
				if (fbl_vx [gpit] < 0) { fbl_vx [gpit] += FABOLEES_AX; if (fbl_vx [gpit] > 0) fbl_vx [gpit] = 0; }
				if (fbl_vx [gpit] > 0) { fbl_vx [gpit] -= FABOLEES_AX; if (fbl_vx [gpit] < 0) fbl_vx [gpit] = 0; }
				fbl_x [gpit] += fbl_vx [gpit];
			} else {
				rda = fbl_lock_on [gpit];
				fbl_x [gpit] = en_x [rda] << 6; fbl_y [gpit] = en_y [rda] << 6;
			}

			rdx = fbl_x [gpit] >> 6;
			rdy = fbl_y [gpit] >> 6;

			// Render
			oam_meta_spr (rdx, rdy + SPRITE_ADJUST, OAM_FABOLEE + (gpit << 4), (fbl_ct [gpit] > 50 || half_life) ? spr_hs [fabolee_frames [(frame_counter + gpit) & 3]] : spr_empty);

			// Collide
			if (0xff == fbl_lock_on [gpit]) {
				gpjt = 3; while (gpjt --) {
					if (en_t [gpjt] && en_t [gpjt] != 4 && (en_t [gpjt] != 9 || en_mx [gpjt] == 2)) {
						if (collide (rdx, rdy, en_x [gpjt], en_y [gpjt])) {
							en_ud [gpjt] = 1;
							fbl_lock_on [gpit] = gpjt;
							sfx_play (5, 0);
						}
					}
				}	

				if (rdy > 16 && (!pj /*|| pctj > 8*/)) {
					if (prx + 11 >= rdx && prx <= rdx + 11) {
						if (pry + 17 >= rdy && pry + 12 <= rdy) {
							pgotten = 1; 
							pgtmy = fbl_vy [gpit]; pgtmx = fbl_vx [gpit];
							py = (rdy - 16) << 6; pry = py >> 6;
							pvy = 0;
						}
					}
				}
			}
			
			fbl_ct [gpit] --;

			// Free?
			if (!fbl_ct [gpit]) if (fbl_lock_on [gpit] != 0xff) en_ud [fbl_lock_on [gpit]] = 0;
		} else oam_meta_spr (0, 240, OAM_FABOLEE + (gpit << 4), spr_empty);
	}
}