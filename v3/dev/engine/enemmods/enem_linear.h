// MT MK2 NES v0.8y - Yun Edition
// Copyleft 2017 by The Mojon Twins

// Enem. type linear

	if (!en_washit [gpit]) if (!_en_state || half_life) {
#ifdef LINEAR_COLLIDES		
		rdx = _en_x;
#endif
		_en_x += _en_mx;

#ifdef LINEAR_COLLIDES		
		if (_en_mx) {
			cy1 = _en_y >> 4; 
			cy2 = (_en_y + 15) >> 4;
			if (_en_mx < 0) {
				cx1 = cx2 = _en_x >> 4;
			} else {
				cx1 = cx2 = (_en_x + 15) >> 4;
			}
			cm_two_points ();
#ifdef LINEAR_COLLIDE_EVERYTHING
			if (at1 + at2)
#else
			if ((at1 & OBSTACLE_BIT) || (at2 & OBSTACLE_BIT))
#endif
			{
				en_collx = 1;
				_en_x = rdx;
				_en_mx = -_en_mx;
			}
		}		
#endif

#ifdef LINEAR_COLLIDES		
		rdy = _en_y;
#endif
		_en_y += _en_my;

#ifdef LINEAR_COLLIDES
		if (_en_my) {
			cx1 = _en_x >> 4;
			cx2 = (_en_x + 15) >> 4;
			if (_en_my < 0) {
				cy1 = cy2 = _en_y >> 4;	
			} else  {
				cy1 = cy2 = (_en_y + 15) >> 4;
			}				
			cm_two_points ();
#ifdef LINEAR_COLLIDE_EVERYTHING
			if (at1 + at2)
#else
			if ((at1 & OBSTACLE_BIT) || (at2 & OBSTACLE_BIT))
#endif
			{
				en_colly = 1;
				_en_y = rdy;
				_en_my = -_en_my;
			}				
		}
#endif

		if (_en_x == _en_x1 || _en_x == _en_x2) _en_mx = -_en_mx;
#ifdef PLAYER_STEPS_ON_ENEMIES
		if (_en_my) {
			if (_en_y <= _en_y1) _en_my = ABS (_en_my);
			if (_en_y >= _en_y2) _en_my = -ABS (_en_my);
		}
#else		
		if (_en_y == _en_y1 || _en_y == _en_y2) _en_my = -_en_my;		
#endif
	}

	spr_id = en_s [gpit] + en_fr + (_en_mx ? ((_en_mx > 0) ? 0 : 2) : ((_en_my > 0) ? 0 : 2));

	// enems_spr ();
