
#include <bl.h>

static
void
IrqHandler(X86_REGS *regs)
{
}

void
InitializeTimer(void)
{
    RegisterInterruptRequestHandler(X86_IRQ_TIMER, IrqHandler);
}
