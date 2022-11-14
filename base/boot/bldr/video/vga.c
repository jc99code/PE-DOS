
#include <bl.h>

WORD *pVideoMemory = NULL;

static INT32 LineNumber = 0;
static INT32 PutCharColumn = 0;

void 
VgaPutChar(char Char)
{
	char *video = (char *)pVideoMemory + PutCharColumn;
  
    *video++ = Char;
    *video++ = 7;
  
    PutCharColumn += 2;
}

void 
VgaWriteLine(int colour, const char *string)
{
	char *video = (char *)(pVideoMemory + (80 * LineNumber));



    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
	
	++LineNumber;
}
