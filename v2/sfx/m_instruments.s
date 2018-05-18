music_instruments:
@ins:
	.word @env_default,@env_default,@env_default
	.byte $30,$00
	.word @env_vol2,@env_default,@env_default
	.byte $30,$00
	.word @env_vol0,@env_default,@env_pitch0
	.byte $30,$00
	.word @env_vol13,@env_arp7,@env_default
	.byte $30,$00
	.word @env_vol22,@env_default,@env_default
	.byte $30,$00
	.word @env_vol15,@env_default,@env_default
	.byte $30,$00
	.word @env_vol9,@env_default,@env_default
	.byte $30,$00
	.word @env_vol16,@env_default,@env_default
	.byte $30,$00
	.word @env_vol11,@env_default,@env_default
	.byte $30,$00
	.word @env_vol4,@env_default,@env_default
	.byte $30,$00
	.word @env_vol5,@env_default,@env_default
	.byte $30,$00
	.word @env_vol7,@env_default,@env_default
	.byte $30,$00
	.word @env_vol12,@env_arp0,@env_default
	.byte $30,$00
@env_default:
	.byte $c0,$7f,$00
@env_vol0:
	.byte $c1,$c2,$c3,$c6,$7f,$03
@env_vol2:
	.byte $cf,$7f,$00
@env_vol4:
	.byte $ca,$c8,$c6,$c4,$c2,$c1,$c0,$7f,$06
@env_vol5:
	.byte $ca,$c9,$c7,$c4,$c2,$c0,$7f,$05
@env_vol7:
	.byte $c0,$c1,$c2,$c4,$c5,$c6,$02,$c4,$c3,$c2,$03,$7f,$0a
@env_vol9:
	.byte $cf,$cd,$cb,$c9,$c7,$c6,$c5,$c4,$c3,$06,$7f,$09
@env_vol11:
	.byte $ce,$cd,$cc,$ca,$c9,$c8,$c7,$c6,$c5,$c4,$c4,$c3,$c2,$c6,$c5,$c4
	.byte $c4,$c3,$c2,$c2,$c1,$c0,$09,$c2,$c3,$c2,$c2,$c1,$03,$c0,$15,$7f
	.byte $1e
@env_vol12:
	.byte $c2,$c3,$c5,$c6,$c7,$c8,$c9,$02,$c8,$c6,$c4,$c8,$01,$7f,$0c
@env_vol13:
	.byte $cf,$cd,$cb,$c9,$c7,$c5,$c3,$c1,$c0,$7f,$08
@env_vol15:
	.byte $ca,$c5,$c3,$c2,$c0,$7f,$04
@env_vol16:
	.byte $cf,$cf,$ce,$ce,$cd,$cb,$c6,$c5,$c3,$c3,$c2,$c2,$c1,$02,$7f,$0d
@env_vol22:
	.byte $cd,$cc,$ca,$c9,$c7,$c6,$c5,$c3,$c0,$7f,$08
@env_arp0:
	.byte $c0,$cc,$cc,$c0,$7f,$03
@env_arp1:
	.byte $cc,$c0,$7f,$01
@env_arp7:
	.byte $c7,$c3,$c0,$bd,$7f,$02
