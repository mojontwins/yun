mus_cuts_module:
	.word @chn0,@chn1,@chn2,@chn3,@chn4,music_instruments
	.byte $06

@chn0:
@chn0_0:
	.byte $46,$17,$80,$18,$80,$17,$80,$18,$80,$17,$80,$18,$80,$17,$80,$18
	.byte $80,$1b,$80,$1c,$80,$1b,$80,$1c,$80,$1b,$80,$1c,$80,$1b,$80,$1c
	.byte $80,$18,$8d,$3f,$80
@chn0_loop:
@chn0_1:
	.byte $b0
	.byte $fe
	.word @chn0_loop

@chn1:
@chn1_0:
	.byte $41,$18,$86,$17,$86,$1c,$86,$1b,$86,$46,$1b,$8d,$3f,$80
@chn1_loop:
@chn1_1:
	.byte $b0
	.byte $fe
	.word @chn1_loop

@chn2:
@chn2_0:
	.byte $41,$24,$80,$3f,$80,$24,$80,$3f,$80,$18,$82,$3f,$80,$18,$80,$28
	.byte $80,$3f,$80,$28,$80,$3f,$80,$1b,$82,$3f,$82,$46,$1f,$8d,$3f,$80
@chn2_loop:
@chn2_1:
	.byte $b0
	.byte $fe
	.word @chn2_loop

@chn3:
@chn3_0:
	.byte $44,$01,$80,$45,$0f,$80,$0f,$80,$0f,$80,$43,$06,$80,$45,$0f,$80
	.byte $0f,$80,$44,$01,$80,$01,$80,$45,$0f,$80,$0f,$80,$0f,$80,$43,$06
	.byte $80,$45,$0f,$80,$0f,$80,$0f,$91
@chn3_loop:
@chn3_1:
	.byte $b0
	.byte $fe
	.word @chn3_loop

@chn4:
@chn4_0:
	.byte $b0
@chn4_loop:
@chn4_1:
	.byte $b0
	.byte $fe
	.word @chn4_loop
