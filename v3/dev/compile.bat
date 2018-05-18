@echo off
if [%1]==[justcompile] goto :justcompile

echo Generating Pals
..\utils\mkts.exe mode=pals pals=..\gfx\palts1A.png out=work\palbg0.h label=palts0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1B.png out=work\palbg1.h label=palts1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1C.png out=work\palbg2.h label=palts2 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1D.png out=work\palbg3.h label=palts3 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1E.png out=work\palbg4.h label=palts4 silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltsT.png out=work\palbgT.h label=paltitle silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1A.png out=work\palfg0.h label=palss0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1B.png out=work\palfg1.h label=palss1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1C.png out=work\palfg2.h label=palss2 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palcuts1.png out=work\palcuts.h label=palcuts silent
copy /b work\palbg0.h + work\palbg1.h + work\palbg2.h + work\palbg3.h + work\palbg4.h + work\palbgT.h + work\palfg0.h + work\palfg1.h + work\palfg2.h + work\palcuts.h assets\palettes.h > nul

echo Exporting chr
cd ..\gfx

..\utils\mkts.exe mode=scripted in=cut_patterns.spt out=..\dev\tileset.chr silent

cd ..\dev\

echo Exporting enems
cd ..\enems
..\utils\eneexp3c.exe level0.ene ..\dev\assets\enems0.h 0 1
..\utils\eneexp3c.exe level1.ene ..\dev\assets\enems1.h 1 1
..\utils\eneexp3c.exe level2.ene ..\dev\assets\enems2.h 2 1
..\utils\eneexp3c.exe level3.ene ..\dev\assets\enems3.h 3 1
..\utils\eneexp3c.exe level4.ene ..\dev\assets\enems4.h 4 1 nohotspots

echo Making map 
cd ..\map
..\utils\rle44map.exe in=level0.map out=..\dev\assets\map0.h size=4,6 prefix=0 tlock=15 nodecos scrsizes fixmappy
..\utils\rle44map.exe in=level1.map out=..\dev\assets\map1.h size=4,6 prefix=1 tlock=15 nodecos scrsizes fixmappy
..\utils\rle44map.exe in=level2.map out=..\dev\assets\map2.h size=4,6 prefix=2 tlock=15 nodecos scrsizes
..\utils\rle44map.exe in=level3.map out=..\dev\assets\map3.h size=12,2 prefix=3 tlock=15 nodecos scrsizes fixmappy
..\utils\rle44map.exe in=level4.map out=..\dev\assets\map4.h size=3,4 prefix=4 nodecos scrsizes

rem echo Making texts
rem cd ..\texts
rem ..\utils\texts2array.exe dialogue.txt ..\dev\assets\texts.h texts0 19

cd ..\dev

rem ..\utils\msc4nes.exe in=..\script\yun.spt out=..\dev\engine\mscnes.h maxpants=30 mapadjust=1

:justcompile

ca65 crt0.s -o crt0.o

cc65 -Oi game.c --add-source -D STANDALONE
ca65 game.s
ld65 -v -C nes.cfg -o yun_v3.nes crt0.o game.o runtime.lib -Ln labels.txt

del game.s
del game.o
del crt0.o
