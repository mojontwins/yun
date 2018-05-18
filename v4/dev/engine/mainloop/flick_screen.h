		// Change screen
		// Very basic. Extend when needed.
		if (prx == 4 && pvx < 0) {
// CUSTOM {
			if (level == 4) {
				if (n_pant == 0) n_pant = 11;
				else if (n_pant == 12) n_pant = 23;
				else n_pant --;
			} else 
// } END_OF_CUSTOM 
			n_pant --;
			px = 244 << FIX_BITS;
		} else if (prx == 244 && pvx > 0) {
// CUSTOM {
			if (level == 4) {
				if (n_pant == 11) n_pant = 0;
				else if (n_pant == 23) n_pant = 12;
				else n_pant ++;
			} else 
// } END_OF_CUSTOM 
			n_pant ++;
			px = 8<<FIX_BITS;
		} else if (pry <= 4 && (pvy < 0 || pfaboleed)
#ifdef MAP_CHECK_TOP
			&& n_pant >= map_w
#endif
		) {
			n_pant -= map_w;
			py = 192<<FIX_BITS;
#if defined (PLAYER_JUMPS) || defined (PLAYER_MONONO)
			pvy = -PLAYER_VY_FLICK_TOP;
#endif
		} else if (pry >= 192 && pvy > 0) {
			n_pant += map_w;
			py = 0;
		}

		if (on_pant != n_pant && do_game) {
			prx = px >> FIX_BITS;
			pry = py >> FIX_BITS;
			game_prepare_screen ();
			on_pant = n_pant;
		} 
