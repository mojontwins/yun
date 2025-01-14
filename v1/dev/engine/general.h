// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// general.h
// General functions, vars & buffers

unsigned char attr (signed char x, signed char y) {
	if (x < 0 || x > 15 || y < 0 || y > 11) return 0;
	return map_attr [x + (y << 4)];
}

unsigned char qtile (signed char x, signed char y) {
	return (x & 1) ? this_screen_base [(x >> 1) + (y << 3)] & 15 : this_screen_base [(x >> 1) + (y << 3)] >> 4;
}

void map_set (unsigned char x, unsigned char y, unsigned char n) {
	map_attr [x + (y << 4)] = tbehs [n];
	update_list_tile (x + x, TOP_ADJUST + y + y, n); 
}

unsigned char collide_in (x0, y0, x1, y1) {
	return (x0 >= x1 && x0 <= x1 + 15 && y0 >= y1 && y0 <= y1 + 15);	
}

unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	return (x1 + 8 >= x2 && x1 <= x2 + 8 && y1 + 8 >= y2 && y1 <= y2 + 8);
}

signed int add_sign (signed int sign, signed int value) {
	return sign == 0 ? 0 : sign < 0 ? -value : value;
}

signed int saturate (signed int v, signed int max) {
	return v >= 0 ? (v > max ? max : v) : (v < -max ? -max : v);
}

void wait_for (unsigned char ticks) {
	while (pad_poll (0));
	while (ticks --) {
		if (pad_poll (0)) break;
		ppu_waitnmi ();
	}
}
