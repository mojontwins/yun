void simplecoco_init (void) {
	coco_it = COCOS_MAX; while (coco_it --) {
		coco_flag [coco_it] = 0;
	}
}

void simplecoco_new () {
	// Create coco @ rdx, rdy
	coco_it = COCOS_MAX; while (coco_it --) if (!coco_flag [coco_it]) {
		// Calculate distance
		rda = delta (prx, rdx); // dx
		rdb = delta (pry, rdy); // dy
		rdc = min (rda, rdb);	// min (dx, dy)
		rdct = rda + rdb - (rdc >> 1) - (rdc >> 2) + (rdc >> 4);
		
		if (rdct > COCO_FAIR_D) {
			// Shoot towards the player.
			coco_x [coco_it] = rdx << 6;
			coco_y [coco_it] = rdy << 6;

			// Apply formula. Looks awkward but it's optimized for space and shitty compiler
			rds16 = COCO_V * rda / rdct; coco_vx [coco_it] = add_sign_2 (px, coco_x [coco_it], rds16);
			rds16 = COCO_V * rdb / rdct; coco_vy [coco_it] = add_sign_2 (py, coco_y [coco_it], rds16);

			coco_flag [coco_it] = 1;
		}
		
		break;
	}
}

void simplecoco_do (void) {
	coco_it = COCOS_MAX; while (coco_it --) if (coco_flag [coco_it]) {
		// Move
		coco_x [coco_it] += coco_vx [coco_it];
		coco_y [coco_it] += coco_vy [coco_it];

		// Out of bounds
		if (coco_x [coco_it] < 0 || coco_x [coco_it] > 256<<6 || coco_y [coco_it] < 0 || coco_y [coco_it] > 192<<6) {
			coco_flag [coco_it] = 0; break;
		}

		rdx = coco_x [coco_it] >> 6;
		rdy = coco_y [coco_it] >> 6;

		// Render
		oam_index = oam_spr (rdx, rdy + SPRITE_ADJUST, COCO_PATTERN, 0, oam_index);

		// Collide w/player
		if (pstate == EST_NORMAL && rdx >= prx + 1 && rdx <= prx + 7 && rdy + 7 >= pry && rdy <= pry + 12) {
			pkilled = 1;
			coco_flag [coco_it] = 0; 
		}
	} 
}
