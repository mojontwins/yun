// MTE MK1_NES / AGNES 0.1 R
// Copyleft Mojon Twins 2013, 2019

// Hooks for custom stuff (replace scripting)

const unsigned char bits [] = {
	1, 2, 4, 8, 16, 32, 64, 128
};

#define PLAYER_TOUCHES(x,y) (rdx==(x) && rdy==(y))

void entering_game (void) {

}

void entering_level (void) {
	// Clear tile persistence
	vram_adr (MAP_CLEAR_LIST_ADDRESS);
	vram_fill (0, 1024);

}

void flick_screen (void) {
	// Right after flick screen DETECTION.

}

void exiting_screen (void) {
	// This is run when screen is OFF!

}

void entering_screen (void) {
	// This is run when screen is OFF!

	// Generally
	f0 = 0;
}

void press_fire_at_screen (void) {
	// Player_touches
	rdx = (prx + 8) >> 4;
	rdy = (pry + 8) >> 4;
	
	if (firezoned) {
		// Fire zones

	} else {
		// Exceptions

	}

	// Tile below to rdt:
		__asm__ ("lda %v", prx);
		__asm__ ("clc");
		__asm__ ("adc #8");
		__asm__ ("lsr a");
		__asm__ ("lsr a");
		__asm__ ("lsr a");
		__asm__ ("lsr a");
		__asm__ ("sta %v", _x);

		__asm__ ("lda %v", pry);
		__asm__ ("clc");
		__asm__ ("adc #16");
		__asm__ ("sta %v", cy1);

		__asm__ ("and #$f0");
		__asm__ ("ora %v", _x);
		__asm__ ("sta %v", rdi);
		__asm__ ("tax");
		__asm__ ("lda %v, x", map_buff);
		__asm__ ("sta %v", rdt);

		__asm__ ("lda %v", cy1);
		__asm__ ("lsr a");
		__asm__ ("lsr a");
		__asm__ ("lsr a");
		__asm__ ("lsr a");
		__asm__ ("sta %v", _y);

	// Code to activate ray tile and open fences
	if (rdt == TILE_RAY) {

	}

	// Code to activate face tiles and count chain tiles
	if (rdt == TILE_FACE) {

	}
}

void custom_hud (void) {
}

#ifdef ENABLE_BREAKABLE
	void on_tile_break (void) {
		// Tile is @ (_x, _y). You may substitute _t

	}
#endif

#ifdef ENABLE_TILE_GET
	void on_tile_get (void) {
		// Tile is @ (_x, _y), precalc @ rdm.
		// You may substitute _t

	}
#endif

#ifndef DEACTIVATE_OBJECTS
	void on_obj_got (void) {
	
	}
#endif

#ifdef ENEMS_CAN_DIE
	#ifndef FIRE_ON_KILL
		void on_enem_killed (void) {	

		}
	#endif
#endif
