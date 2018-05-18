@echo off

if [%1]==[justcompile] goto :compilestage

echo Generating pals
..\utils\mkts.exe mode=pals pals=..\gfx\palts1A.png out=work\palbg0.h label=mypal_game_bg0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1B.png out=work\palbg1.h label=mypal_game_bg1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1C.png out=work\palbg2.h label=mypal_game_bg2 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts2A.png out=work\palbg3.h label=mypal_game_bg3 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts2B.png out=work\palbg4.h label=mypal_game_bg4 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts2C.png out=work\palbg5.h label=mypal_game_bg5 silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltsT.png out=work\palbgT.h label=mypal_title silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1A.png out=work\palfg0.h label=mypal_game_fg0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1B.png out=work\palfg1.h label=mypal_game_fg1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1C.png out=work\palfg2.h label=mypal_game_fg2 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss2A.png out=work\palfg3.h label=mypal_game_fg3 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss2B.png out=work\palfg4.h label=mypal_game_fg4 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss2C.png out=work\palfg5.h label=mypal_game_fg5 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palcuts1.png out=work\palcuts.h label=mypal_cuts silent
..\utils\mkts.exe mode=pals pals=..\gfx\palmt.png out=work\mypalmt.h label=mypal_mt silent
copy /b work\palbg0.h + work\palbg1.h + work\palbg2.h + work\palbg3.h + work\palbg4.h + work\palbg5.h + work\palbgT.h + work\palfg0.h + work\palfg1.h + work\palfg2.h + work\palfg3.h + work\palfg4.h + work\palfg5.h + work\palcuts.h + work\mypalmt.h assets\palettes.h > nul

echo Exporting chr
cd ..\gfx

rem charset, tileset, fill to 4096
..\utils\mkts.exe mode=text in=alltext.png out=tschr1.bin pals=palts1A.png tsmap=..\dev\work\strings.h offset=0,0 label=strings tmapoffset=0 silent
..\utils\mkts.exe in=ts.png pals=palts1A.png out=tschr3.bin mode=mapped offset=0,0 size=16,5 tsmap=..\dev\assets\tiledata1.h label=ts1 tmapoffset=43 max=77 silent

copy /b tschr1.bin + tschr2.bin + tschr3.bin tschr.bin > nul
..\utils\fillto.exe tschr.bin 4096

del tschr1.bin > nul
del tschr2.bin > nul
del tschr3.bin > nul
rem del tschr4.bin > nul

..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschr1.bin mode=sprites tsmap=..\dev\assets\spr_pl.h offset=0,0 size=7,1 metasize=2,3 sprorg=0,-8 label=spr_pl genflipped silent
..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschrC.bin mode=chars offset=15,0 size=1,1 silent
..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschr2a.bin mode=sprites tsmap=..\dev\assets\spr_en1.h offset=0,3 size=8,1 metasize=2,2 sprorg=0,0 label=spr_en1 tmapoffset=35 genflipped upsidedown silent
..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschr2b.bin mode=sprites tsmap=..\dev\assets\spr_en2.h offset=0,5 size=6,1 metasize=2,2 sprorg=0,0 label=spr_en2 tmapoffset=57 genflipped upsidedown silent
..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschr2c.bin mode=sprites tsmap=..\dev\assets\spr_en3.h offset=0,7 size=6,1 metasize=2,2 sprorg=0,0 label=spr_en3 tmapoffset=73 genflipped upsidedown silent
..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschr3.bin mode=sprites tsmap=..\dev\assets\spr_hs.h offset=0,9 size=8,2 metasize=2,2 sprorg=0,0 max=10 label=spr_hs tmapoffset=83 silent
..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschr2d.bin mode=sprites tsmap=..\dev\assets\spr_en4.h offset=4,11 size=2,1 metasize=2,2 sprorg=0,0 label=spr_en4 tmapoffset=112 upsidedown silent
..\utils\mkts.exe in=logo.png pals=palmt.png out=sschr4.bin mode=sprites tsmap=..\dev\assets\spr_logo.h offset=0,0 size=1,1 metasize=6,2 sprorg=0,0 label=spr_mt_logo tmapoffset=119 silent
..\utils\mkts.exe in=cuts1.png pals=palcuts1.png out=sschr5.bin mode=mapped tsmap=..\dev\assets\cutscene.h offset=0,0 size=8,6 metasize=2,2 label=cuts tmapoffset=131 silent
..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschr6a.bin mode=sprites tsmap=..\dev\assets\spr_limite1.h offset=0,13 size=6,1 metasize=2,3 sprorg=0,-8 label=spr_lim1 tmapoffset=219 genflipped silent
..\utils\mkts.exe in=ss1.png pals=palss1A.png out=sschr6b.bin mode=sprites tsmap=..\dev\assets\spr_limite2.h offset=12,13 size=1,1 metasize=3,2 sprorg=-4,0 label=spr_lim2 tmapoffset=249 genflipped silent

copy /b sschr1.bin + sschrC.bin + sschr2a.bin + sschr2b.bin + sschr2c.bin + sschr3.bin + sschr2d.bin + sschr4.bin + sschr5.bin + sschr6a.bin + sschr6b.bin sschr.bin > nul
del sschr1.bin > nul
del sschrC.bin > nul
del sschr2a.bin > nul
del sschr2b.bin > nul
del sschr2c.bin > nul
del sschr3.bin > nul
del sschr2d.bin > nul
del sschr4.bin > nul
del sschr5.bin > nul
del sschr6a.bin > nul
del sschr6b.bin > nul
..\utils\fillto.exe sschr.bin 4096

copy /b tschr.bin + sschr.bin ..\dev\tileset0.chr > nul

del tschr.bin > nul
del sschr.bin > nul

echo Copying enems
cd ..\enems
..\utils\eneexp2.exe enems0.ene ..\dev\assets\enems0.h 0
..\utils\eneexp2.exe enems1.ene ..\dev\assets\enems1.h 1
..\utils\eneexp2.exe enems2.ene ..\dev\assets\enems2.h 2
echo Making map
cd ..\map
..\utils\packmap.exe mapa0.map ..\dev\assets\mapa0.h 4 6 15 0
..\utils\packmap.exe mapa1.map ..\dev\assets\mapa1.h 4 6 15 1
..\utils\packmap.exe mapa2.map ..\dev\assets\mapa2.h 4 6 15 2
rem cd ..\script
rem ..\utils\mscnes script.spt 24
rem copy mscnes.h ..\dev\assets\ > nul
rem copy scripts.s ..\dev > nul
cd ..\dev

:compilestage
cc65 -Oi game.c --add-source
ca65 crt0.s -o crt0.o
ca65 game.s
rem ca65 scripts.s
rem ld65 -v -C nes.cfg -o cart.nes crt0.o game.o scripts.o runtime.lib
ld65 -v -C nes.cfg -o cart.nes crt0.o game.o runtime.lib -Ln labels.txt

del *.o
del game.s
