// metasprites.h
// Metaspriteset.

#include "assets/spr_pl.h"
#include "assets/spr_limite1.h"
#include "assets/spr_limite2.h"
#include "assets/spr_en1.h"
#include "assets/spr_en2.h"
#include "assets/spr_en3.h"
#include "assets/spr_en4.h"
#include "assets/spr_hs.h"
#include "assets/spr_logo.h"

// spritesets

const char * const spr_player [] = {
	spr_pl_00_a, spr_pl_01_a, spr_pl_02_a, spr_pl_03_a, spr_pl_04_a, spr_pl_05_a, spr_pl_06_a,  				// Right
	spr_pl_00_b, spr_pl_01_b, spr_pl_02_b, spr_pl_03_b, spr_pl_04_b, spr_pl_05_b, spr_pl_06_b,					// Left
	spr_lim1_00_a, spr_lim1_01_a, spr_lim1_02_a, spr_lim1_03_a, spr_lim1_04_a, spr_lim1_05_a, spr_lim2_00_a,  	// Right
	spr_lim1_00_b, spr_lim1_01_b, spr_lim1_02_b, spr_lim1_03_b, spr_lim1_04_b, spr_lim1_05_b, spr_lim2_00_b,	// Left
};

const char * const spr_enems [] = {
	// L1 L2 R1 R2, en_00->17
	spr_en1_00_b, spr_en1_01_b, spr_en1_00_a, spr_en1_01_a,
	spr_en1_02_b, spr_en1_03_b, spr_en1_02_a, spr_en1_03_a,
	spr_en1_04_b, spr_en1_05_b, spr_en1_04_a, spr_en1_05_a,
	spr_en1_06_b, spr_en1_07_b, spr_en1_06_a, spr_en1_07_a,
	
	spr_en2_00_b, spr_en2_01_b, spr_en2_00_a, spr_en2_01_a,
	spr_en2_02_b, spr_en2_03_b, spr_en2_02_a, spr_en2_03_a,
	spr_en2_04_b, spr_en2_05_b, spr_en2_04_a, spr_en2_05_a,
	spr_en1_06_b, spr_en1_07_b, spr_en1_06_a, spr_en1_07_a,

	spr_en3_00_b, spr_en3_01_b, spr_en3_00_a, spr_en3_01_a,
	spr_en3_02_b, spr_en3_03_b, spr_en3_02_a, spr_en3_03_a,
	spr_en3_04_b, spr_en3_05_b, spr_en3_04_a, spr_en3_05_a,
	spr_en1_06_b, spr_en1_07_b, spr_en1_06_a, spr_en1_07_a,

	// Upside down, en 00->17 [48 + en_t]
	spr_en1_00_ud, 
	spr_en1_02_ud, 
	spr_en1_04_ud, 
	spr_en1_06_ud, 
	
	spr_en2_00_ud, 
	spr_en2_02_ud, 
	spr_en2_04_ud, 
	spr_en1_06_ud, 
	
	spr_en3_00_ud, 
	spr_en3_02_ud, 
	spr_en3_04_ud, 
	spr_en1_06_ud, 
	
	// Hack. Saves code. 60.
	spr_hs_09,

	// Special: Zurully, Zurully_ud (61, 62)
	spr_en4_00, spr_en4_00_ud
};

/*
	0 Key
	1 Life
	2 Explosion
	3 NO!
*/
const char * const spr_hs [] = {
	spr_hs_00, spr_hs_01, spr_hs_02, spr_hs_03, spr_hs_04, spr_hs_05, spr_hs_06, spr_hs_07, spr_hs_08
};
