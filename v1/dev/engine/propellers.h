#define MAX_PROPELLERS 4

unsigned char prp_idx, prp_it;
unsigned char prp_x [MAX_PROPELLERS], prp_y1 [MAX_PROPELLERS], prp_y2 [MAX_PROPELLERS];

void add_propeller (unsigned char x, unsigned char y) {
	// Has to calculate teh real area.
	prp_it = y - 1; while (prp_it) {
		if (attr (x, prp_it)) break;
		prp_it --;
	}

	// Storage is in pixel coordinates.
	prp_x [prp_idx] = x << 4;
	prp_y1 [prp_idx] = prp_it << 4;
	prp_y2 [prp_idx] = y << 4;
	prp_idx ++;
}

void move_propellers () {
	ppropelled = 0;
	prp_it = prp_idx; while (prp_it --) {
		if (pry >= prp_y1 [prp_it] && pry <= prp_y2 [prp_it]) {
			if (prx + 8 >= prp_x [prp_it] && prx <= prp_x [prp_it] + 7) {
				ppropelled = 1;
			}
		}
		oam_meta_spr (prp_x [prp_it], prp_y2 [prp_it] + SPRITE_ADJUST, 192 + (prp_it << 4), spr_enems [22 + half_life]);
	}
}

void clear_propellers () {
	prp_it = MAX_PROPELLERS; while (prp_it --) {
		oam_meta_spr (0, 240, 192 + (prp_it << 4), spr_empty);
	}
	prp_idx = 0;
}
