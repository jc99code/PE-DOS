
COPY X86REALM.BIN + BOOTLDR A:\BOOTLDR

IF NOT ERRORLEVEL 0 GOTO :DONE_ERROR

EXIT /B 0

:DONE_ERROR

EXIT /B 1
