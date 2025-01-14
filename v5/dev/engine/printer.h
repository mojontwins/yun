// MT MK2 NES v0.8y - Yun Edition
// Copyleft 2017 by The Mojon Twins

// General printing functions

void fade_out (void) { fader = 5; while (fader --) { pal_bright (fader); ppu_wait_nmi (); } }
	
void fade_in (void) { fader = 5; while (fader --) { pal_bright (4 - fader); ppu_wait_nmi (); } }
	
void cls (void) { vram_adr (0x2000); vram_fill (0x00,0x400); }

void reset_attributes (void) {

	gpit = 64; while (gpit --) attr_table [gpit] = 0xff;
}

void show_attributes (void) {
	vram_adr (NAMETABLE_A + 0x03c0);
	// CUSTOM {
	//vram_write (attr_table, 64);
	vram_write (attr_table, 48);
	// } END_OF_CUSTOM;
}

void close_update_cycle (void) {
	*ul = NT_UPD_EOF; ppu_wait_nmi ();
}

void write_attr (void) {
	rdc = (rdx >> 2) + ((rdy >> 2) << 3);
	rdb = ((rdx >> 1) & 1) + (((rdy >> 1) & 1) << 1);
	rda = attr_table [rdc];
	rda = (rda & bitmasks [rdb]) | (c_ts_pals [rdt] << (rdb << 1));
	attr_table [rdc] = rda;
}

void update_list_write (void) {
	*ul ++ = MSB(gp_addr);
	*ul ++ = LSB(gp_addr++);
	*ul ++ = ulw;
}

void draw_tile (void) {
#ifdef MAP_DONT_PAINT_TILE_0
	if (!rdt) return;
#endif

	write_attr ();
	
	gp_tmap = (unsigned char *) c_ts_tmaps + (rdt << 2);
	gp_addr = ((rdy << 5) + rdx + 0x2000);

#ifdef MAP_ENABLE_AUTOSHADOWS
	if (mapmode_autoshadows && !scr_attr [gpit]) {
		vram_adr (gp_addr++);
		vram_put (*(((scr_attr [gpit - 17] & 8) ? 64 : 0) + gp_tmap));
		gp_tmap ++;
		vram_put (*(((scr_attr [gpit - 16] & 8) ? 64 : 0) + gp_tmap));
		gp_tmap ++;
		gp_addr += 31;
		vram_adr (gp_addr++);
		vram_put (*(((scr_attr [gpit - 1] & 8) ? 64 : 0) + gp_tmap));
		gp_tmap ++;
		vram_put (*gp_tmap);
	} else 
#endif
	{
		vram_adr (gp_addr++);
		vram_put (*gp_tmap++);
		vram_put (*gp_tmap++);
		gp_addr += 31;
		vram_adr (gp_addr++);
		vram_put (*gp_tmap++);
		vram_put (*gp_tmap);	
	}
}

void draw_tile_advance (void) {
	draw_tile (); rdx = (rdx + 2) & 31; if (!rdx) rdy += 2;
}

void update_list_horz_2 (void) {
	*ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
	*ul ++ = LSB (gp_addr);
	*ul ++ = 2;	
	*ul ++ = *gp_tmap ++;
	*ul ++ = *gp_tmap ++;
}

void update_list_tile (void) {
	write_attr ();
	
	gp_addr = 0x23c0 + rdc;
	ulw = rda; update_list_write ();
	
	// tiles
	gp_tmap = (unsigned char *) c_ts_tmaps + (rdt << 2);
	gp_addr = ((rdy << 5) + rdx + NAMETABLE_A);
	update_list_horz_2 ();
	
	gp_addr += 32;
	update_list_horz_2 ();
	
}

void set_map_tile (unsigned char x, unsigned char y, unsigned char t) {
	rdx = x + x; rdy = y + y + TOP_ADJUST; rdt = t;
	scr_buff [x + (y << 4)] = rdt; scr_attr [x + (y << 4)] = c_behs [rdt];
	update_list_tile ();
}

void p_t2 (unsigned char x, unsigned char y, unsigned char n) {
	gp_addr = NAMETABLE_A + (y << 5) + x;
	*ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
	*ul ++ = LSB (gp_addr);
	*ul ++ = 2;	
	*ul ++ = DIGIT ((n / 10));
	*ul ++ = DIGIT ((n % 10));
}

void advance_worm (void) {

#ifdef CREATE_STUFF_FROM_MAP
	switch (rdt) {
#ifdef PROPELLERS_CREATE_FROM_MAP
		case PROPELLERS_CREATE_FROM_MAP: 
			propellers_add ();
			break;
#endif
#ifdef SPRINGS_CREATE_FROM_MAP
		case SPRINGS_CREATE_FROM_MAP:
			springs_add ();
			break;
#endif
	}
#endif

#ifdef MAP_USE_ALT_TILE
	rdd = rdt;
	if (rdt == 0 && ALT_TILE_EXPRESSION) rdt = MAP_USE_ALT_TILE;
	scr_buff [gpit] = rdt; scr_attr [gpit] = c_behs [rdt]; draw_tile_advance (); gpit ++;
	rdt = rdd;
#else
	scr_buff [gpit] = rdt; scr_attr [gpit] = c_behs [rdt]; draw_tile_advance (); gpit ++;
#endif
}

#ifdef MAP_CHR_ROM
	unsigned char read_ppu_data (void) {
		return *((unsigned char *) (0x2007));
	}
#endif

void draw_scr (void) {
	// Draw current screen
	set_rand (1 + n_pant);

#ifdef ENABLE_TOUCHPLATES
	gpit = 32; while (gpit --) bolt_lives [gpit] = 0;
#endif

#ifdef MAP_CHR_ROM

	// This time c_map is an integer which contains
	// a base address in CHR-ROM (this is, the PPU address space)
	// c_chr_rom stores the current level's CHR-ROM page.

	bankswitch (c_chr_rom);

	#ifdef MAP_FORMAT_PACKED
	
		// First of all copy stuff 

		gpint = c_map + (n_pant << 6) + (n_pant << 5);
		vram_adr (gpint);
		vram_read (scr_buff + 96, 96);

		gp_map = scr_buff + 96;
		gpit = 0; rdx = 0; rdy = TOP_ADJUST;

		while (gpit < 192) {
			rdct = *gp_map ++;
			rdt = rdct >> 4; advance_worm ();
			rdt = rdct & 15; advance_worm ();
		}

	#endif

	#ifdef MAP_FORMAT_RLE44
		vram_adr (c_map [n_pant]);
		rda = read_ppu_data (); 	// Dummy read.
		
		// UNRLE into scr_buff
		gpit = 0; while (gpit < 192) {
			rdt = read_ppu_data ();
			rdct = 1 + (rdt >> 4);
			rdt &= 0x0f;
			while (rdct --) scr_buff [gpit ++] = rdt;
		}

		// Now render
		gpit = 0; rdx = 0; rdy = TOP_ADJUST;
		while (gpit < 192) {
			rdt = scr_buff [gpit]; advance_worm ();
		}
	#endif

	#ifdef MAP_FORMAT_RLE53
		vram_adr (c_map [n_pant]);
		rda = read_ppu_data (); 	// Dummy read.
		
		// UNRLE into scr_buff
		gpit = 0; while (gpit < 192) {
			rdt = read_ppu_data ();
			rdct = 1 + (rdt >> 5);
			rdt &= 0x1f;
			while (rdct --) scr_buff [gpit ++] = rdt;
		}

		// Now render
		gpit = 0; rdx = 0; rdy = TOP_ADJUST;
		while (gpit < 192) {
			rdt = scr_buff [gpit]; advance_worm ();
		}
	#endif

	// Decos are in CHR-ROM as well and are indexed 
	// This time we custom-access VRAM.
	// c_decos is pointing to the current decos index,
	// which is an array of integer PPU addresses.

	#ifdef MAP_WITH_DECORATIONS

		if (c_decos && (gpint = c_decos [n_pant])) {
			vram_adr (gpint);
			rda = read_ppu_data (); 	// Dummy read.

			gp_gen = decos_buffer;
			while (rda = read_ppu_data ()) *gp_gen ++ = rda;
			*gp_gen = 0;

			gp_gen = decos_buffer;
			while (rdt = *gp_gen ++) {
				if (rdt & 0x80) {
					rdt &= 0x7F;
					rdct = 1;
				} else {
					rdct = *gp_gen ++;
				}
				while (rdct --) {
					gpit = *gp_gen ++;
					rdy = TOP_ADJUST + ((gpit >> 4) << 1); rdx = (gpit & 15) << 1; 
					advance_worm ();
				}
			}
		}
	#endif 

	bankswitch (cur_bank);

#else

	#ifdef PERSISTENT_TILE_GET
		tile_got_offset = (n_pant << 3) | (n_pant << 2);
	#endif

	#ifdef MAP_FORMAT_RLE53
		gp_map = (unsigned char *) c_map [n_pant];
		gpit = 0; rdx = 0; rdy = TOP_ADJUST;
		while (gpit < 192) {
			rdt = *gp_map ++;
			rdct = 1 + (rdt >> 5);
			rdt &= 0x1f;
			while (rdct --) advance_worm ();
		}
	#endif

	#ifdef MAP_FORMAT_RLE44
		gp_map = (unsigned char *) c_map [n_pant];
		gpit = 0; rdx = 0; rdy = TOP_ADJUST;
		while (gpit < 192) {
			rdt = *gp_map ++;
			rdct = 1 + (rdt >> 4);
			rdt &= 0x0f;
			while (rdct --) advance_worm ();
		}
	#endif

	#ifdef MAP_FORMAT_BYTE_RLE
		gp_map = (unsigned char *) c_map [n_pant];
		gpit = 0; rdx = 0; rdy = TOP_ADJUST;
		while (gpit < 192) {
			rdt = *gp_map ++;
			if (rdt & 128) {
				rdt &= 127;
				rdct = *gp_map ++; while (rdct --) advance_worm ();
			} else advance_worm ();
		}
	#endif

	#ifdef MAP_FORMAT_PACKED
		// n_pant * 96 = n_pant * 64 + n_pant * 32
		gp_map = (unsigned char *) c_map + (n_pant << 6) + (n_pant << 5);
		gpit = 0; rdx = 0; rdy = TOP_ADJUST;
		while (gpit < 192) {
			rdct = *gp_map ++;
			rdt = rdct >> 4; advance_worm ();
			rdt = rdct & 15; advance_worm ();
		}
	#endif	

	#ifdef MAP_WITH_DECORATIONS
		if (c_decos && c_decos [n_pant]) {
			gp_gen = (unsigned char *) c_decos [n_pant];

			while (rdt = *gp_gen ++) {
				if (rdt & 0x80) {
					rdt &= 0x7F;
					rdct = 1;
				} else {
					rdct = *gp_gen ++;
				}
				while (rdct --) {
					gpit = *gp_gen ++;
					rdy = TOP_ADJUST + ((gpit >> 4) << 1); rdx = (gpit & 15) << 1; 
					advance_worm ();
				}
			}
		}
	#endif 
#endif
}

#ifdef PRINT_PSEUDOASCII
void p_s (unsigned char x, unsigned char y, const unsigned char *s) {
	vram_adr (NAMETABLE_A + (y << 5) + x);
	while (rda = *s ++) {
		if (rda == '/') {
			y ++; vram_adr (NAMETABLE_A + (y << 5) + x);
		} else vram_put (rda - 32);
	}
}
#elif defined (PRINT_CUSTOM)
void p_s (unsigned char x, unsigned char y, const unsigned char *s) {
	vram_adr (NAMETABLE_A + (y << 5) + x);
	while ((rda = *s ++) != 0xff) {
		vram_put (rda);
	}
}
#endif

#ifdef PRINT_UL_PRINTER
void p_s_ul (unsigned char x, unsigned char y, const unsigned char *s) {
	gp_gen = (unsigned char *) s; rda = 0; while (*gp_gen ++) rda ++;
	gp_addr = NAMETABLE_A + (y << 5) + x;
	*ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
	*ul ++ = LSB (gp_addr);
	*ul ++ = rda;
	while (rda = *s ++) *ul ++ = (rda - 32);
}
#endif

/*
void un_rle_screen (const unsigned char *rle) {
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

	vram_adr (NAMETABLE_A + 0x03c0);
	vram_write ((unsigned char *) rle, 64);
}
*/
