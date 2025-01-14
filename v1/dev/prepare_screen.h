void prepare_scr (void) {
	if (!ft) fade_out (); else ft = 0;

	fabolee_init ();
	oam_spr (0, 240, 0, 0, 156);
	oam_meta_spr (0, 240, 160, spr_empty);

	persistent_update ();
	enems_load ();
	simplecoco_init ();

	ppu_off ();

	draw_scr ();
	hotspots_create ();
	vram_write (attr_table, 0x23c0, 64);

	// Place sprites 
	enems_move ();
	player_move ();
	render_player ();

	ppu_on_all ();
	ppu_waitnmi ();
	fade_in ();
}
