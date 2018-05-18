// hotspots.h
// Hotspot management

void hotspots_load (void) {
	// Copies hotspots from ROM to RAM and initializes them
	gp_gen = (unsigned char *) c_hotspots;
	gpit = MAP_W * MAP_H; while (gpit --) hact [gpit] = 1;
}

void hotspots_create (void) {
	hrt = 0;
	gp_gen = (unsigned char *) c_hotspots; gp_gen += (n_pant << 1);
	rdb = *gp_gen ++; rda = *gp_gen;
	if (rdb && rdb < 3 && hact [n_pant] && (game_mode == GM_LIMITE || rdb < 3)) {
		hrt = rdb;
		hry = rda & 0xf0; hrx = rda << 4;

		if (hrt == HOTSPOT_TYPE_PROPELLER) {
			while (!map_attr [rda] && rda < 192) { map_attr [rda] = 128; rda -= 16; }
		}
	} 
}
