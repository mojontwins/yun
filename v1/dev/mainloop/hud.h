			// Update frame
			if (okilled != pkilled) {
				okilled = pkilled;
				p_t (KILLED_X, KILLED_Y, baddies_count - pkilled);
			}
			if (okeys != pkeys) {
				okeys = pkeys;
				//p_t (KEYS_X, KEYS_Y, pkeys);
				gp_addr = (KEYS_Y << 5) + KEYS_X + 0x2000;
				update_list_write (pkeys + 1);
			}
			if (olife != plife) {
				olife = plife;
				//p_t (LIFE_X, LIFE_Y, plife);
				gp_addr = (LIFE_Y << 5) + LIFE_X + 0x2000;
				update_list_write (plife + 1);
			}
			