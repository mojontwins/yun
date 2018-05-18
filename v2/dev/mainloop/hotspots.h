			// Hotspot interaction
			if (hrt && hrt != HOTSPOT_TYPE_PROPELLER) {
				//if (collide_in (prx + 8, pry + 8, hrx, hry)) {
				if (collide (prx, pry, hrx, hry)) {
					switch (hrt) {
						case HOTSPOT_TYPE_KEYS:
							pkeys ++;
							break;
						case HOTSPOT_TYPE_REFILL:
							plife += PLAYER_REFILL;
							if (plife > PLAYER_LIFE) plife = PLAYER_LIFE;
							break;
						case HOTSPOT_TYPE_OBJECT:
							pobjs --;
							break;
					}
					sfx_play (2, 1);
					hry = 240;
					hact [n_pant] = 0;
				}
			}
			