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
	if (rdb && hact [n_pant]) {
		hrt = rdb;
		hrx = rda & 0xf0; hry = rda << 4;
		oam_meta_spr (hrx, hry + SPRITE_ADJUST, OAM_HOTSPOTS, spr_hs [hrt - 1]);
	} else oam_meta_spr (0, 240, OAM_HOTSPOTS, spr_empty);
}
