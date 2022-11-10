
#include "bl.h"

#define MAX_INTERRUPTS 256


static __declspec(align(0x10)) IDT32 BootLoaderIDT[MAX_INTERRUPTS];
static IDT32_REGISTER R_IDT32;
/**
 * implementation
 */
void CreateInterruptDescriptor(UINT32 id, PFN_BOOTLDR_ISR_HANDLER isr, UINT8 flags)
{
	IDT32 *desc = &BootLoaderIDT[id];
	
	desc->IsrAddressLow = (UINT32)isr & 0xffff;	
	desc->Selector = 8;		// Using the code selector defined in x86realm.bin
	desc->Unused = 0;		// <- magic(k)!
	desc->Flags = flags;	
	desc->IsrAddressHigh = ((UINT32)isr >> 16) & 0xffff;
}


/**
 * implementation
 */
void SetIRQMask(UINT8 IrqLine)
{
	UINT16 port;
	UINT8 value;
	
	if (IrqLine < 8)
	{
		port = 0x21;
	}
	else
	{
		port = 0xa1;
		IrqLine -= 8;
	}
	
	value = inportb(port) | (1 << IrqLine);
	outportb(port, value);
}


/**
 * implementation
 */
void ClearIRQMask(UINT8 IrqLine)
{
	UINT16 port;
	UINT8 value;
	
	if (IrqLine < 8)
	{
		port = 0x21;
	}
	else
	{
		port = 0xa1;
		IrqLine -= 8;
	}
	
	value = inportb(port) | ~(1 << IrqLine);
	outportb(port, value);
}


/**
 * implementation
 */
void RemapPIC(void)
{
	outportb(0x20, 0x11);
	outportb(0xa0, 0x11);
	outportb(0x80, 0);

	outportb(0x21, 0x20);
	outportb(0xa1, 0x28);
	outportb(0x80, 0);

	outportb(0x21, 0x04);
	outportb(0xa1, 0x02);
	outportb(0x80, 0);

	outportb(0x21, 0x01);
	outportb(0xa1, 0x01);
	outportb(0x80, 0);
}


static void InitializeExceptionHandlers(void)
{

}

/**
 * implementation
 */
void SetInterruptsTable(void)
{
	//RemapPIC();
	
	R_IDT32.Limit = (sizeof(IDT32) * MAX_INTERRUPTS) - 1;
	R_IDT32.Base = (UINT32)&BootLoaderIDT[0];
}

