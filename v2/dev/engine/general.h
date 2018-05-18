// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// general.h
// General functions, vars & buffers

void cm_two_points (void) {
	// Calculates at1 & at2 from cx1, cy1 & cx2, cy2
	at1 = cy1 > 11 ? 0 : map_attr [cx1 + (cy1 << 4)];
	at2 = cy2 > 11 ? 0 : map_attr [cx2 + (cy2 << 4)];
}

unsigned char qtile (signed char x, signed char y) {
	return (x & 1) ? this_screen_base [(x >> 1) + (y << 3)] & 15 : this_screen_base [(x >> 1) + (y << 3)] >> 4;
}

void map_set (unsigned char x, unsigned char y, unsigned char n) {
	map_attr [x + (y << 4)] = tbehs [n];
	rdx = x + x; rdy = TOP_ADJUST + y + y; rdt = n;
	update_list_tile (); 
}

/*
unsigned char collide_in (x0, y0, x1, y1) {
	return (x0 >= x1 && x0 <= x1 + 15 && y0 >= y1 && y0 <= y1 + 15);	
}
*/

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
	while (ticks --) ppu_waitnmi ();
}
