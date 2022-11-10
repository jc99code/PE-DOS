
#include "bl.h"

static INT32 LineNumber = 0;

/**
 * implementation
 */
void VgaWriteLine(int colour, const char *string)
{
	char *video = (char *)(0xB8000 + ((80 * 2) * LineNumber));
	int numCharsShown = 0;

    while( *string != 0 )
    {
		++numCharsShown;
		
		if (numCharsShown > 80)
		{
			++LineNumber;
			numCharsShown = 0;
		}
		
        *video++ = *string++;
        *video++ = colour;
    }
	
	++LineNumber;
}
