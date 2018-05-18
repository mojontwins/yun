;this file for FamiTone2 library generated by text2data tool

yun_music_data:
	.byte 5
	.word @instruments
	.word @samples-3
	.word @song0ch0,@song0ch1,@song0ch2,@song0ch3,@song0ch4,307,256
	.word @song1ch0,@song1ch1,@song1ch2,@song1ch3,@song1ch4,307,256
	.word @song2ch0,@song2ch1,@song2ch2,@song2ch3,@song2ch4,307,256
	.word @song3ch0,@song3ch1,@song3ch2,@song3ch3,@song3ch4,307,256
	.word @song4ch0,@song4ch1,@song4ch2,@song4ch3,@song4ch4,307,256

@instruments:
	.byte $30 ;instrument $00
	.word @env2,@env0,@env0
	.byte $00
	.byte $30 ;instrument $01
	.word @env1,@env0,@env0
	.byte $00
	.byte $30 ;instrument $04
	.word @env9,@env14,@env0
	.byte $00
	.byte $30 ;instrument $05
	.word @env12,@env0,@env0
	.byte $00
	.byte $30 ;instrument $06
	.word @env10,@env0,@env0
	.byte $00
	.byte $30 ;instrument $07
	.word @env6,@env0,@env0
	.byte $00
	.byte $30 ;instrument $08
	.word @env11,@env0,@env0
	.byte $00
	.byte $30 ;instrument $09
	.word @env7,@env0,@env0
	.byte $00
	.byte $30 ;instrument $0a
	.word @env3,@env0,@env0
	.byte $00
	.byte $30 ;instrument $0b
	.word @env4,@env0,@env0
	.byte $00
	.byte $30 ;instrument $0c
	.word @env5,@env0,@env0
	.byte $00
	.byte $30 ;instrument $0d
	.word @env8,@env13,@env0
	.byte $00

@samples:
@env0:
	.byte $c0,$00,$00
@env1:
	.byte $c1,$c2,$c3,$c6,$00,$03
@env2:
	.byte $cf,$00,$00
@env3:
	.byte $ca,$c8,$c6,$c4,$c2,$c1,$c0,$00,$06
@env4:
	.byte $ca,$c9,$c7,$c4,$c2,$c0,$00,$05
@env5:
	.byte $c0,$c1,$c2,$c4,$c5,$c6,$03,$c4,$c3,$c2,$03,$c2,$00,$0b
@env6:
	.byte $cf,$cd,$cb,$c9,$c7,$c6,$c5,$c4,$c3,$06,$c3,$00,$0a
@env7:
	.byte $ce,$cd,$cc,$ca,$c9,$c8,$c7,$c6,$c5,$c4,$c4,$c3,$c2,$c6,$c5,$c4
	.byte $c4,$c3,$c2,$c2,$c1,$c0,$0a,$c2,$c3,$c2,$c2,$c1,$04,$c0,$00,$1d
@env8:
	.byte $c2,$c3,$c5,$c6,$c7,$c8,$c9,$03,$c8,$c6,$c4,$c8,$c8,$c8,$00,$0d
@env9:
	.byte $cf,$cd,$cb,$c9,$c7,$c5,$c3,$c1,$c0,$00,$08
@env10:
	.byte $ca,$c5,$c3,$c2,$c0,$00,$04
@env11:
	.byte $cf,$cf,$ce,$ce,$cd,$cb,$c6,$c5,$c3,$c3,$c2,$c2,$c1,$02,$c1,$00
	.byte $0e
@env12:
	.byte $cd,$cc,$ca,$c9,$c7,$c6,$c5,$c3,$c0,$00,$08
@env13:
	.byte $c0,$cc,$cc,$c0,$00,$03
@env14:
	.byte $c7,$c3,$c0,$bd,$00,$02


@song0ch0:
	.byte $fb,$06
@ref0:
	.byte $8a,$33,$35,$33,$35,$33,$35,$33,$35,$33,$35,$33,$35,$33,$35,$33
	.byte $35,$32,$9b,$00,$9f
@song0ch0loop:
@ref1:
	.byte $81
	.byte $fd
	.word @song0ch0loop

@song0ch1:
@ref2:
	.byte $9f,$8a,$59,$5b,$59,$5b,$59,$5b,$59,$5b,$58,$99,$00,$a1
@song0ch1loop:
@ref3:
	.byte $81
	.byte $fd
	.word @song0ch1loop

@song0ch2:
@ref4:
	.byte $80,$32,$8d,$22,$85,$28,$85,$32,$8d,$22,$85,$28,$85,$22,$97,$00
	.byte $a3
@song0ch2loop:
@ref5:
	.byte $81
	.byte $fd
	.word @song0ch2loop

@song0ch3:
@ref6:
	.byte $86,$21,$21,$84,$21,$86,$21,$21,$21,$84,$21,$86,$21,$21,$21,$84
	.byte $21,$86,$21,$21,$21,$84,$21,$86,$21,$20,$bd
@song0ch3loop:
@ref7:
	.byte $81
	.byte $fd
	.word @song0ch3loop

@song0ch4:
@ref8:
	.byte $f9,$85
@song0ch4loop:
@ref9:
	.byte $81
	.byte $fd
	.word @song0ch4loop


@song1ch0:
	.byte $fb,$06
@ref10:
	.byte $8a,$31,$33,$31,$33,$31,$33,$31,$33,$39,$3b,$39,$3b,$39,$3b,$39
	.byte $3b,$32,$9b,$00,$81
@song1ch0loop:
@ref11:
	.byte $e1
	.byte $fd
	.word @song1ch0loop

@song1ch1:
@ref12:
	.byte $80,$32,$8d,$30,$8d,$3a,$8d,$38,$8d,$8a,$38,$9b,$00,$81
@song1ch1loop:
@ref13:
	.byte $e1
	.byte $fd
	.word @song1ch1loop

@song1ch2:
@ref14:
	.byte $80,$4b,$01,$4b,$01,$32,$85,$01,$33,$53,$01,$53,$01,$38,$85,$00
	.byte $85,$8a,$40,$9b,$00,$81
@song1ch2loop:
@ref15:
	.byte $e1
	.byte $fd
	.word @song1ch2loop

@song1ch3:
@ref16:
	.byte $86,$03,$88,$1f,$1f,$1f,$84,$0d,$88,$1f,$1f,$86,$03,$03,$88,$1f
	.byte $1f,$1f,$84,$0d,$88,$1f,$1f,$1e,$a3
@song1ch3loop:
@ref17:
	.byte $e1
	.byte $fd
	.word @song1ch3loop

@song1ch4:
@ref18:
	.byte $e1
@song1ch4loop:
@ref19:
	.byte $e1
	.byte $fd
	.word @song1ch4loop


@song2ch0:
	.byte $fb,$0d
@song2ch0loop:
@ref20:
	.byte $8a,$2c,$9d,$2c,$9d
@ref21:
	.byte $44,$9d,$44,$9d
@ref22:
	.byte $2c,$9d,$2c,$9d
@ref23:
	.byte $2c,$9d,$2c,$9d
@ref24:
	.byte $2c,$8d,$2c,$8d,$2c,$8d,$2c,$8d,$2c,$8d
@ref25:
	.byte $2c,$8d,$26,$9d,$2a,$89,$2d,$2a,$85,$26,$85
@ref26:
	.byte $2c,$9d,$2c,$8d,$2c,$85,$2e,$85
@ref27:
	.byte $32,$8d,$1a,$8d,$32,$8d,$1a,$8d
@ref28:
	.byte $32,$85,$24,$85,$3c,$85,$24,$85,$40,$85,$33,$3d,$36,$8d
@ref29:
	.byte $8f,$2c,$8d,$3a,$8d,$3c,$8d
	.byte $fd
	.word @song2ch0loop

@song2ch1:
@song2ch1loop:
@ref30:
	.byte $00,$bd
@ref31:
	.byte $bf
@ref32:
	.byte $8a,$3a,$85,$37,$3b,$3d,$3a,$89,$00,$9d
@ref33:
	.byte $3a,$85,$45,$3d,$41,$3d,$3a,$85,$00,$9d
@ref34:
	.byte $4e,$85,$4c,$95,$4e,$85,$4c,$95,$52,$85,$4e,$85
@ref35:
	.byte $4c,$85,$48,$85,$4e,$9d,$52,$9d
@ref36:
	.byte $44,$91,$3b,$3d,$37,$44,$8b,$46,$44,$8d
@ref37:
	.byte $3a,$9d,$3a,$9d
@ref38:
	.byte $82,$3d,$25,$2d,$25,$3d,$25,$2d,$25,$00,$89,$8a,$24,$91
@ref39:
	.byte $82,$2c,$85,$3c,$85,$3a,$85,$36,$85,$3c,$85,$40,$85,$3c,$85,$3a
	.byte $85
	.byte $fd
	.word @song2ch1loop

@song2ch2:
@song2ch2loop:
@ref40:
	.byte $80,$44,$9d,$2c,$9d
@ref41:
	.byte $2c,$9d,$2c,$83,$00,$22,$83,$00,$24,$83,$00,$1e,$83,$00
@ref42:
	.byte $2c,$bd
@ref43:
	.byte $22,$85,$1f,$23,$25,$28,$85,$25,$22,$9d
@ref44:
	.byte $2c,$8d,$2c,$2e,$2c,$2e,$2c,$2e,$2c,$2e,$2c,$8d,$2c,$2e,$2c,$2e
	.byte $2c,$2e,$2c,$2e,$2c,$85,$2e,$85
@ref45:
	.byte $28,$85,$1e,$85,$36,$9d,$22,$9d
@ref46:
	.byte $2c,$8d,$3a,$85,$3c,$85,$2c,$8d,$40,$85,$3c,$85
@ref47:
	.byte $22,$9d,$32,$83,$00,$2e,$83,$00,$28,$83,$00,$22,$83,$00
@ref48:
	.byte $32,$9d,$28,$85,$24,$85,$1e,$8d
@ref49:
	.byte $2c,$bd
	.byte $fd
	.word @song2ch2loop

@song2ch3:
@song2ch3loop:
@ref50:
	.byte $86,$21,$88,$1f,$84,$09,$88,$1e,$1e,$86,$20,$88,$1e,$86,$21,$84
	.byte $09,$88,$1e,$1e,$86,$21,$88,$1f,$84,$09,$88,$1e,$1e,$86,$20,$88
	.byte $1e,$86,$21,$84,$09,$88,$1e,$1e
	.byte $ff,$16
	.word @ref50
	.byte $ff,$16
	.word @ref50
	.byte $ff,$16
	.word @ref50
@ref54:
	.byte $8c,$14,$85,$15,$86,$21,$84,$1e,$1e,$86,$20,$88,$1e,$86,$20,$88
	.byte $1e,$86,$20,$88,$1e,$8c,$14,$85,$15,$86,$21,$84,$1e,$1e,$86,$20
	.byte $88,$1e,$86,$20,$88,$1e,$86,$20,$88,$1e,$8c,$14,$85,$14,$85
@ref55:
	.byte $14,$85,$14,$85,$86,$21,$88,$1f,$84,$09,$88,$1e,$1e,$86,$20,$88
	.byte $1e,$86,$21,$84,$09,$88,$1e,$1e,$8c,$15,$88,$1f,$84,$09,$88,$1e
	.byte $1e,$86,$20,$88,$1e,$86,$21,$84,$09,$88,$1e,$1e
	.byte $ff,$16
	.word @ref50
	.byte $ff,$16
	.word @ref50
	.byte $ff,$16
	.word @ref50
	.byte $ff,$16
	.word @ref50
	.byte $fd
	.word @song2ch3loop

@song2ch4:
@song2ch4loop:
@ref60:
	.byte $bf
@ref61:
	.byte $bf
@ref62:
	.byte $bf
@ref63:
	.byte $bf
@ref64:
	.byte $cf
@ref65:
	.byte $cf
@ref66:
	.byte $bf
@ref67:
	.byte $bf
@ref68:
	.byte $bf
@ref69:
	.byte $bf
	.byte $fd
	.word @song2ch4loop


@song3ch0:
	.byte $fb,$0a
@ref70:
	.byte $8a,$32,$bd
@ref71:
	.byte $bf
@song3ch0loop:
@ref72:
	.byte $90,$5c,$62,$6a,$90,$62,$6a,$92,$62,$8a,$5c,$62,$6a,$90,$62,$6a
	.byte $92,$62,$6a,$85,$8a,$5c,$60,$6a,$90,$60,$6a,$92,$60,$8a,$5c,$66
	.byte $6a,$90,$66,$6a,$92,$66,$6a,$85
@ref73:
	.byte $8a,$5c,$62,$6a,$90,$62,$6a,$92,$62,$8a,$5c,$62,$6a,$90,$62,$6a
	.byte $92,$62,$6a,$85,$8a,$5c,$60,$6a,$90,$60,$6a,$92,$60,$8a,$5c,$66
	.byte $6a,$90,$66,$6a,$92,$66,$6a,$85
	.byte $ff,$1c
	.word @ref73
	.byte $ff,$1c
	.word @ref73
@ref76:
	.byte $8a,$60,$6a,$6e,$90,$6a,$6e,$92,$6a,$8a,$60,$6a,$70,$90,$6a,$70
	.byte $92,$6a,$70,$85,$8a,$5c,$64,$6a,$90,$64,$6a,$92,$64,$8a,$5c,$64
	.byte $6e,$90,$64,$6e,$92,$64,$6e,$85
	.byte $ff,$1c
	.word @ref76
	.byte $ff,$1c
	.word @ref76
	.byte $ff,$1c
	.word @ref76
	.byte $ff,$1c
	.word @ref73
	.byte $ff,$1c
	.word @ref73
	.byte $ff,$1c
	.word @ref73
	.byte $ff,$1c
	.word @ref73
	.byte $ff,$1c
	.word @ref76
	.byte $ff,$1c
	.word @ref76
	.byte $ff,$1c
	.word @ref76
	.byte $ff,$1c
	.word @ref76
@ref88:
	.byte $8a,$5c,$64,$6a,$90,$64,$6a,$92,$64,$8a,$5c,$64,$6e,$90,$64,$6e
	.byte $92,$64,$6e,$85,$8a,$56,$5c,$6a,$90,$5c,$6a,$92,$5c,$8a,$56,$5c
	.byte $64,$90,$5c,$64,$92,$5c,$64,$85
	.byte $ff,$1c
	.word @ref88
	.byte $ff,$1c
	.word @ref88
	.byte $ff,$1c
	.word @ref88
@ref92:
	.byte $00,$bd
@ref93:
	.byte $af,$8a,$44,$90,$44,$92,$44,$85,$5c,$90,$5c
	.byte $fd
	.word @song3ch0loop

@song3ch1:
@ref94:
	.byte $00,$bd
@ref95:
	.byte $bf
@song3ch1loop:
@ref96:
	.byte $94,$44,$b9,$40,$81
@ref97:
	.byte $44,$ad,$00,$89,$40,$81
@ref98:
	.byte $44,$b9,$40,$81
	.byte $ff,$06
	.word @ref97
@ref100:
	.byte $49,$3a,$85,$49,$3a,$85,$48,$85,$4d,$48,$85,$4f,$4f,$4d,$49,$4c
	.byte $81
@ref101:
	.byte $49,$3a,$85,$49,$3a,$85,$48,$85,$45,$40,$85,$3a,$85,$41,$3b,$40
	.byte $81
	.byte $ff,$11
	.word @ref100
	.byte $ff,$11
	.word @ref101
@ref104:
	.byte $44,$b9,$40,$81
	.byte $ff,$06
	.word @ref97
@ref106:
	.byte $44,$b9,$40,$81
	.byte $ff,$06
	.word @ref97
	.byte $ff,$11
	.word @ref100
	.byte $ff,$11
	.word @ref101
	.byte $ff,$11
	.word @ref100
	.byte $ff,$11
	.word @ref101
@ref112:
	.byte $96,$45,$3b,$43,$44,$91,$52,$85,$4e,$85,$4d,$49,$45,$48,$81
@ref113:
	.byte $45,$3b,$43,$44,$91,$52,$85,$4e,$85,$56,$85,$52,$85
@ref114:
	.byte $45,$3b,$43,$44,$91,$52,$85,$4e,$85,$4d,$49,$45,$48,$81
	.byte $ff,$0d
	.word @ref113
	.byte $ff,$04
	.word @ref96
	.byte $ff,$06
	.word @ref97
	.byte $fd
	.word @song3ch1loop

@song3ch2:
@ref118:
	.byte $80,$14,$89,$1a,$91,$18,$89,$1e,$91
@ref119:
	.byte $14,$89,$1a,$91,$18,$89,$1f,$00,$8d
@song3ch2loop:
	.byte $ff,$08
	.word @ref118
	.byte $ff,$09
	.word @ref119
@ref122:
	.byte $14,$89,$1a,$91,$18,$89,$1e,$91
	.byte $ff,$09
	.word @ref119
@ref124:
	.byte $18,$89,$22,$91,$2c,$85,$1d,$14,$8d,$2c,$81
	.byte $ff,$0b
	.word @ref124
	.byte $ff,$0b
	.word @ref124
	.byte $ff,$0b
	.word @ref124
	.byte $ff,$08
	.word @ref122
	.byte $ff,$09
	.word @ref119
	.byte $ff,$08
	.word @ref122
	.byte $ff,$09
	.word @ref119
	.byte $ff,$0b
	.word @ref124
	.byte $ff,$0b
	.word @ref124
	.byte $ff,$0b
	.word @ref124
	.byte $ff,$0b
	.word @ref124
@ref136:
	.byte $15,$23,$1d,$15,$23,$1d,$14,$85,$0f,$15,$1d,$0f,$15,$1d,$23,$26
	.byte $81
	.byte $ff,$11
	.word @ref136
	.byte $ff,$11
	.word @ref136
	.byte $ff,$11
	.word @ref136
	.byte $ff,$08
	.word @ref122
	.byte $ff,$09
	.word @ref119
	.byte $fd
	.word @song3ch2loop

@song3ch3:
@ref142:
	.byte $bf
@ref143:
	.byte $86,$20,$88,$0e,$86,$20,$88,$0a,$84,$08,$88,$0a,$86,$20,$84,$04
	.byte $86,$20,$84,$04,$86,$20,$88,$08,$84,$20,$88,$0e,$12,$16,$86,$20
	.byte $88,$0e,$86,$20,$88,$0a,$84,$08,$88,$0a,$86,$20,$84,$04,$86,$20
	.byte $84,$04,$86,$20,$88,$08,$84,$20,$88,$0e,$12,$16
@song3ch3loop:
@ref144:
	.byte $86,$20,$88,$0e,$86,$20,$88,$0a,$84,$08,$88,$0a,$86,$20,$84,$04
	.byte $86,$20,$84,$04,$86,$20,$88,$08,$84,$20,$88,$0e,$12,$16,$86,$20
	.byte $88,$0e,$86,$20,$88,$0a,$84,$08,$88,$0a,$86,$20,$84,$04,$86,$20
	.byte $84,$04,$86,$20,$88,$08,$84,$20,$08,$20,$08
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
	.byte $ff,$20
	.word @ref144
@ref165:
	.byte $86,$20,$88,$0e,$86,$20,$88,$0a,$84,$08,$88,$0a,$86,$20,$84,$04
	.byte $86,$20,$84,$04,$86,$20,$88,$08,$84,$20,$88,$0e,$12,$16,$86,$20
	.byte $88,$0e,$86,$20,$88,$0a,$84,$08,$88,$0a,$86,$20,$84,$04,$20,$85
	.byte $88,$0f,$0e,$81
	.byte $fd
	.word @song3ch3loop

@song3ch4:
@ref166:
	.byte $bf
@ref167:
	.byte $bf
@song3ch4loop:
@ref168:
	.byte $bf
@ref169:
	.byte $bf
@ref170:
	.byte $bf
@ref171:
	.byte $bf
@ref172:
	.byte $bf
@ref173:
	.byte $bf
@ref174:
	.byte $bf
@ref175:
	.byte $bf
@ref176:
	.byte $bf
@ref177:
	.byte $bf
@ref178:
	.byte $bf
@ref179:
	.byte $bf
@ref180:
	.byte $bf
@ref181:
	.byte $bf
@ref182:
	.byte $bf
@ref183:
	.byte $bf
@ref184:
	.byte $bf
@ref185:
	.byte $bf
@ref186:
	.byte $bf
@ref187:
	.byte $bf
@ref188:
	.byte $bf
@ref189:
	.byte $bf
	.byte $fd
	.word @song3ch4loop


@song4ch0:
	.byte $fb,$0b
@ref190:
	.byte $8a,$32,$34,$32,$34,$33,$34,$81
@ref191:
	.byte $3b,$35,$33,$2e,$81
@song4ch0loop:
@ref192:
	.byte $8a,$4a,$8f,$4c,$52,$4c,$4b,$47,$4a,$8f,$4c,$52,$4c,$4b,$52,$81
@ref193:
	.byte $54,$8f,$54,$5a,$54,$53,$4f,$52,$8d,$4a,$89,$46,$81
@ref194:
	.byte $4a,$8f,$4c,$52,$4c,$4b,$47,$4a,$8f,$4c,$52,$4c,$4b,$52,$81
	.byte $ff,$0d
	.word @ref193
@ref196:
	.byte $32,$34,$32,$34,$33,$35,$3b,$35,$33,$2f,$32,$91,$2b,$29,$24,$81
@ref197:
	.byte $28,$91,$2b,$33,$2b,$28,$9d
	.byte $ff,$10
	.word @ref196
	.byte $ff,$07
	.word @ref197
@ref200:
	.byte $8e,$58,$85,$55,$4b,$59,$5b,$61,$5b,$58,$85,$55,$4b,$58,$5a,$58
	.byte $5a,$61,$5a,$81
@ref201:
	.byte $62,$85,$61,$59,$62,$85,$61,$59,$59,$5b,$59,$5b,$61,$5b,$59,$54
	.byte $81
@ref202:
	.byte $58,$85,$55,$4b,$59,$5b,$61,$5b,$58,$85,$55,$4b,$58,$5a,$58,$5a
	.byte $61,$5a,$81
	.byte $ff,$11
	.word @ref201
@ref204:
	.byte $8a,$32,$34,$32,$34,$33,$35,$3b,$35,$33,$2f,$32,$91,$2b,$29,$24
	.byte $81
	.byte $ff,$07
	.word @ref197
	.byte $ff,$10
	.word @ref196
	.byte $ff,$07
	.word @ref197
	.byte $fd
	.word @song4ch0loop

@song4ch1:
@ref208:
	.byte $8a,$1a,$8d
@ref209:
	.byte $8f
@song4ch1loop:
@ref210:
	.byte $8a,$58,$9d,$52,$9d
@ref211:
	.byte $42,$95,$40,$a5
@ref212:
	.byte $58,$9d,$52,$9d
@ref213:
	.byte $42,$95,$40,$a5
@ref214:
	.byte $1a,$bd
@ref215:
	.byte $bf
@ref216:
	.byte $1a,$bd
@ref217:
	.byte $bf
@ref218:
	.byte $82,$4a,$85,$4d,$53,$4b,$55,$53,$4d,$4a,$85,$4d,$53,$4b,$55,$53
	.byte $4c,$81
@ref219:
	.byte $54,$85,$4f,$53,$54,$85,$4f,$53,$4b,$4d,$4b,$4d,$51,$4d,$4b,$4a
	.byte $81
@ref220:
	.byte $4a,$85,$4d,$53,$4b,$55,$53,$4d,$4a,$85,$4d,$53,$4b,$55,$53,$4c
	.byte $81
	.byte $ff,$11
	.word @ref219
@ref222:
	.byte $8a,$1a,$bd
@ref223:
	.byte $bf
@ref224:
	.byte $1a,$bd
@ref225:
	.byte $bf
	.byte $fd
	.word @song4ch1loop

@song4ch2:
@ref226:
	.byte $00,$8d
@ref227:
	.byte $8f
@song4ch2loop:
@ref228:
	.byte $80,$1a,$85,$32,$85,$1a,$85,$33,$2f,$1a,$85,$32,$85,$1a,$85,$33
	.byte $1a,$81
@ref229:
	.byte $24,$85,$3c,$85,$24,$85,$3c,$85,$1a,$85,$32,$85,$1b,$33,$1b,$2e
	.byte $81
@ref230:
	.byte $1a,$85,$32,$85,$1a,$85,$33,$2f,$1a,$85,$32,$85,$1a,$85,$33,$1a
	.byte $81
	.byte $ff,$11
	.word @ref229
@ref232:
	.byte $00,$bd
@ref233:
	.byte $bf
@ref234:
	.byte $00,$bd
@ref235:
	.byte $bf
	.byte $ff,$11
	.word @ref230
@ref237:
	.byte $24,$85,$3c,$85,$24,$85,$3c,$85,$1a,$85,$32,$85,$31,$35,$1b,$2e
	.byte $81
	.byte $ff,$11
	.word @ref230
	.byte $ff,$11
	.word @ref237
@ref240:
	.byte $00,$bd
@ref241:
	.byte $bf
@ref242:
	.byte $00,$bd
@ref243:
	.byte $bf
	.byte $fd
	.word @song4ch2loop

@song4ch3:
@ref244:
	.byte $8f
@ref245:
	.byte $8f
@song4ch3loop:
@ref246:
	.byte $86,$09,$88,$1a,$1a,$8a,$0b,$88,$1a,$1a,$86,$08,$88,$1a,$1a,$1a
	.byte $8a,$0b,$86,$09,$09,$88,$1a,$1a,$8a,$0b,$88,$1a,$1a,$86,$08,$88
	.byte $1a,$1a,$1a,$86,$09,$08,$81
@ref247:
	.byte $09,$88,$1a,$1a,$8a,$0b,$88,$1a,$1a,$86,$08,$88,$1a,$1a,$1a,$8a
	.byte $0b,$86,$09,$09,$88,$1a,$1a,$8a,$0b,$88,$1a,$1a,$86,$08,$88,$1a
	.byte $1a,$1a,$86,$09,$08,$81
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $ff,$19
	.word @ref247
	.byte $fd
	.word @song4ch3loop

@song4ch4:
@ref262:
	.byte $8f
@ref263:
	.byte $8f
@song4ch4loop:
@ref264:
	.byte $bf
@ref265:
	.byte $bf
@ref266:
	.byte $bf
@ref267:
	.byte $bf
@ref268:
	.byte $bf
@ref269:
	.byte $bf
@ref270:
	.byte $bf
@ref271:
	.byte $bf
@ref272:
	.byte $bf
@ref273:
	.byte $bf
@ref274:
	.byte $bf
@ref275:
	.byte $bf
@ref276:
	.byte $bf
@ref277:
	.byte $bf
@ref278:
	.byte $bf
@ref279:
	.byte $bf
	.byte $fd
	.word @song4ch4loop
