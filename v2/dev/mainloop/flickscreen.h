			// Change screen
			if (px < 0) {
				n_pant --;
				prx = 240; px = prx << 6;
			} else if (px > 240 * 64) {
				n_pant ++;
				prx = 0; px = prx >> 6;
			} else if (py < 0) {		// Does this really work?
				if (n_pant >= MAP_W) {
					n_pant -= MAP_W;
					py = 176 * 64;
					pvy = -PLAYER_VY_JUMP_MAX;
				}
			} else if (pry >= 176 && (pvy > 0)) {
				n_pant += MAP_W;
				py = 0;
			}
