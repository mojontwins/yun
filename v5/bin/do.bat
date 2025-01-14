xtrctbin.exe ..\dev\yun_v5.nes prg.bin 16 32768
xtrctbin.exe ..\dev\yun_v5.nes chr32.bin 32784 32768
copy /b chr32.bin + chr32.bin + chr32.bin + chr32.bin chr128.bin
