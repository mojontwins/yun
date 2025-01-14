// Everything else on normal RAM
#pragma bssseg (push,"BSS")
#pragma dataseg(push,"BSS")

unsigned char map_attr [192];
//unsigned char map_buff [192];

unsigned char hact [MAP_W * MAP_H];

// NBOLTS = max of bolts among leves
#define N_BOLTS 2
unsigned char lkxy [N_BOLTS], lknp [N_BOLTS], lkact [N_BOLTS];

unsigned char olife, okeys, okilled;

// Baddies count. Properly fill this value!
unsigned char baddies_count;

// Persistent enemies
unsigned char ep_x [3 * MAP_W * MAP_H];
unsigned char ep_y [3 * MAP_W * MAP_H];
signed char ep_mx [3 * MAP_W * MAP_H];
signed char ep_my [3 * MAP_W * MAP_H];
unsigned char ep_t [3 * MAP_W * MAP_H];
unsigned int ep_it;

// Persistent deaths
unsigned char ep_flags [3 * MAP_W * MAP_H];

// Die & respawn
unsigned char n_pant_safe;
signed int px_safe, py_safe;

unsigned char level, game_over;
unsigned char c_max_bolts;

// Fabolees
signed int fbl_x [FABOLEES_MAX], fbl_y [FABOLEES_MAX];
signed int fbl_vx [FABOLEES_MAX], fbl_vy [FABOLEES_MAX];
unsigned char fbl_ct [FABOLEES_MAX];
unsigned char fbl_lock_on [FABOLEES_MAX];

// Cocos
signed int coco_x [COCOS_MAX], coco_y [COCOS_MAX];
signed int coco_vx [COCOS_MAX], coco_vy [COCOS_MAX];
unsigned char coco_flag [COCOS_MAX];
