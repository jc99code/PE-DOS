
#include "bl.h"

static int something;
static const char *message = "Hello, world! BOOTLDR has been started...\0";

int so = 234;
static int ass = 5;

B_DECLSPEC_NORETURN
void main()
{
	SetInterruptsTable();
	
	VgaWriteLine(7, "poop1231231231231231213\0");
	VgaWriteLine(7, message);
	
	while (1)
	{
	}
}


UINT8 inportb(UINT16 port)
{
	UINT8 result = 0;
	
	__asm
	{
		mov		dx, port
		in		ax, dx
		mov		[result], al
	}
	
	return result;
}

void outportb(UINT16 port, UINT8 value)
{
	__asm
	{
		mov		al, [value]
		mov		dx, [port]
		out		dx, al
	}
}

