
#include <bl.h>

static
void
IrqHandler(X86_REGS *regs)
{
}

void
InitializeKeyboard(void)
{
    RegisterInterruptRequestHandler(X86_IRQ_KEYBOARD, IrqHandler);
}
