	if (en_ud [gpit]) {
		enems_jitter_spr ();
		spr_id = 48 + 6;
	} else {
		// Modify v
		if (!half_life) {
			rda = game_mode == GM_LIMITE ? FANTY_A : FANTY_A + FANTY_A;
			enf_vx [gpit] = saturate (enf_vx [gpit] + add_sign (prx - en_x [gpit], rda), FANTY_MAXV);
			enf_vy [gpit] = saturate (enf_vy [gpit] + add_sign (pry - 16 - en_y [gpit], rda), FANTY_MAXV);
		}

		// Modify s + collide
		en_y [gpit] = enf_y [gpit] >> 6; // Needed?

		// Horizontal
		enf_x [gpit] += enf_vx [gpit]; 
		enf_y [gpit] += enf_vy [gpit]; 

		if (!half_life) {
			if (enf_x [gpit] < 256) enf_x [gpit] = 256;
			if (enf_x [gpit] > 15360) enf_x [gpit] = 15360;
			
			if (enf_y [gpit] < 256) enf_y [gpit] = 256;
			if (enf_y [gpit] > 11264) enf_y [gpit] = 11264;
		}

		en_x [gpit] = enf_x [gpit] >> 6;
		en_y [gpit] = enf_y [gpit] >> 6;

		// Draw
		enems_spr ();
		spr_id = FANTY_BASE_SPRID + ((en_x [gpit] >> 3) & 1) + ((en_x [gpit] > prx) ? 0 : 2);
	}
