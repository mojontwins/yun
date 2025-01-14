	if (en_ud [gpit]) {
		spr_x = en_x [gpit] + jitter [frame_counter & 15];
		spr_y = en_y [gpit] + jitter [15 - (frame_counter & 15)];
		spr_id = 48 + 6;
	} else {
		// Modify v
		enf_vx [gpit] = saturate (enf_vx [gpit] + add_sign (prx - en_x [gpit], FANTY_A), FANTY_MAXV);
		enf_vy [gpit] = saturate (enf_vy [gpit] + add_sign (pry - en_y [gpit], FANTY_A), FANTY_MAXV);

		// Modify s + collide
		en_y [gpit] = enf_y [gpit] >> 6; // Needed?

		// Horizontal
		enf_x [gpit] += enf_vx [gpit]; 
		if (enf_x [gpit] < 0) enf_x [gpit] = 0;
		if (enf_x [gpit] > 15360) enf_x [gpit] = 15360;
		en_x [gpit] = enf_x [gpit] >> 6;

#ifdef FANTY_COLLIDES
		if (enf_vx [gpit]) {
			pty1 = (en_y [gpit] + 8) >> 4;
			pty2 = (en_y [gpit] + 15) >> 4;
			if (enf_vx [gpit] > 0) {
				ptx2 = (en_x [gpit] + 11) >> 4;
				if (attr (ptx2, pty1) || attr (ptx2, pty2)) {
					enf_vx [gpit] = -enf_vx [gpit];
					en_x [gpit] = ((ptx2 - 1) << 4) + 4;
					enf_x [gpit] = en_x [gpit] << 6;
				}
			} else {
				ptx1 = (en_x [gpit] + 4) >> 4;
				if (attr (ptx1, pty1) || attr (ptx1, pty2)) {
					enf_vx [gpit] = -enf_vx [gpit];
					en_x [gpit] = ((ptx1 + 1) << 4) - 4;
					enf_x [gpit] = en_x [gpit] << 6;
				}
			}
		}
#endif

		enf_y [gpit] += enf_vy [gpit]; 
		if (enf_y [gpit] < 0) enf_y [gpit] = 0;
		if (enf_y [gpit] > 11264) enf_y [gpit] = 11264;
		en_y [gpit] = enf_y [gpit] >> 6;

#ifdef FANTY_COLLIDES
		if (enf_vy [gpit]) {

			ptx1 = (en_x [gpit] + 4) >> 4;
			ptx2 = (en_x [gpit] + 11) >> 4;
			if (enf_vy [gpit] > 0) {	
				pty2 = (en_y [gpit] + 15) >> 4;
				if (attr (ptx1, pty2) || attr (ptx2, pty2)) {
					enf_vy [gpit] = -enf_vy [gpit];
					en_y [gpit] = ((pty2 - 1) << 4);
					enf_y [gpit] = en_y [gpit] << 6;
				}
			} else {
				pty1 = (en_y [gpit] + 8) >> 4;
				if (attr (ptx1, pty1) || attr (ptx2, pty1)) {
					enf_vy [gpit] = -enf_vy [gpit];
					en_y [gpit] = ((pty1 + 1) << 4) - 8;
					enf_y [gpit] = en_y [gpit] << 6;
				}
			}
		}
#endif

		// Draw
		spr_x = en_x [gpit];
		spr_y = en_y [gpit];
		spr_id = FANTY_BASE_SPRID + ((en_x [gpit] >> 3) & 1) + ((en_x [gpit] > prx) ? 0 : 2);
	}
