// This is ugly. Some code reorganization is due
// But not now.

void player_reset_movement (void);
void player_register_safe_spot (void);
void player_restore_safe_spot (void);
void containers_add (void);
void containers_draw (void);
void game_run_fire_script (void);
void enems_drain (void);
void enems_restore_vals (void);
void enems_local_copy (void);

#ifdef ENABLE_PROPELLERS
void propellers_add (void);
#endif

#ifdef ENABLE_SPRINGS
void springs_add (void);
#endif