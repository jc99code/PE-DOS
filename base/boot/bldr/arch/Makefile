
CC = $(compiler)
CFLAGS = $(bootldr-compiler-switches)

arch\i386\%.obj: arch\i386\%.c
	$(CC) $(CFLAGS) /Fo$@ $<


arch\i386\idtasm.obj: arch\i386\idt.asm
	$(asm) -f win -o $@ $<


