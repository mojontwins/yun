// MT MK2 NES v0.8b
// Copyleft 2017 by The Mojon Twins

// Levelset
// Coment whichever doesn't apply

const unsigned char * const l_ts_pals [] = { ts4_pals, ts0_pals, ts1_pals, ts2_pals, ts3_pals };
const unsigned char * const l_ts_tmaps [] = { ts4_tmaps, ts0_tmaps, ts1_tmaps, ts2_tmaps, ts3_tmaps };
const unsigned char * const l_behs [] = { behs4, behs0, behs1, behs2, behs3 };
const unsigned char l_scr_ini [] = { 9, 20, 20, 23, 12 };
const unsigned char * const * const l_map [] = { map_4, map_0, map_1, map_2, map_3 };
//const unsigned char * const * const l_decos [] = { map_0_decos, map_1_decos, map_2_decos };
const unsigned char * const * const l_enems [] = { enems_4, enems_0, enems_1, enems_2, enems_3 } ;
const unsigned char * const l_hotspots [] = { 0, hotspots_0, hotspots_1, hotspots_2, hotspots_3 };
const unsigned char * const l_locks [] = { 0, map_0_locks, map_1_locks, map_2_locks, map_3_locks };
const unsigned char * const l_pal_bgs [] = { palts4, palts0, palts1, palts2, palts3 };
const unsigned char * const l_pal_fgs [] = { palss2, palss0, palss1, palss2, palss2 };
// const unsigned char * const t_pal_bgs [] = { palts0, palts0 };
// const unsigned char * const t_pal_fgs [] = { palss0, palss0 };
// const unsigned char l_max_hotspots_type_1 [] = { MAX_HOTSPOTS_1_TYPE_1, MAX_HOTSPOTS_1_TYPE_1, MAX_HOTSPOTS_1_TYPE_1 };
const unsigned char l_max_killable_enems [] = { 
	MAX_ENEMS_4_TYPE_10,
	MAX_ENEMS_0_TYPE_10 + MAX_ENEMS_0_TYPE_30 + MAX_ENEMS_0_TYPE_90,
	MAX_ENEMS_1_TYPE_10 + MAX_ENEMS_1_TYPE_30,
	MAX_ENEMS_2_TYPE_10 + MAX_ENEMS_2_TYPE_30 + MAX_ENEMS_2_TYPE_90 + MAX_ENEMS_2_TYPE_A0,
	MAX_ENEMS_3_TYPE_10 + MAX_ENEMS_3_TYPE_30 + MAX_ENEMS_3_TYPE_90 + MAX_ENEMS_3_TYPE_A0
};
const unsigned char l_map_w [] = { 3, 4, 4, 4, 12 };
// const unsigned char l_plife [] = { 5, 5, 5 };
const unsigned char player_ini_x [] = { 2, 2, 2, 13, 2 };
const unsigned char player_ini_y [] = { 2, 6, 9, 5, 6 };
//const unsigned char * const * const l_spr_enems [] = { spr_enems_1, spr_enems_1, spr_enems_1 }; 
// const unsigned char * const * const l_spr_player [] = { spr_player_0, spr_player_0, spr_player_0 };
const unsigned char level_musics [] = { 4, 2, 3, 4, 2 };
