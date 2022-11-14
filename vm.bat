@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION

SET "EMULATION_SOFTWARE=D:\Program Files (x86)\qemu\qemu-system-i386.exe"

"%EMULATION_SOFTWARE%" -accel tcg,thread=single -cpu coreduo -m 128 -no-reboot -fda BOOTDISK.img -vga std -monitor stdio

PAUSE

ENDLOCAL
