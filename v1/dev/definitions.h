// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// definitions.h
// Main definitions

#define EST_NORMAL 		0
#define EST_PARP 		2
#define EST_MUR 		4
#define sgni(n)			(((n)) < 0 ? -1 : 1)
#define sgnc(a,b,c)		((a) < (b) ? -(c) : (c))
#define saturate_z(n)	((n) < 0 ? 0 : (n))
#define abs(n)			((n) < 0 ? -(n) : (n))
#define delta(a,b)		((a) < (b) ? (b) - (a) : (a) - (b))
#define s_delta(a,b)	((a) < (b) ? - ((b) - (a)) : (a) - (b))
#define min(a,b)		((a) < (b) ? (a) : (b))
#define add_sign_2(a,b,c) ((a) >= (b) ? (c) : -(c))

#define OAM_FABOLEE		0
#define OAM_ENEMS		OAM_FABOLEE+4*(3*4)
#define OAM_OCCL 		OAM_ENEMS+4*(3*4)
#define OAM_PLAYER 		OAM_OCCL+4*(3*4)
#define OAM_HOTSPOTS 	OAM_PLAYER+4*6
#define OAM_NO 			OAM_HOTSPOTS+4*4
#define OAM_COCO_BASE	OAM_NO+4*4

#define CELL_FACING_RIGHT	0
#define CELL_WALK_BASE		1
#define CELL_ASCENDING		5
#define CELL_DESCENDING		6
#define CELL_FACING_LEFT	7
