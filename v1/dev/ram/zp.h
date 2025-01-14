// Push to zero page:
#pragma bssseg (push,"ZEROPAGE")
#pragma dataseg(push,"ZEROPAGE")

unsigned char tmap_level_offset;
unsigned char tmap_level_altbg;
unsigned char base_for_sprites;

unsigned char i, gpit, gpjt, gpaux;
signed char fader;
unsigned char half_life, frame_counter;

unsigned char n_pant, on_pant;

unsigned char *gp_gen, *gp_tmap, *this_screen_base;
unsigned int gp_addr;
unsigned char rdx, rdy, rdt, rdit;
unsigned char rda, rdb, rdc, rdct;
signed int rds16;

unsigned char at1, at2;

// Enemies
unsigned char en_x [3], en_y [3];
unsigned char en_x1 [3], en_y1 [3];
unsigned char en_x2 [3], en_y2 [3];
signed char en_mx [3], en_my [3];
unsigned char en_t [3], en_s [3], en_facing;
unsigned char en_status [3], en_ct [3];
unsigned char en_fr, etx1, etx2, ety1, ety2;
unsigned char en_collx, en_colly;
unsigned char touched;
unsigned char en_touched [3], en_cttouched [3];
#ifdef ENABLE_FANTY
signed int enf_x [3], enf_y [3], enf_vx [3], enf_vy [3];
#endif
unsigned char en_ud [3];

// Main player
signed int px, py, pvx, pvy;
unsigned char pfacing, pfr, pctfr, psprid;
unsigned char pj, pctj, pjb, pgotten, ppossee, psprint;
unsigned char pobjs, plife, pcontinues, pkeys, pkilled;
unsigned char pstate, pctstate;
signed int pgtmx, pgtmy;
unsigned char pfiring, pice, pconveyor, pconvd1, pconvd2;

// Aux player
unsigned char prx, pry, ptx1, ptx2, pty1, pty2;
unsigned char pfacingv, pfacingh;
#ifdef ENABLE_PROPELLERS
unsigned char ppropelled;
#endif

// Bullets
#ifdef PLAYER_CAN_FIRE
unsigned char bst [MAX_BULLETS], bx [MAX_BULLETS], by [MAX_BULLETS], bmx [MAX_BULLETS], bmy [MAX_BULLETS];
unsigned char btx, bty;
#endif

// Hotspots
unsigned char hrx, hry, hrt;

// Process breakable?
#ifdef BREAKABLE_ANIM
unsigned char do_process_breakable;
#endif

unsigned char ft;

// Gfx sets
//char **spr_enems, **spr_player;

// Level control

// Current level
unsigned char *c_map;
unsigned char **c_decos;
unsigned char *c_locks;
unsigned char *c_enems;
unsigned char *c_hotspots;
unsigned char *c_pal_bg;
unsigned char *c_pal_fg;

unsigned char *tileset_pals;
unsigned char *tsmap;

// NO!
unsigned char no_on, no_ct;

// Save code
unsigned char spr_x, spr_y, spr_id;
