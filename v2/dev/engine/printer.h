// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// printer.h
// Draw map, print text, etcetera.

void fade_out (void) { fader = 5; while (fader --) { pal_bright (fader); ppu_waitnmi (); } }
	
void fade_in (void) { fader = 5; while (fader --) { pal_bright (4 - fader); ppu_waitnmi (); } }
	
void cls (void) { vram_adr(0x2000); vram_fill(255,0x400); vram_adr(0x2c00); vram_fill(255,0x400); }

const unsigned char bitmasks [] = {0xfc, 0xf3, 0xcf, 0x3f};
unsigned char attr_table [64];

void write_attr (void) {
	rdc = (rdx >> 2) + ((rdy >> 2) << 3);
	rdb = ((rdx >> 1) & 1) + (((rdy >> 1) & 1) << 1);
	rda = attr_table [rdc];
	rda = (rda & bitmasks [rdb]) | (tileset_pals [rdt] << (rdb << 1));
	attr_table [rdc] = rda;
}

void update_list_write (unsigned char a) {
	*ul ++ = MSB(gp_addr);
	*ul ++ = LSB(gp_addr++);
	*ul ++ = a;
}

void draw_tile (void) {
	write_attr ();
	
	gp_tmap = tsmap + (rdt << 2);
	gp_addr = ((rdy << 5) + rdx + 0x2000);
	vram_adr (gp_addr++);
	vram_put (*gp_tmap++);
	vram_put (*gp_tmap++);
	gp_addr += 31;
	vram_adr (gp_addr++);
	vram_put (*gp_tmap++);
	vram_put (*gp_tmap);	
}

void draw_tile_advance (void) {
	draw_tile (); rdx = (rdx + 2) & 31; if (!rdx) rdy += 2;
}

void update_list_tile () {
	write_attr ();
	
	gp_addr = 0x23c0 + rdc;
	update_list_write (rda);
	
	// tiles
	gp_tmap = tsmap + (rdt << 2);
	gp_addr = ((rdy << 5) + rdx + 0x2000);
	update_list_write (*gp_tmap ++);
	update_list_write (*gp_tmap ++);
	gp_addr += 30;
	update_list_write (*gp_tmap ++);
	update_list_write (*gp_tmap);
}

void p_t (unsigned char x, unsigned char y, unsigned char n) {
	gp_addr = (y << 5) + x + 0x2000;
	update_list_write ((n / 10) + 1);
	update_list_write ((n % 10) + 1);
}

void draw_scr (void) {
	// Draw current screen
	set_rand (n_pant);

	gp_gen = (unsigned char *) (c_map + (n_pant << 6) + (n_pant << 5)); rdx = 0; rdy = TOP_ADJUST;
	this_screen_base = gp_gen;
	
	for (rdit = 0; rdit < 192; rdit ++) {
		if ((rdit & 1) == 0) {
			rdt = (*gp_gen) >> 4;
		} else {
			rdt = (*gp_gen) & 15; gp_gen ++;
		}
		
		rdt += tmap_level_offset;

		//map_buff [rdit] = rdt;		
		map_attr [rdit] = tbehs [rdt];		

		if (rdt == tmap_level_offset && (rand8 () & 15) == 1) rdt = tmap_level_altbg;	// ALT BG
		
		draw_tile_advance ();
	}

	// Clear open locks
	gpit = c_max_bolts; while (gpit --) {
		if (n_pant == lknp [gpit]) {
			if (!lkact [gpit]) {
				map_attr [lkyx [gpit]] = 0;
				rdt = 0; rdx = (lkyx [gpit] & 0x0f) << 1; rdy = TOP_ADJUST + ((lkyx [gpit] & 0xf0) >> 3);
				draw_tile ();
			}
		}
	}	
}

void pr_str (unsigned char x, unsigned char y, const unsigned char *s) {
	vram_adr ((y << 5) + x + 0x2000);
	while ((gpit = *s++) != 0xff) vram_put (gpit);
}

void un_rle_screen (unsigned char *rle) {
	rdx = 0; rdy = 0; 
	gpit = 240;
	while (gpit) {
		rdt = (*rle);
		rle ++;
		if (rdt & 128) {
			gpjt = rdt & 127;
			rdt = (*rle);
			rle ++;
			while (gpjt --) {
				draw_tile_advance ();
				gpit --;
			}
		} else {
			draw_tile_advance ();
			gpit --;
		}
	}

	vram_write (rle, 0x23c0, 64);
}
