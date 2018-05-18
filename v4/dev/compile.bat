@echo off
if [%1]==[justcompile] goto :justcompile

del work\*.* /q > nul

echo Generating Pals
..\utils\mkts.exe mode=pals pals=..\gfx\palts1A.png out=work\palbg0.h label=palts0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1B.png out=work\palbg1.h label=palts1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1C.png out=work\palbg2.h label=palts2 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1D.png out=work\palbg3.h label=palts3 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1E.png out=work\palbg4.h label=palts4 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1F.png out=work\palbg5.h label=palts5 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palts1G.png out=work\palbg6.h label=palts6 silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltsT.png out=work\palbgT.h label=paltitle silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1A.png out=work\palfg0.h label=palss0 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1B.png out=work\palfg1.h label=palss1 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palss1C.png out=work\palfg2.h label=palss2 silent
..\utils\mkts.exe mode=pals pals=..\gfx\palcuts1.png out=work\palcuts.h label=palcuts silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltsending.png out=work\paltsending.h label=paltsending silent
..\utils\mkts.exe mode=pals pals=..\gfx\palssending.png out=work\palssending.h label=palssending silent
copy /b work\pal*.h assets\palettes.h > nul

echo Exporting chr
cd ..\gfx

..\utils\mkts.exe mode=scripted in=cut_patterns.spt out=..\dev\tileset0.chr silent
..\utils\mkts.exe mode=scripted in=cut_patterns_extra.spt out=..\dev\tileset3.chr silent

cd ..\dev\

echo Exporting enems
cd ..\enems
..\utils\eneexp3c.exe level0.ene ..\dev\assets\enems0.h 0 1
..\utils\eneexp3c.exe level1.ene ..\dev\assets\enems1.h 1 1
..\utils\eneexp3c.exe level2.ene ..\dev\assets\enems2.h 2 1
..\utils\eneexp3c.exe level3.ene ..\dev\assets\enems3.h 3 1
..\utils\eneexp3c.exe level4.ene ..\dev\assets\enems4.h 4 1 nohotspots
..\utils\eneexp3c.exe level5.ene ..\dev\assets\enems5.h 5 1
..\utils\eneexp3c.exe level6.ene ..\dev\assets\enems6.h 6 1

echo Making map 
cd ..\map
..\utils\rle44mapchrrom.exe in=maplist.txt bin=..\dev\work\mapchr.bin out=..\dev\assets\chr-rom-maps.h

cd ..\dev
copy work\mapchr.bin.1 tileset1.chr > nul
copy work\mapchr.bin.2 tileset2.chr > nul 

:justcompile

ca65 crt0-CNROM.s -o crt0.o

cc65 -Oi game.c --add-source
ca65 game.s
ld65 -v -C nes-CNROM.cfg -o yun_v4.nes crt0.o game.o runtime.lib -Ln labels.txt

del game.s
del game.o
del crt0.o
