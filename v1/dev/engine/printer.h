// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// printer.h
// Draw map, print text, etcetera.

void fade_out (void) { fader = 5; while (fader --) { pal_bright (fader); ppu_waitnmi (); } }
	
void fade_in (void) { fader = 5; while (fader --) { pal_bright (4 - fader); ppu_waitnmi (); } }
	
void clear_update_list (void) { i = UPDATE_LIST_SIZE * 3; while ( i -- ) update_list [i] = 0; }
	
void cls (void) { vram_adr(0x2000); vram_fill(255,0x400); }

const unsigned char bitmasks [] = {0xfc, 0xf3, 0xcf, 0x3f};
unsigned char attr_table [64];

void write_attr (unsigned char x, unsigned char y, unsigned char tl) {
	rdc = (x >> 2) + ((y >> 2) << 3);
	rdb = ((x >> 1) & 1) + (((y >> 1) & 1) << 1);
	rda = attr_table [rdc];
	rda = (rda & bitmasks [rdb]) | (tileset_pals [tl] << (rdb << 1));
	attr_table [rdc] = rda;
}

void update_list_write (unsigned char a) {
	update_list [update_index++] = MSB(gp_addr);
	update_list [update_index++] = LSB(gp_addr++);
	update_list [update_index++] = a;
}

void draw_tile (unsigned char x, unsigned char y, unsigned char tl) {
	write_attr (x, y, tl);
	
	gp_tmap = tsmap + (tl << 2);
	gp_addr = ((y<<5) + x + 0x2000);
	vram_adr (gp_addr++);
	vram_put (*gp_tmap++);
	vram_put (*gp_tmap++);
	gp_addr += 31;
	vram_adr (gp_addr++);
	vram_put (*gp_tmap++);
	vram_put (*gp_tmap);	
}

void update_list_tile (unsigned char x, unsigned char y, unsigned char tl) {
	write_attr (x, y, tl);
	
	gp_addr = 0x23c0 + rdc;
	update_list_write (rda);
	
	// tiles
	gp_tmap = tsmap + (tl << 2);
	gp_addr = ((y<<5) + x + 0x2000);
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

void draw_game_tile (unsigned char x, unsigned char y, unsigned char t) {
	rdit = x + (y << 4);
	//map_buff [rdit] = t;
	map_attr [rdit] = tbehs [t];
	
	draw_tile (x + x, TOP_ADJUST + y + y, t);
}

void draw_scr (void) {
	// Draw current screen
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
		draw_tile (rdx, rdy, rdt);
		
		rdx = (rdx + 2) & 31; if (!rdx) rdy += 2;
	}

	// Clear open locks
	gpit = c_max_bolts; while (gpit --) {
		if (n_pant == lknp [gpit]) {
			if (!lkact [gpit]) {
				draw_game_tile (lkxy [gpit] >> 4, lkxy [gpit] & 15, 0);
			}
		}
	}	
}

void pr_str (unsigned char x, unsigned char y, const unsigned char *s) {
	vram_adr ((y << 5) + x + 0x2000);
	while ((gpit = *s++) != 0xff) vram_put (gpit);
}

void pr_str_upd (unsigned char x, unsigned char y, const unsigned char *s) {
	gp_addr = (y << 5) + x + 0x2000;
	while ((gpit = *s++) != 0xff) update_list_write (gpit);
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
				draw_tile (rdx, rdy, rdt);
				rdx = (rdx + 2) & 31; if (!rdx) rdy += 2;
				gpit --;
			}
		} else {
			draw_tile (rdx, rdy, rdt);
			rdx = (rdx + 2) & 31; if (!rdx) rdy +=2;
			gpit --;
		}
	}

	vram_write (rle, 0x23c0, 64);
}
