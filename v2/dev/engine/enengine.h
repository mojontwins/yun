// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// enengine.h
// Enemies Engine & stuff

void enems_persistent_load (void) {
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

void enems_persistent_update (void) {
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

void enems_persistent_deaths_load (void) {
	gpit = MAP_W * MAP_H * 3; while (gpit --) ep_flags [gpit] |= 0x01;
}

void enems_init_fp (void) {
	enf_x [gpit] = en_x [gpit] << 6;
	enf_y [gpit] = en_y [gpit] << 6;
	enf_vx [gpit] = enf_vy [gpit] = 0;
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
	n_pant_3 = rdc;

	for (gpit = 0; gpit < 3; gpit ++) {
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
					en_x [gpit] = en_x1 [gpit];		// Always restore
					en_y [gpit] = en_y1 [gpit];
					
					enems_init_fp ();
					break;

				case 8:
					// Pezons
					PEZON_COUNTER [gpit] = PEZON_COUNT_MAX [gpit] = PEZON_WAIT + (rda << 3);
					en_r [gpit] = 0;
					en_y [gpit] = en_y1 [gpit];
					enems_init_fp ();
					break;

				case 9:
					// Monococos
					en_mx [gpit] = 0; en_my [gpit] = MONOCOCO_BASE_TIME_HIDDEN - (rand8 () & 0x15);
			}

			en_cttouched [gpit] = 0;
		}
		rdc ++;
	}
}

void enems_kill (void) {	
	en_cttouched [gpit] = 8;
	sfx_play (6, 2);
	
	en_t [gpit] = 0;
	ep_flags [n_pant_3 + gpit] &= 0xFE;
	
	baddies_count --;

	// Find fabolee(s) locked on to this
	gpjt = FABOLEES_MAX; while (gpjt --) if (fbl_lock_on [gpjt] == gpit) fbl_ct [gpjt] = 0;
}

void enems_jitter_spr (void) {
	spr_x = en_x [gpit] + jitter [frame_counter & 15];
	spr_y = en_y [gpit] + jitter [15 - (frame_counter & 15)];	
}

void enems_spr (void) {
	spr_x = en_x [gpit];
	spr_y = en_y [gpit];
}

void enems_move (void) {
	// Updates sprites
	for (gpit = 0; gpit < 3; gpit ++) {
		if (en_cttouched [gpit]) {
			en_cttouched [gpit] --;
			oam_index = oam_meta_spr (en_x [gpit], en_y [gpit] + SPRITE_ADJUST, oam_index, spr_hs_04);
			continue;
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
				cx1 = (en_x [gpit] + 4) >> 4;
				cx2 = (en_x [gpit] + 11) >> 4;
				cy1 = cy2 = (en_y [gpit] + 15) >> 4;
				cm_two_points ();
				if (at1 + at2) {
					if (en_t [gpit] == 9) {
						enems_kill ();
						continue;
					}
				} else {
					en_y [gpit] ++; 
					enf_y [gpit] = en_y [gpit] << 6; 
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
				case 8:
					#include "engine/enemmods/enem_pezons.h"
					break;
				case 9:
					#include "engine/enemmods/enem_monococo.h"
					break;
			}

			// Paint

			oam_index = oam_meta_spr (
				spr_x, spr_y + SPRITE_ADJUST, 
				oam_index, 
				spr_enems [spr_id]);

			if (en_t [gpit] == 4) {
				if (gpjt && !pgotten && !pj) {
					// Horizontal moving platforms
					if (en_mx [gpit]) {
						if (pry + 16 >= en_y [gpit] && pry + 12 <= en_y [gpit]) {
							pgotten = 1;
							pgtmx = en_mx [gpit] << (6 - en_status [gpit]);
							pry = (en_y [gpit] - 16); py = pry << 6;
						}
					}
					
					// Vertical moving platforms
					if (
						(en_my [gpit] < 0 && pry + 17 >= en_y [gpit] && pry + 12 <= en_y [gpit]) ||
						(en_my [gpit] > 0 && pry + 16 + en_my [gpit] >= en_y [gpit] && pry + 12 <= en_y [gpit])
					) {
						pgotten = 1;
						pgtmy = en_my [gpit] << (6 - en_status [gpit]);
						pry = (en_y [gpit] - 16); py = pry << 6;
						pvy = 0;
					}
				} 
			} else if (collide (prx, pry, en_x [gpit], en_y [gpit])) {
				if (en_ud [gpit]) {
					if (!pad_poll (0) & PAD_B) {
						pvy = -PLAYER_VY_JUMP_INITIAL << 1;
					} else {
						pj = 1; 
						pctj = 0;
						//sfx_play (7, 0);
						pvy = -PLAYER_VY_JUMP_INITIAL;
					}

					if (!en_cttouched [gpit]) enems_kill ();
					continue;
				} else if (en_t [gpit] != 9 || en_mx [gpit] == 2) {
					if (game_mode == GM_LIMITE) enems_kill ();
					if (pstate == EST_NORMAL) pkilled = 1;
				}
			}
		} 
	}	
}
