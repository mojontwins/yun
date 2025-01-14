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
..\utils\mkts.exe mode=pals pals=..\gfx\palts1H.png out=work\palbg7.h label=palts7 silent
..\utils\mkts.exe mode=pals pals=..\gfx\paltsL.png out=work\palbgL.h label=pallightning silent
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
..\utils\eneexp3c.exe level4.ene ..\dev\assets\enems4.h 4 1
..\utils\eneexp3c.exe level5.ene ..\dev\assets\enems5.h 5 1
..\utils\eneexp3c.exe level6.ene ..\dev\assets\enems6.h 6 1
..\utils\eneexp3c.exe level7.ene ..\dev\assets\enems7.h 7 1

echo Making map 
cd ..\map
..\utils\rle44mapchrrom.exe in=maplist.txt bin=..\dev\work\mapchr.bin out=..\dev\assets\chr-rom-maps.h

cd ..\dev
copy work\mapchr.bin.1 tileset1.chr > nul
copy work\mapchr.bin.2 tileset2.chr > nul 

:justcompile

ca65 crt0-CNROM.s -o crt0.o

set STARTTIME=%TIME%
cc65 -Oi game.c --add-source
set ENDTIME=%TIME%

rem measure time http://stackoverflow.com/questions/9922498/calculate-time-difference-in-windows-batch-file
for /F "tokens=1-4 delims=:.," %%a in ("%STARTTIME%") do (
   set /A "start=(((%%a*60)+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100"
)
for /F "tokens=1-4 delims=:.," %%a in ("%ENDTIME%") do (
   set /A "end=(((%%a*60)+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100"
)
set /A elapsed=end-start
set /A hh=elapsed/(60*60*100), rest=elapsed%%(60*60*100), mm=rest/(60*100), rest%%=60*100, ss=rest/100, cc=rest%%100
if %hh% lss 10 set hh=0%hh%
if %mm% lss 10 set mm=0%mm%
if %ss% lss 10 set ss=0%ss%
if %cc% lss 10 set cc=0%cc%

set DURATION=%hh%:%mm%:%ss%,%cc%

echo cc65 se ha tirado fumando exactamente %DURATION% 
echo en un %PROCESSOR_IDENTIFIER% con %NUMBER_OF_PROCESSORS% nucleos.
ca65 game.s
ld65 -v -C nes-CNROM.cfg -o yun_v5.nes crt0.o game.o runtime.lib -Ln labels.txt


del game.s
del game.o
del crt0.o
