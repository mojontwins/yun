// Precalculated pezon
// Copyleft 2017 by The Mojon Twins

// Needs PEZON_INCS_MAX, PEZON_INCS_FIRST_FALL and pezon_incs

	// CUSTOM {
	spr_id = PEZONS_BASE_SPRID;
	// } END_OF_CUSTOM

	if (_en_state) {
		_en_y += pezon_incs [_PEZON_INCS_IDX];

		// CUSTOM {
		// spr_id = PEZONS_BASE_SPRID + (_PEZON_INCS_IDX > PEZON_INCS_FIRST_FALL);
		// } END_OF_CUSTOM

		if (_PEZON_INCS_IDX < PEZON_INCS_MAX) {
			_PEZON_INCS_IDX ++; 
		} else {
			_en_state = 0;
			_en_y = _en_y1;
			_PEZON_TIMER = _PEZON_MAX_TIME;
		}
	} else {
		// CUSTOM
		// spr_id = 0xff;
		// } END_OF_CUSTOM

		if (_PEZON_TIMER) _PEZON_TIMER --; else {
			_PEZON_INCS_IDX = 0;
			_en_state = 1;
			_en_y = _en_y1;
		}
	}
	