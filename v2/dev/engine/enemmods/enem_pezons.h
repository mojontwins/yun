// All hail the pezons!

// mx is counter, my is max value for counter.

	if (en_ud [gpit]) {
		enems_jitter_spr ();
		spr_id = 62;
	} else {
		switch (en_r [gpit]) {
			case 0:
				if (PEZON_COUNTER [gpit]) {
					PEZON_COUNTER [gpit] --;
				} else {
					PEZON_COUNTER [gpit] = PEZON_COUNT_MAX [gpit];
					en_r [gpit] = 1;
					enf_y [gpit] = en_y1 [gpit] << 6;
					enf_vy [gpit] = -PEZON_THRUST;
				}
				break;
			case 1:
				if (enf_vy [gpit] < PEZON_VY_FALLING_MAX) enf_vy [gpit] += PEZON_G;
				enf_y [gpit] += enf_vy [gpit];
				en_y [gpit] = enf_y [gpit] >> 6;
				if (en_y [gpit] > en_y1 [gpit]) {
					en_y [gpit] = en_y1 [gpit];
					en_r [gpit] = 0;
				}
				break;
		}

		enems_spr ();
		spr_id = 61;
	}
