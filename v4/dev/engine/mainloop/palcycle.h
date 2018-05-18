if ((frame_counter & 31) == 0) {
	gpit = pal_cycle [2]; 
	pal_cycle [2] = pal_cycle [1]; 
	pal_cycle [1] = pal_cycle [0]; 
	pal_cycle [0] = gpit; 
	pal_col (1, pal_cycle [0]);
	pal_col (2, pal_cycle [1]);
	pal_col (3, pal_cycle [2]);
}
