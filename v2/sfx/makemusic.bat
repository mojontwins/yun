@echo off
text2data.exe mus_game0.txt -ca65  -insonly
del m_instruments.s > nul
ren mus_game0.s m_instruments.s
text2data.exe mus_game0.txt -ca65  -noins
text2data.exe mus_game1.txt -ca65  -noins
text2data.exe mus_game2.txt -ca65  -noins
text2data.exe mus_cuts.txt -ca65  -noins
text2data.exe mus_title.txt -ca65  -noins
copy *.s ..\dev >nul
echo DONE CABRONE
