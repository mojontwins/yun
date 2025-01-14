// MT MK2 NES v0.8y - Yun Edition
// Copyleft 2017 by The Mojon Twins

// Metaspritesets (in nice arrays)

// Of course, you have to somewhat customize this for every game and make it fit.

// Rock the Kashbah
const unsigned char * const spr_enems_0 [] = {
	// Linear enemies x 7, 6 frames each: r1, r2, l1, l2, ud1, ud2
	
	// Level 0 has those
	ssen0_00_a, ssen0_01_a, ssen0_00_b, ssen0_01_b, ssen0_00_ud, ssen0_01_ud,             // en 0, of 0
	ssen0_02_a, ssen0_03_a, ssen0_02_b, ssen0_03_b, ssen0_02_ud, ssen0_03_ud,             // en 1, of 6

	// Level 1 has those
	ssen1_00, ssen1_01, ssen1_00, ssen1_01, ssen1_00_ud, ssen1_01_ud,                     // en 2, of 12
	ssen2_00_a, ssen2_01_a, ssen2_00_b, ssen2_01_b, ssen2_00_ud, ssen2_01_ud,             // en 3, of 18

	// Level 2 has those
	ssen3_00, ssen3_01, ssen3_00, ssen3_01, ssen3_00_ud, ssen3_01_ud,                     // en 4, of 24
	ssen3_02, ssen3_03, ssen3_02, ssen3_03, ssen3_02_ud, ssen3_03_ud,                     // en 5, of 30
	ssen4_00_a, ssen4_01_a, ssen4_00_b, ssen4_01_b, ssen4_00_ud, ssen4_01_ud,             // en 6, of 36

	// 42: Fanty
	ssenfan_00_a, ssenfan_01_a, ssenfan_00_b, ssenfan_01_b, ssenfan_00_ud, ssenfan_01_ud, // en 7, of 42

	// 48: Monococo: appear 1 2, on 1 2, ud 1,  pad
	ssmisc_09, ssenmc2_00, ssenmc3_00_a, ssenmc3_00_b, ssenmc3_00_ud, ssenmc3_00_ud,      // en 8, of 48

	// 54: Platform a, b
	ssenplat_00, ssenplat_01, ssenplat_00, ssenplat_01, 0, 0,                             // en 9, of 54

	// 60: Zurully
	ssmisc_0A, 0, 0, 0, ssmisc_0A, ssmisc_0A,                                             // en A, of 60

	// 66: Alt monococo
	ssmisc_0E, ssmisc_0F, ssenmc3_00_a, ssenmc3_00_b, ssenmc3_00_ud, ssenmc3_00_ud,       // en B, of 66	

	// 72: Gyrosaw
	ssmisc_0C, ssmisc_0D,

	// 74: Cannon
	ssencannon_00, ssencannon_01, ssencannon_02, ssencannon_03
};

// RIGHT, LEFT x IDLE, W1 W2 W3 W4, UP, DOWN
const unsigned char * const spr_player_0 [] = {
	sspl_00_a,                                   // IDLE
	sspl_01_a, sspl_02_a, sspl_03_a, sspl_04_a,  // WALK
	sspl_05_a,                                   // UP
	sspl_06_a,                                   // FLOAT
	sspl_07_a,                                   // DOWN
	sspl_08_a,                                   // BLOW

	sspl_00_b,                                   // IDLE
	sspl_04_b, sspl_03_b, sspl_02_b, sspl_01_b,  // WALK
	sspl_05_b,                                   // UP
	sspl_06_b,                                   // FLOAT
	sspl_07_b,                                   // DOWN
	sspl_08_b,                                   // BLOW
};

// Items 
const unsigned char * const spr_items [] = {
//	pad      key        heart      light      star
	0,       ssmisc_00, ssmisc_01, ssmisc_02, ssmisc_03,

};

// Fabolees
const unsigned char * const spr_fabolee [] = {
	ssmisc_06, ssmisc_07, ssmisc_08, ssmisc_07,
	ssemfab_00, ssemfab_01, ssemfab_02, ssemfab_03
};

// FUCK

const unsigned char sprplempty [] = {
	-4, -8, 0, 0, 4, -8, 0, 0, 
	-4, 0, 0, 0, 4, 0, 0, 0, 
	-4, 8, 0, 0, 4, 8, 0, 0, 
	0x80
};
