			// Skip?
			//if ((i & PAD_A) && (i & PAD_SELECT) && (i & PAD_UP)) {
			if ((i & (PAD_A | PAD_SELECT | PAD_UP)) == (PAD_A | PAD_SELECT | PAD_UP)) baddies_count = 0;
			