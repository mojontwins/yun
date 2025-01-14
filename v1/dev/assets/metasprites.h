// metasprites.h
// Metaspriteset.

#include "assets/spr_pl.h"
#include "assets/spr_en.h"
#include "assets/spr_hs.h"
#include "assets/spr_logo.h"

// Extra sprites:

const unsigned char spr_empty [] = {
	0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 128
};

const unsigned char spr_pl_empty [] = {
	0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 128
};

// Special: coverup low priority sprite to cover up saws and other stuff
// (Saws have high priority, but are located further on in the OAM than these)
const char spr_black [] = {
        0x00, 0x00, 0xFF, 0x23, 0x08, 0x00, 0xFF, 0x23,
        0x00, 0x08, 0xFF, 0x23, 0x08, 0x08, 0xFF, 0x23,
        0x80	
};

// spritesets

const char *spr_player [] = {
	spr_pl_00_a, spr_pl_01_a, spr_pl_02_a, spr_pl_03_a, spr_pl_04_a, spr_pl_05_a, spr_pl_06_a,  // Right
	spr_pl_00_b, spr_pl_01_b, spr_pl_02_b, spr_pl_03_b, spr_pl_04_b, spr_pl_05_b, spr_pl_06_b,	// Left
};

const char *spr_enems [] = {
	// L1 L2 R1 R2, en_00->17
	spr_en_00_b, spr_en_01_b, spr_en_00_a, spr_en_01_a,
	spr_en_02_b, spr_en_03_b, spr_en_02_a, spr_en_03_a,
	spr_en_04_b, spr_en_05_b, spr_en_04_a, spr_en_05_a,
	spr_en_06_b, spr_en_07_b, spr_en_06_a, spr_en_07_a,
	spr_en_08_b, spr_en_09_b, spr_en_08_a, spr_en_09_a,
	spr_en_0A_b, spr_en_0B_b, spr_en_0A_a, spr_en_0B_a,
	spr_en_0C_b, spr_en_0D_b, spr_en_0C_a, spr_en_0D_a,
	spr_en_0E_b, spr_en_0F_b, spr_en_0E_a, spr_en_0F_a,
	spr_en_10_b, spr_en_11_b, spr_en_10_a, spr_en_11_a,
	spr_en_12_b, spr_en_13_b, spr_en_12_a, spr_en_13_a,
	spr_en_14_b, spr_en_15_b, spr_en_14_a, spr_en_15_a,
	spr_en_16_b, spr_en_17_b, spr_en_16_a, spr_en_17_a,

	// Upside down, en 00->17 [48 + en_t]
	spr_en_00_ud, 
	spr_en_02_ud, 
	spr_en_04_ud, 
	spr_en_06_ud, 
	spr_en_08_ud, 
	spr_en_0A_ud, 
	spr_en_0C_ud, 
	spr_en_0E_ud, 
	spr_en_10_ud, 
	spr_en_12_ud, 
	spr_en_14_ud, 
	spr_en_16_ud,

	// Hack. Saves code. 60.
	spr_hs_07
};

/*
	0 Key
	1 Life
	2 Explosion
	3 NO!
*/
const char *spr_hs [] = {
	spr_hs_00, spr_hs_01, spr_hs_02, spr_hs_03,
	spr_hs_04, spr_hs_05, spr_hs_06
};
