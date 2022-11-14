
#include <bl.h>

#define MAX_INTERRUPTS 256

// idt.asm
extern PFN_X86_ISRFUNC _ISRTBL[];

static IDT32 BootLoaderIDT[MAX_INTERRUPTS];
static IDT32_REGISTER R_IDT32;
static PFN_X86_IRQFUNC IrqHandlers[16];
static WORD PicMask = 0xff;


void 
InterruptHandler(X86_REGS *regs)
{
    PFN_X86_ISRFUNC IsrFunc = _ISRTBL[regs->InterruptNumber];
    
    if (IsrFunc)
    {
        IsrFunc(regs);
    }
    else
    {
    }
}

static
void 
CreateInterruptDescriptor(DWORD Id, void *pHandler, DWORD Flags)
{
	IDT32 *const desc = &BootLoaderIDT[Id];

	desc->IsrAddressLow = (UINT_PTR)pHandler & 0xffff;	
	desc->Selector = 8;
	desc->Unused = 0;
	desc->Flags = Flags;	
	desc->IsrAddressHigh = ((UINT_PTR)pHandler >> 16) & 0xffff;
}

void 
IoWait(void)
{
    outportb(0x80, 0);
}

static
void 
RemapPIC(DWORD offset1, DWORD offset2)
{
    outportb(X86_PIC1_COMMAND, X86_ICW1_ICW4 | X86_ICW1_INIT);
    IoWait();
    outportb(X86_PIC2_COMMAND, X86_ICW1_ICW4 | X86_ICW1_INIT);
    IoWait();

    outportb(X86_PIC1_DATA, offset1);
    IoWait();
    outportb(X86_PIC2_DATA, offset2);
    IoWait();

    outportb(X86_PIC1_DATA, 4);
    IoWait();
    outportb(X86_PIC2_DATA, 2);
    IoWait();

    outportb(X86_PIC1_DATA, X86_ICW4_8086);
    IoWait();
    outportb(X86_PIC2_DATA, X86_ICW4_8086);
    IoWait();
    
    outportb(X86_PIC1_DATA, 0);
    IoWait();
    outportb(X86_PIC2_DATA, 0);
    IoWait();
}


void RegisterInterruptRequestHandler(DWORD IrqId, PFN_X86_IRQFUNC IrqFunc)
{
    IrqHandlers[IrqId] = IrqFunc;
}

static
void
InterruptRequestHandler(X86_REGS *regs)
{
    DWORD irq = regs->InterruptNumber - X86_PIC_BASE;
    PFN_X86_IRQFUNC IrqFunc = IrqHandlers[irq];
    
    if (IrqFunc)
    {
        IrqFunc(regs);
    }
    else
    {
    }
    
    SendEOI(irq);
}

void 
SetIRQMask(BYTE IrqLine)
{
	WORD port;
	BYTE value;
	
	if (IrqLine < 8)
	{
		port = X86_PIC1_DATA;
	}
	else
	{
		port = X86_PIC2_DATA;
		IrqLine -= 8;
	}
	
	value = inportb(port) | (1 << IrqLine);
	outportb(port, value);
}

void 
ClearIRQMask(BYTE IrqLine)
{
	WORD port;
	BYTE value;
	
	if (IrqLine < 8)
	{
		port = X86_PIC1_DATA;
	}
	else
	{
		port = X86_PIC2_DATA;
		IrqLine -= 8;
	}
	
	value = inportb(port) | ~(1 << IrqLine);
	outportb(port, value);
}

void 
SendEOI(BYTE Irq)
{
    if (Irq >= 8)
    {
        outportb(X86_PIC2_COMMAND, X86_PIC_EOI);
    }
    
    outportb(X86_PIC1_COMMAND, X86_PIC_EOI);
}


static 
WORD 
GetIRQRegister(DWORD Ocw3)
{
    outportb(X86_PIC1_COMMAND, Ocw3);
    outportb(X86_PIC2_COMMAND, Ocw3);
    
    return (inportb(X86_PIC2_COMMAND) << 8) + inportb(X86_PIC1_COMMAND);
}

WORD 
GetInterruptRequestRoutine(void)
{
    return GetIRQRegister(X86_PIC_READ_IRR);
}

WORD 
GetInterruptServiceRoutine(void)
{
    return GetIRQRegister(X86_PIC_READ_ISR);
}


//
// The REAL initialization code begins HERE.
//

void 
InitializeInterrupts(void)
{
	R_IDT32.Limit = (WORD)sizeof(IDT32) * MAX_INTERRUPTS - 1;
	R_IDT32.Base = (UINT_PTR)&BootLoaderIDT[0];

    // Zero the entire descriptor table.
    // This way, no bogus "interrupts" will be called due to any (potentially) garbage memory.
    memset(BootLoaderIDT, 0, sizeof(IDT32) * MAX_INTERRUPTS);

    DWORD i;
    for (i = 0; i < 32; i++) 
    {
        CreateInterruptDescriptor(i, _ISRTBL[i], X86_IDT_INTERRUPT);
    }

    // The boot loader initializes every descriptor.
    // The main reason for this is, the boot loader simply needs a PoLR and stream-lined opportunity
    // to load the operating system. 
    //
    // It really doesn't matter what's what here. Initializing everything uses less code, which is
    // very nice, considering this OS runs on a floppy-disk.
    for (i = 32; i < 256; i++) 
    {
        CreateInterruptDescriptor(i, _ISRTBL[i], X86_IDT_INTERRUPT);
    }

    // Install the descriptor table, replacing the one from real-mode.
    __asm
    {
        lidt [R_IDT32]
    }
    
    RemapPIC(X86_PIC_BASE, X86_PIC_BASE + 8);

    for (i = 0; i < 16; ++i)
    {
        // Each IRQ involves the same service routine, but then is later dispatched to "sub-handlers"
        // that handler each IRQ in detail.
        _ISRTBL[X86_PIC_BASE + i] = InterruptRequestHandler;
    }
    
    // NMI can finally be enabled.
    __asm
    {
        sti
    }
}
