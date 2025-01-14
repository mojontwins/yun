void simplecoco_init (void) {
	gpit = COCOS_MAX; while (gpit --) {
		coco_flag [gpit] = 0;
		oam_spr (0, 240, 0xff, 0, OAM_COCO_BASE + (gpit << 2));
	}
}

void simplecoco_new () {
	// Create coco @ rdx, rdy
	gpit = COCOS_MAX; while (gpit --) if (!coco_flag [gpit]) {
		// Calculate distance
		rda = delta (prx, rdx); // dx
		rdb = delta (pry, rdy); // dy
		rdc = min (rda, rdb);	// min (dx, dy)
		rdct = rda + rdb - (rdc >> 1) - (rdc >> 2) + (rdc >> 4);
		
		if (rdct > COCO_FAIR_D) {
			// Shoot towards the player.
			coco_x [gpit] = rdx << 6;
			coco_y [gpit] = rdy << 6;

			// Apply formula. Looks awkward but it's optimized for space and shitty compiler
			rds16 = COCO_V * rda / rdct; coco_vx [gpit] = add_sign_2 (px, coco_x [gpit], rds16);
			rds16 = COCO_V * rdb / rdct; coco_vy [gpit] = add_sign_2 (py, coco_y [gpit], rds16);

			coco_flag [gpit] = 1;
		}
		
		break;
	}
}

void simplecoco_do (void) {
	gpit = COCOS_MAX; while (gpit --) if (coco_flag [gpit]) {
		// Move
		coco_x [gpit] += coco_vx [gpit];
		coco_y [gpit] += coco_vy [gpit];

		// Out of bounds
		if (coco_x [gpit] < 0 || coco_x [gpit] > 256<<6 || coco_y [gpit] < 0 || coco_y [gpit] > 192<<6) {
			coco_flag [gpit] = 0; break;
		}

		rdx = coco_x [gpit] >> 6;
		rdy = coco_y [gpit] >> 6;

		// Render
		oam_spr (rdx, rdy + SPRITE_ADJUST, COCO_PATTERN, 0, OAM_COCO_BASE + (gpit << 2));

		// Collide w/player
		if (rdx >= prx + 1 && rdx <= prx + 7 && rdy + 7 >= pry && rdy <= pry + 12) {
			kill_player ();
			coco_flag [gpit] = 0; 
		}
	} else {
		oam_spr (0, 240, 0xff, 0, OAM_COCO_BASE + (gpit << 2));
	}
}
