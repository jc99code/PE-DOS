@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION

SET "BASEPATH=C:\Users\HeatS\Desktop\PE-DOS\"
SET "BOOTDISK=%BASEPATH%\BOOTDISK.img"

START "" /B /WAIT "D:\MinGW\bin\mingw32-make.exe"
IF !ERRORLEVEL! == 0 GOTO :DONE

:DONE

IF EXIST "%BOOTDISK%" (
	ECHO Setting up "%BOOTDISK%"...
	
	imdisk -a -f "%BOOTDISK%" -s 1440K -m A:
	
	PUSHD "%BASEPATH%\base\boot\bldr"
	CALL SYS.BAT
	POPD
	
	PUSHD "%BASEPATH%\base\system"
	CALL SYS.BAT
	POPD

	imdisk -D -m A:
) ELSE (
	ECHO The virtual disk image "%BOOTDISK%" is missing.
)

ECHO Build completed
ENDLOCAL

EXIT /B 1
