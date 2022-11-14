
CC = $(compiler)
CFLAGS = $(bootldr-compiler-switches)

devices\%.obj: devices\%.c
	$(CC) $(CFLAGS) /Fo$@ $<

