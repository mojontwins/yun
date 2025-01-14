mus_game2_module:
	.word @chn0,@chn1,@chn2,@chn3,@chn4,music_instruments
	.byte $0b

@chn0:
@chn0_0:
	.byte $48,$18,$19,$18,$19,$18,$80,$19,$80,$1c,$80,$19,$80,$18,$80,$16
	.byte $80
@chn0_loop:
@chn0_1:
	.byte $48,$24,$87,$25,$28,$25,$24,$80,$22,$80
@chn0_2:
	.byte $24,$87,$25,$28,$25,$24,$80,$28,$80
@chn0_3:
	.byte $29,$87,$29,$2c,$29,$28,$80,$26,$80
@chn0_4:
	.byte $28,$86,$24,$84,$22,$80
@chn0_5:
	.byte $24,$87,$25,$28,$25,$24,$80,$22,$80
@chn0_6:
	.byte $ff,$10
	.word @chn0_2
@chn0_7:
	.byte $ff,$10
	.word @chn0_3
@chn0_8:
	.byte $ff,$10
	.word @chn0_4
@chn0_9:
	.byte $18,$19,$18,$19,$18,$80,$19,$80,$1c,$80,$19,$80,$18,$80,$16,$80
@chn0_10:
	.byte $18,$88,$14,$80,$13,$80,$11,$80
@chn0_11:
	.byte $13,$88,$14,$80,$18,$80,$14,$80
@chn0_12:
	.byte $13,$8e
@chn0_13:
	.byte $ff,$10
	.word @chn0_9
@chn0_14:
	.byte $ff,$10
	.word @chn0_10
@chn0_15:
	.byte $ff,$10
	.word @chn0_11
@chn0_16:
	.byte $ff,$10
	.word @chn0_12
@chn0_17:
	.byte $4a,$2b,$82,$29,$80,$24,$80,$2b,$80,$2c,$80,$2f,$80,$2c,$80
@chn0_18:
	.byte $2b,$82,$29,$80,$24,$80,$2b,$2c,$2b,$2c,$2f,$80,$2c,$80
@chn0_19:
	.byte $30,$82,$2f,$80,$2b,$80,$30,$82,$2f,$80,$2b,$80
@chn0_20:
	.byte $2b,$80,$2c,$80,$2b,$80,$2c,$80,$2f,$80,$2c,$80,$2b,$80,$29,$80
@chn0_21:
	.byte $ff,$10
	.word @chn0_0
@chn0_22:
	.byte $ff,$10
	.word @chn0_10
@chn0_23:
	.byte $ff,$10
	.word @chn0_11
@chn0_24:
	.byte $ff,$10
	.word @chn0_12
	.byte $fe
	.word @chn0_loop

@chn1:
@chn1_0:
	.byte $48,$0c,$8e
@chn1_loop:
@chn1_1:
	.byte $48,$2b,$8e
@chn1_2:
	.byte $28,$8e
@chn1_3:
	.byte $20,$8a,$1f,$82
@chn1_4:
	.byte $8f
@chn1_5:
	.byte $2b,$8e
@chn1_6:
	.byte $ff,$10
	.word @chn1_2
@chn1_7:
	.byte $ff,$10
	.word @chn1_3
@chn1_8:
	.byte $8f
@chn1_9:
	.byte $0c,$8e
@chn1_10:
	.byte $8f
@chn1_11:
	.byte $8f
@chn1_12:
	.byte $8f
@chn1_13:
	.byte $ff,$10
	.word @chn1_9
@chn1_14:
	.byte $8f
@chn1_15:
	.byte $8f
@chn1_16:
	.byte $8f
@chn1_17:
	.byte $42,$24,$82,$25,$80,$28,$80,$24,$80,$29,$80,$28,$80,$25,$80
@chn1_18:
	.byte $24,$82,$25,$80,$28,$80,$24,$80,$29,$80,$28,$80,$25,$80
@chn1_19:
	.byte $29,$82,$24,$80,$28,$80,$29,$82,$24,$80,$28,$80
@chn1_20:
	.byte $24,$80,$25,$80,$24,$80,$25,$80,$27,$80,$25,$80,$24,$80,$24,$80
@chn1_21:
	.byte $ff,$10
	.word @chn1_18
@chn1_22:
	.byte $ff,$10
	.word @chn1_18
@chn1_23:
	.byte $ff,$10
	.word @chn1_19
@chn1_24:
	.byte $ff,$10
	.word @chn1_20
	.byte $fe
	.word @chn1_loop

@chn2:
@chn2_0:
	.byte $3f,$8e
@chn2_loop:
@chn2_1:
	.byte $41,$0c,$82,$18,$82,$0c,$82,$18,$80,$16,$80
@chn2_2:
	.byte $0c,$82,$18,$82,$0c,$82,$18,$80,$0c,$80
@chn2_3:
	.byte $11,$82,$1d,$82,$11,$82,$1d,$82
@chn2_4:
	.byte $0c,$82,$18,$82,$0c,$80,$18,$80,$0c,$80,$16,$80
@chn2_5:
	.byte $0c,$82,$18,$82,$0c,$82,$18,$80,$16,$80
@chn2_6:
	.byte $ff,$10
	.word @chn2_2
@chn2_7:
	.byte $ff,$10
	.word @chn2_3
@chn2_8:
	.byte $ff,$10
	.word @chn2_4
@chn2_9:
	.byte $ff,$10
	.word @chn2_0
@chn2_10:
	.byte $8f
@chn2_11:
	.byte $8f
@chn2_12:
	.byte $8f
@chn2_13:
	.byte $ff,$10
	.word @chn2_0
@chn2_14:
	.byte $8f
@chn2_15:
	.byte $8f
@chn2_16:
	.byte $8f
@chn2_17:
	.byte $ff,$10
	.word @chn2_5
@chn2_18:
	.byte $ff,$10
	.word @chn2_2
@chn2_19:
	.byte $ff,$10
	.word @chn2_3
@chn2_20:
	.byte $ff,$10
	.word @chn2_4
@chn2_21:
	.byte $ff,$10
	.word @chn2_5
@chn2_22:
	.byte $ff,$10
	.word @chn2_2
@chn2_23:
	.byte $ff,$10
	.word @chn2_3
@chn2_24:
	.byte $ff,$10
	.word @chn2_4
	.byte $fe
	.word @chn2_loop

@chn3:
@chn3_0:
	.byte $8f
@chn3_loop:
@chn3_1:
	.byte $46,$04,$80,$47,$0d,$0d,$48,$05,$80,$47,$0d,$0d,$46,$04,$47,$0d
	.byte $0d,$0d,$48,$05,$80,$46,$04,$80
@chn3_2:
	.byte $04,$80,$47,$0d,$0d,$48,$05,$80,$47,$0d,$0d,$46,$04,$47,$0d,$0d
	.byte $0d,$46,$04,$80,$04,$80
@chn3_3:
	.byte $04,$80,$47,$0d,$0d,$48,$05,$80,$47,$0d,$0d,$46,$04,$47,$0d,$0d
	.byte $0d,$48,$05,$80,$46,$04,$80
@chn3_4:
	.byte $ff,$10
	.word @chn3_2
@chn3_5:
	.byte $ff,$10
	.word @chn3_3
@chn3_6:
	.byte $ff,$10
	.word @chn3_2
@chn3_7:
	.byte $ff,$10
	.word @chn3_3
@chn3_8:
	.byte $ff,$10
	.word @chn3_2
@chn3_9:
	.byte $ff,$10
	.word @chn3_3
@chn3_10:
	.byte $ff,$10
	.word @chn3_2
@chn3_11:
	.byte $ff,$10
	.word @chn3_3
@chn3_12:
	.byte $ff,$10
	.word @chn3_2
@chn3_13:
	.byte $ff,$10
	.word @chn3_3
@chn3_14:
	.byte $ff,$10
	.word @chn3_2
@chn3_15:
	.byte $ff,$10
	.word @chn3_3
@chn3_16:
	.byte $ff,$10
	.word @chn3_2
@chn3_17:
	.byte $ff,$10
	.word @chn3_3
@chn3_18:
	.byte $ff,$10
	.word @chn3_2
@chn3_19:
	.byte $ff,$10
	.word @chn3_3
@chn3_20:
	.byte $ff,$10
	.word @chn3_2
@chn3_21:
	.byte $ff,$10
	.word @chn3_3
@chn3_22:
	.byte $ff,$10
	.word @chn3_2
@chn3_23:
	.byte $ff,$10
	.word @chn3_3
@chn3_24:
	.byte $ff,$10
	.word @chn3_2
	.byte $fe
	.word @chn3_loop

@chn4:
