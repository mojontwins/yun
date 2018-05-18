Yun
===

I keep working in Yun from time to time, enhancing the game and making it lower and better balanced.

Different versions
------------------

- Yun v1 is lost. It was like v2 but without a *Johnny Limite* mode.
- Yun v2 includes 3 levels and the *Johnny Limite* mode, accessed by pressing DOWN+START on the title screen.
- Yun v3 was ported to MK2_NES and includes 5 levels.
- Yun v4 was extended to CN-ROM and includes 7 levels.

How to build
------------

Yun v2 is built upon cc65 v2.13, the original neslib and famitone 1. You need to grab cc65 v2.13 and add its `bin` folder to the system PATH. You can alternatively run `v2/dev/setenv.bat` (edit it to fix the path where you have cc65 v2.13 installed).

Yun v3 & v4 are built upon cc65 v2.15 (or newer), the latest neslib and famitone 2. Grab the latest cc65 and add its `bin` folder to the system PATH. You can alternatively run `v3/dev/setenv.bat` or `v4/dev/setenv.bat` (edit it to fix the path where you have cc65 v2.15 (or newer) installed).

Once the correct cc65 version is installed and configured, enter the `/dev/` folder of the version you want to compile, then run:

`compile.bat`

