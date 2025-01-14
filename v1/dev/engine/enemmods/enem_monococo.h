// All hail the monococo!

// x1, y1 is where it appears.
// mx is state. my is counter.
#define MONOCOCO_X en_x [gpit]
#define MONOCOCO_Y en_y [gpit]
#define MONOCOCO_COUNTER en_my [gpit]
#define MONOCOCO_STATE en_mx [gpit]

if (en_ud [gpit]) {
	spr_x = MONOCOCO_X + jitter [frame_counter & 15];
	spr_y = MONOCOCO_Y + jitter [15 - (frame_counter & 15)];
	spr_id = 50;
} else {
	// Counter & state change
	MONOCOCO_COUNTER --; if (!MONOCOCO_COUNTER) {
		MONOCOCO_STATE = (MONOCOCO_STATE + 1) & 3; MONOCOCO_COUNTER = monococo_state_times [MONOCOCO_STATE] - (rand8 () & 0x15);
	}

	// Shoot
	if (MONOCOCO_STATE == 2 && MONOCOCO_COUNTER == FIRE_COCO_AT) {
		rdx = MONOCOCO_X + 4; rdy = MONOCOCO_Y + 4; simplecoco_new ();
	}

	// Sprite
	spr_x = MONOCOCO_X;
	spr_y = MONOCOCO_Y;
	spr_id = monococo_metasprite [MONOCOCO_STATE] + ((MONOCOCO_STATE == 2 && ((frame_counter >> 4) & 1)) << 1);
}
