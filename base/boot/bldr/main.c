
#include <bl.h>

static int something;
static const char *message = "BOOTLDR\0";

int so = 234;
static int ass = 5;

FAT_BOOTSECT *pBootSector = NULL;
WORD *pFAT = NULL;

static void TestStartKrnl386()
{
}


static
void
InitializeInterruptRequests()
{
    InitializeTimer();
    InitializeKeyboard();
}

B_DECLSPEC_NORETURN
void main()
{
    pVideoMemory = (WORD *)0xb8000;

    InitializeInterrupts();
    InitializeInterruptRequests();
    
    __asm
    {

        //int 0x5
        //int 0x6
        //int 0x10
        //int 0x30
        //
        //int 0x21
        //
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x21
        //int 0x24

    }

    while (1)
    {
    }
}


/**
 * implementation
 */
DWORD GetProcessorMode()
{
    DWORD result = 0;
    
    __asm
    {
    }
    
    return result;
}


/**
 * implementation
 */
DWORD GetProcessorPageFault()
{
    DWORD result = 0;
    
    __asm
    {
    }
    
    return result;
}


/**
 * implementation
 */
DWORD GetProcessorPagingDirectory()
{
    DWORD result = 0;
    
    __asm
    {
    }
    
    return result;
}


/**
 * implementation
 */
DWORD GetProcessorOther()
{
    DWORD result = 0;
    
    __asm
    {
    }
    
    return result;
}


/**
 * implementation
 */
BYTE inportb(UINT16 port)
{
	BYTE result = 0;
	
	__asm
	{
		mov		dx, port
		in		ax, dx
		mov		[result], al
	}
	
	return result;
}


/**
 * implementation
 */
void outportb(UINT16 port, BYTE value)
{
	__asm
	{
		mov		al, [value]
		mov		dx, [port]
		out		dx, al
	}
}

static INT_PTR HeapPtr = 0x100000;


/**
 * implementation
 */
void *HeapAlloc(DWORD Size, DWORD AlignBy, DWORD *pPhysAddr)
{
    if (AlignBy == 1 && (HeapPtr & 0xfffff000))
    {
        HeapPtr &= 0xfffff000;
        HeapPtr += 0x1000;
    }
    
    if (pPhysAddr)
    {
        *pPhysAddr = HeapPtr;
    }
    
    INT_PTR TempHeapPtr = HeapPtr;
    HeapPtr += Size;
    
    return (void *)TempHeapPtr;
}





void *memset(void *pMem, DWORD Value, ULONG_PTR Size)
{
    ULONG_PTR i;
    BYTE *pTempMem = (BYTE *)pMem;
 
    for (i = 0; i < Size; ++i)
    {
        pTempMem[i] = Value;
    }
    
    return pMem;
}




void DbgWriteLine(const char *format, ...)
{
}
