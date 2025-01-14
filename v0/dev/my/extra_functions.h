// MTE MK1_NES / AGNES 0.1 R
// Copyleft Mojon Twins 2013, 2019

// Extra functions. Add here helper functions you need elsewhare (in hooks)

// Custom function
void clear_tile_rdn (void) {
	// Check buffer to substitute tile rdn for c_tsmap [0]
		__asm__ ("lda #0");
		__asm__ ("sta %v", rdx);
		__asm__ ("sta %v", rdy);
		__asm__ ("tax");
	substitute_10_loop:
		__asm__ ("lda %v, x", map_buff);
		__asm__ ("cmp %v", rdn);
		__asm__ ("bne %g", substitute_10_continue);

		__asm__ ("lda %v", rdx);
		__asm__ ("sta %v", _x);
		__asm__ ("lda %v", rdy);
		__asm__ ("sta %v", _y);
		__asm__ ("ldy #0");
		__asm__ ("lda (%v), y", c_tsmap);
		__asm__ ("sta %v", _t);

		__asm__ ("stx %v", rdm);
		map_set ();
		__asm__ ("ldx %v", rdm);

	substitute_10_continue:
		__asm__ ("inc %v", rdx);
		__asm__ ("lda %v", rdx);
		__asm__ ("cmp #16");
		__asm__ ("bne %g", substitute_10_noincy);
		__asm__ ("inc %v", rdy);
		__asm__ ("lda #0");
		__asm__ ("sta %v", rdx);

	substitute_10_noincy:
		__asm__ ("inx");
		__asm__ ("cpx #192");
		__asm__ ("bne %g", substitute_10_loop);
}
