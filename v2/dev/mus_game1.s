mus_game1_module:
	.word @chn0,@chn1,@chn2,@chn3,@chn4,music_instruments
	.byte $0a

@chn0:
@chn0_0:
	.byte $bf
@chn0_loop:
@chn0_1:
	.byte $46,$2d,$30,$34,$49,$30,$34,$4a,$30,$46,$2d,$30,$34,$49,$30,$34
	.byte $4a,$30,$34,$82,$46,$2d,$2f,$34,$49,$2f,$34,$4a,$2f,$46,$2d,$32
	.byte $34,$49,$32,$34,$4a,$32,$34,$82,$46,$2d,$30,$34,$49,$30,$34,$4a
	.byte $30,$46,$2d,$30,$34,$49,$30,$34,$4a,$30,$34,$82,$46,$2d,$2f,$34
	.byte $49,$2f,$34,$4a,$2f,$46,$2d,$32,$34,$49,$32,$34,$4a,$32,$34,$82
@chn0_2:
	.byte $ff,$40
	.word @chn0_1
@chn0_3:
	.byte $46,$2f,$34,$36,$49,$34,$36,$4a,$34,$46,$2f,$34,$37,$49,$34,$37
	.byte $4a,$34,$37,$82,$46,$2d,$31,$34,$49,$31,$34,$4a,$31,$46,$2d,$31
	.byte $36,$49,$31,$36,$4a,$31,$36,$82,$46,$2f,$34,$36,$49,$34,$36,$4a
	.byte $34,$46,$2f,$34,$37,$49,$34,$37,$4a,$34,$37,$82,$46,$2d,$31,$34
	.byte $49,$31,$34,$4a,$31,$46,$2d,$31,$36,$49,$31,$36,$4a,$31,$36,$82
@chn0_4:
	.byte $ff,$40
	.word @chn0_3
@chn0_5:
	.byte $ff,$40
	.word @chn0_1
@chn0_6:
	.byte $ff,$40
	.word @chn0_1
@chn0_7:
	.byte $ff,$40
	.word @chn0_3
@chn0_8:
	.byte $ff,$40
	.word @chn0_3
@chn0_9:
	.byte $46,$2d,$31,$34,$49,$31,$34,$4a,$31,$46,$2d,$31,$36,$49,$31,$36
	.byte $4a,$31,$36,$82,$46,$2a,$2d,$34,$49,$2d,$34,$4a,$2d,$46,$2a,$2d
	.byte $31,$49,$2d,$31,$4a,$2d,$31,$82,$46,$2d,$31,$34,$49,$31,$34,$4a
	.byte $31,$46,$2d,$31,$36,$49,$31,$36,$4a,$31,$36,$82,$46,$2a,$2d,$34
	.byte $49,$2d,$34,$4a,$2d,$46,$2a,$2d,$31,$49,$2d,$31,$4a,$2d,$31,$82
@chn0_10:
	.byte $ff,$40
	.word @chn0_9
@chn0_11:
	.byte $3f,$b6,$46,$21,$49,$21,$4a,$21,$82,$2d,$49,$2d
	.byte $fe
	.word @chn0_loop

@chn1:
@chn1_0:
	.byte $3f,$be
@chn1_loop:
@chn1_1:
	.byte $4b,$21,$9c,$1f,$80,$21,$96,$3f,$84,$1f,$80
@chn1_2:
	.byte $21,$9c,$1f,$80,$21,$96,$3f,$84,$1f,$80
@chn1_3:
	.byte $23,$80,$1c,$82,$23,$80,$1c,$82,$23,$82,$25,$80,$23,$82,$26,$80
	.byte $26,$80,$25,$80,$23,$80,$25,$80,$23,$80,$1c,$82,$23,$80,$1c,$82
	.byte $23,$82,$21,$80,$1f,$82,$1c,$82,$1f,$80,$1c,$80,$1f,$80
@chn1_4:
	.byte $ff,$40
	.word @chn1_3
@chn1_5:
	.byte $ff,$40
	.word @chn1_2
@chn1_6:
	.byte $ff,$40
	.word @chn1_2
@chn1_7:
	.byte $ff,$40
	.word @chn1_3
@chn1_8:
	.byte $ff,$40
	.word @chn1_3
@chn1_9:
	.byte $4c,$21,$80,$1c,$80,$20,$80,$21,$88,$28,$82,$26,$82,$25,$80,$23
	.byte $80,$21,$80,$23,$80,$21,$80,$1c,$80,$20,$80,$21,$88,$28,$82,$26
	.byte $82,$2a,$82,$28,$82
@chn1_10:
	.byte $21,$80,$1c,$80,$20,$80,$21,$88,$28,$82,$26,$82,$25,$80,$23,$80
	.byte $21,$80,$23,$80,$21,$80,$1c,$80,$20,$80,$21,$88,$28,$82,$26,$82
	.byte $2a,$82,$28,$82
@chn1_11:
	.byte $ff,$40
	.word @chn1_1
	.byte $fe
	.word @chn1_loop

@chn2:
@chn2_0:
	.byte $41,$09,$84,$0c,$88,$0b,$84,$0e,$88,$09,$84,$0c,$88,$0b,$84,$0e
	.byte $80,$3f,$86
@chn2_loop:
@chn2_1:
	.byte $ff,$40
	.word @chn2_0
@chn2_2:
	.byte $09,$84,$0c,$88,$0b,$84,$0e,$88,$09,$84,$0c,$88,$0b,$84,$0e,$80
	.byte $3f,$86
@chn2_3:
	.byte $0b,$84,$10,$88,$15,$82,$0d,$80,$09,$86,$15,$80,$0b,$84,$10,$88
	.byte $15,$82,$0d,$80,$09,$86,$15,$80
@chn2_4:
	.byte $ff,$40
	.word @chn2_3
@chn2_5:
	.byte $ff,$40
	.word @chn2_2
@chn2_6:
	.byte $ff,$40
	.word @chn2_2
@chn2_7:
	.byte $ff,$40
	.word @chn2_3
@chn2_8:
	.byte $ff,$40
	.word @chn2_3
@chn2_9:
	.byte $09,$80,$10,$80,$0d,$80,$09,$80,$10,$80,$0d,$80,$09,$82,$06,$80
	.byte $09,$80,$0d,$80,$06,$80,$09,$80,$0d,$80,$10,$80,$12,$80,$09,$80
	.byte $10,$80,$0d,$80,$09,$80,$10,$80,$0d,$80,$09,$82,$06,$80,$09,$80
	.byte $0d,$80,$06,$80,$09,$80,$0d,$80,$10,$80,$12,$80
@chn2_10:
	.byte $ff,$40
	.word @chn2_9
@chn2_11:
	.byte $ff,$40
	.word @chn2_2
	.byte $fe
	.word @chn2_loop

@chn3:
@chn3_0:
	.byte $9f,$44,$00,$45,$07,$44,$00,$45,$05,$43,$04,$45,$05,$44,$00,$43
	.byte $02,$44,$00,$43,$02,$44,$00,$45,$04,$43,$00,$45,$07,$09,$0b,$44
	.byte $00,$45,$07,$44,$00,$45,$05,$43,$04,$45,$05,$44,$00,$43,$02,$44
	.byte $00,$43,$02,$44,$00,$45,$04,$43,$00,$45,$07,$09,$0b
@chn3_loop:
@chn3_1:
	.byte $44,$00,$45,$07,$44,$00,$45,$05,$43,$04,$45,$05,$44,$00,$43,$02
	.byte $44,$00,$43,$02,$44,$00,$45,$04,$43,$00,$45,$07,$09,$0b,$44,$00
	.byte $45,$07,$44,$00,$45,$05,$43,$04,$45,$05,$44,$00,$43,$02,$44,$00
	.byte $43,$02,$44,$00,$45,$04,$43,$00,$04,$00,$04,$44,$00,$45,$07,$44
	.byte $00,$45,$05,$43,$04,$45,$05,$44,$00,$43,$02,$44,$00,$43,$02,$44
	.byte $00,$45,$04,$43,$00,$45,$07,$09,$0b,$44,$00,$45,$07,$44,$00,$45
	.byte $05,$43,$04,$45,$05,$44,$00,$43,$02,$44,$00,$43,$02,$44,$00,$45
	.byte $04,$43,$00,$04,$00,$04
@chn3_2:
	.byte $ff,$40
	.word @chn3_1
@chn3_3:
	.byte $ff,$40
	.word @chn3_1
@chn3_4:
	.byte $ff,$40
	.word @chn3_1
@chn3_5:
	.byte $ff,$40
	.word @chn3_1
@chn3_6:
	.byte $ff,$40
	.word @chn3_1
@chn3_7:
	.byte $ff,$40
	.word @chn3_1
@chn3_8:
	.byte $ff,$40
	.word @chn3_1
@chn3_9:
	.byte $ff,$40
	.word @chn3_1
@chn3_10:
	.byte $ff,$40
	.word @chn3_1
@chn3_11:
	.byte $44,$00,$45,$07,$44,$00,$45,$05,$43,$04,$45,$05,$44,$00,$43,$02
	.byte $44,$00,$43,$02,$44,$00,$45,$04,$43,$00,$45,$07,$09,$0b,$44,$00
	.byte $45,$07,$44,$00,$45,$05,$43,$04,$45,$05,$44,$00,$43,$02,$44,$00
	.byte $43,$02,$44,$00,$45,$04,$43,$00,$04,$00,$04,$44,$00,$45,$07,$44
	.byte $00,$45,$05,$43,$04,$45,$05,$44,$00,$43,$02,$44,$00,$43,$02,$44
	.byte $00,$45,$04,$43,$00,$45,$07,$09,$0b,$44,$00,$45,$07,$44,$00,$45
	.byte $05,$43,$04,$45,$05,$44,$00,$43,$02,$00,$82,$45,$07,$80,$07,$80
	.byte $fe
	.word @chn3_loop

@chn4:
@chn4_0:
	.byte $bf
@chn4_loop:
@chn4_1:
	.byte $bf
@chn4_2:
	.byte $bf
@chn4_3:
	.byte $bf
@chn4_4:
	.byte $bf
@chn4_5:
	.byte $bf
@chn4_6:
	.byte $bf
@chn4_7:
	.byte $bf
@chn4_8:
	.byte $bf
@chn4_9:
	.byte $bf
@chn4_10:
	.byte $bf
@chn4_11:
	.byte $bf
	.byte $fe
	.word @chn4_loop
