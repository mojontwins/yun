			// Change screen
			if (prx == 0 && pvx < 0) {
				n_pant --;
				px = 240 * 64;
			} else if (prx >= 240 && pvx > 0) {
				n_pant ++;
				px = 0;
			} else if (py < 0) {		// Does this really work?
				if (n_pant >= MAP_W) {
					n_pant -= MAP_W;
					py = 176 * 64;
				}
			} else if (pry >= 176 && (pvy > 0)) {
				n_pant += MAP_W;
				py = 0;
			}
