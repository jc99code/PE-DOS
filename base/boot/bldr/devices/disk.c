
#include <bl.h>

#define FDC_BASE    0x3f0
#define FDC_IRQ     6

static const char *DriveTypes[] = 
{
    "NONE\0",
    
    "360KB 5.25\0",
    "1.2MB 5.25\0",
    "720KB 3.5\0",
    
    "1.44MB 3.5\0",
    "2.88MB\0",
    
    "UNKNOWN\0",
    "UNKNOWN\0"
};

static INT Ticks = 0;
static INT State = 0; 


/**
 * implementation
 */
void DetectDrives()
{
    outportb(0x70, 0x10);
    DWORD drives = inportb(0x71);
}


/**
 * implementation
 */
INT ResetDrive()
{
    outportb(FDC_BASE + FDC_REG_DOR, 0);
    outportb(FDC_BASE + FDC_REG_DOR, 0xc0);
    
    return 0;
}


/**
 * implementation
 */
void SendDriveCommand()
{
}


/**
 * implementation
 */
void WaitForDrive()
{
}
