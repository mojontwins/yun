// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// bolts.h
// Lock management

void bolts_load (void) {
	gp_gen = (unsigned char *) (c_locks);
	gpit = c_max_bolts; while (gpit --) {
		lknp [gpit] = *gp_gen++;
		lkxy [gpit] = *gp_gen++;
		lkact [gpit] = 1;
	}
}

void clear_cerrojo (unsigned char xy) {
	gpit = c_max_bolts; while (gpit --) {
		if (n_pant == lknp [gpit] && xy == lkxy [gpit]) {
			lkact [gpit] = 0;
		}
	}
}
	