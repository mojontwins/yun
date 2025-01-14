			// Hotspot interaction
			if (hrt) {
				if (collide_in (prx + 8, pry + 8, hrx, hry)) {
					oam_meta_spr (0, 240, OAM_HOTSPOTS, spr_empty);
					switch (hrt) {
						case HOTSPOT_TYPE_KEYS:
							pkeys ++;
							sfx_play (2, 1);
							break;
						case HOTSPOT_TYPE_REFILL:
							plife += PLAYER_REFILL;
							if (plife > PLAYER_LIFE) plife = PLAYER_LIFE;
							sfx_play (3, 1);
							break;
					}
					hry = 240;
					hact [n_pant] = 0;
				}
			}
			