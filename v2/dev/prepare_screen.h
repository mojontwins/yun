void prepare_scr (void) {
	if (!ft) fade_out (); else ft = 0;

	no_ct = 0; 

	fabolee_init ();
	
	enems_persistent_update ();
	enems_load ();
	simplecoco_init ();

	ppu_off ();

	draw_scr ();
	hotspots_create ();
	vram_write (attr_table, 0x23c0, 64);

	// Place sprites 
	oam_index = 0;
	enems_move ();
	player_move ();
	player_render ();

	ppu_on_all ();
	oam_hide_rest (oam_index);
	*ul = 0xff;
	ppu_waitnmi ();
	fade_in ();
}
