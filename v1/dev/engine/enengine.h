// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// enengine.h
// Enemies Engine & stuff

void persistent_enems_load (void) {
	gp_gen = (unsigned char *) (c_enems);
	baddies_count = 0;
	for (ep_it = 0; ep_it < 3 * MAP_W * MAP_H; ep_it ++) {
		// Skip t
		rdt = *gp_gen ++; if (rdt && rdt != 4) baddies_count ++;

		// XY1
		rda = *gp_gen ++;
		ep_x [ep_it] = rda & 0xf0;
		ep_y [ep_it] = rda << 4;

		// XY2
		rda = *gp_gen ++;
		rdb = rda & 0xf0;
		rdc = rda << 4;

		// P, here used for speed
		rda = *gp_gen ++;
		ep_mx [ep_it] = add_sign (rdb - ep_x [ep_it], rda);
		ep_my [ep_it] = add_sign (rdc - ep_y [ep_it], rda);		
	}
}

void persistent_update (void) {
	if (on_pant != 99) {
		ep_it = on_pant + on_pant + on_pant;
		for (gpit = 0; gpit < 3; gpit ++) {
			ep_x [ep_it] = en_x [gpit];
			ep_y [ep_it] = en_y [gpit];
			ep_mx [ep_it] = en_mx [gpit] << (1 - en_status [gpit]);
			ep_my [ep_it] = en_my [gpit] << (1 - en_status [gpit]);	
			ep_it ++;
		}	
	}
}

void persistent_deaths_load (void) {
	gpit = MAP_W * MAP_H * 3; while (gpit --) {
		ep_flags [gpit] |= 0x01;
	}
}

void enems_load (void) {
	// Loads enems from n_pant
	
	// Read 3 enemies from enems ROM pool and populate my arrays properly.
	// If persistent enemies on: x, y, mx, my read from RAM pool.
	// If persistent deaths on: read ep_flags and modify en_t accordingly.

	// Each screen holds 3 * 4 bytes of enemies, that's 12 bytes per screen.
	// 12 = 4 + 8 so you know the drill...
	gp_gen = (unsigned char *) (c_enems + (n_pant << 2) + (n_pant << 3));

	// Notice that enemies are writen backwards. Take in account in the future

	rdc = n_pant + n_pant + n_pant;

	for (gpit = 0; gpit < 3; gpit ++) {
		oam_meta_spr (0, 240, OAM_ENEMS + (gpit << 4), spr_empty);

		// Fast hack. If enemy is dead, change for type 0 and skip data.
		if (!ep_flags [rdc] & 1) {
			en_t [gpit] = 0;
			gp_gen += 4;
		} else {
			en_ud [gpit] = 0;

			// First get T, then do whatever I need
			en_t [gpit] = *gp_gen ++;

			// General...

			// XY1
			rda = *gp_gen ++;
			en_x1 [gpit] = rda & 0xf0;
			en_y1 [gpit] = rda << 4;

			// XY2
			rda = *gp_gen ++;
			en_x2 [gpit] = rda & 0xf0;
			en_y2 [gpit] = rda << 4;
		
			// P, here used for speed
			rda = *gp_gen ++;

			// But...
			en_x [gpit] = ep_x [rdc];
			en_y [gpit] = ep_y [rdc];
			en_mx [gpit] = ep_mx [rdc];
			en_my [gpit] = ep_my [rdc];

			switch (en_t [gpit]) {
				case 1:
				case 2:
				case 3:
				case 4:
					// Linear enems.			

					// HL conversion
					en_s [gpit] = en_t [gpit] - 1;
					if (rda == 1) {
						en_status [gpit] = 1; 
					} else {
						en_status [gpit] = 0;
						en_mx [gpit] >>= 1;
						en_my [gpit] >>= 1;
					}

					// Fix limits so 1 < 2 always.
					if (en_x1 [gpit] > en_x2 [gpit]) { rda = en_x1 [gpit]; en_x1 [gpit] = en_x2 [gpit]; en_x2 [gpit] = rda; }
					if (en_y1 [gpit] > en_y2 [gpit]) { rda = en_y1 [gpit]; en_y1 [gpit] = en_y2 [gpit]; en_y2 [gpit] = rda; }
					
					break;

				case 6:
					// Fantys
					enf_x [gpit] = en_x [gpit] << 6;
					enf_y [gpit] = en_y [gpit] << 6;
					enf_vx [gpit] = enf_vy [gpit] = 0;
					break;

				case 9:
					// Monococos
					en_mx [gpit] = 0; en_my [gpit] = BASE_TIME_HIDDEN - (rand8 () & 0x15);
			}

			en_cttouched [gpit] = 0;
		}
		rdc ++;
	}
}

void enems_kill (void) {	
	en_touched [gpit] = 1;
	en_cttouched [gpit] = 8;
	sfx_play (6, 2);
	
	en_t [gpit] = 0;
	ep_flags [n_pant + n_pant + n_pant + gpit] &= 0xFE;
	
	pkilled ++;

	// Find fabolee(s) locked on to this
	gpjt = FABOLEES_MAX; while (gpjt --) if (fbl_lock_on [gpjt] == gpit) fbl_ct [gpjt] = 0;
}

void enems_move (void) {
	// Updates sprites
	for (gpit = 0; gpit < 3; gpit ++) {
		if (en_touched [gpit]) {
			en_cttouched [gpit] --;
			if (!en_cttouched [gpit]) {
				en_touched [gpit] = 0;
			} else {
				oam_meta_spr (en_x [gpit], en_y [gpit] + SPRITE_ADJUST, OAM_ENEMS + (gpit << 4), spr_hs_02);
				continue;
			}
		}
		
		if (en_t [gpit]) {

			// Gotten preliminary:
			gpjt = (prx + 11 >= en_x [gpit] && prx <= en_x [gpit] + 11);

			if (en_mx [gpit] != 0) {
				en_fr = ((en_x [gpit]) >> 4) & 1;
			} else {
				en_fr = ((en_y [gpit]) >> 4) & 1;
			}

			if (en_ud [gpit]) {
				ptx1 = (en_x [gpit] + 4) >> 4;
				ptx2 = (en_x [gpit] + 11) >> 4;
				pty2 = (en_y [gpit] + 15) >> 4;
				if (!(attr (ptx1, pty2) + attr (ptx2, pty2))) { en_y [gpit] ++; enf_y [gpit] = en_y [gpit] << 6; } else {
					if (en_t [gpit] == 9) enems_kill ();
				}
			}

			switch (en_t [gpit]) {
				case 1:
				case 2:
				case 3:
				case 4:
					#include "engine/enemmods/enem_linear.h"
					break;
				case 6:
					#include "engine/enemmods/enem_fanty.h"
					break;
				case 9:
					#include "engine/enemmods/enem_monococo.h"
					break;
			}

			// Paint

			oam_meta_spr (
				spr_x, spr_y + SPRITE_ADJUST, 
				OAM_ENEMS + (gpit << 4), 
				spr_enems [spr_id]);

			if (en_t [gpit] == 4) {
				if (gpjt && !pgotten && !pj) {
					// Horizontal moving platforms
					if (en_mx [gpit]) {
						if (pry + 16 >= en_y [gpit] && pry + 12 <= en_y [gpit]) {
							pgotten = 1;
							pgtmx = en_mx [gpit] << (6 - en_status [gpit]);
							py = (en_y [gpit] - 16) << 6; pry = py >> 6;
						}
					}
					
					// Vertical moving platforms
					if (
						(en_my [gpit] < 0 && pry + 17 >= en_y [gpit] && pry + 12 <= en_y [gpit]) ||
						(en_my [gpit] > 0 && pry + 16 + en_my [gpit] >= en_y [gpit] && pry + 12 <= en_y [gpit])
					) {
						pgotten = 1;
						pgtmy = en_my [gpit] << (6 - en_status [gpit]);
						py = (en_y [gpit] - 16) << 6; pry = py >> 6;
						pvy = 0;
					}
				} 
			} else if (pstate == EST_NORMAL && collide (prx, pry, en_x [gpit], en_y [gpit])) {
				if (en_ud [gpit]) {
					if (!pad_poll (0) & PAD_B) {
						pvy = -PLAYER_VY_JUMP_INITIAL << 1;
					} else {
						pj = 1; 
						pctj = 0;
						//sfx_play (7, 0);
						pvy = -PLAYER_VY_JUMP_INITIAL;
					}

					enems_kill ();
					continue;
				} else if (en_t [gpit] != 9 || en_mx [gpit] == 2) {
					kill_player ();
				}
			}
		} else {
			oam_meta_spr (0, 240, OAM_ENEMS + (gpit << 4), spr_empty);
		}
	}	
}
