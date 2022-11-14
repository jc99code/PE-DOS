
#ifndef _BL_H_
#define _BL_H_

#include <basedef.h>

#define B_DECLSPEC_NORETURN __declspec(noreturn)

#ifndef DECLSPEC_ALIGN
#define DECLSPEC_ALIGN(x) __declspec(align(x))
#endif

typedef void *HANDLE;

void *HeapAlloc(DWORD Size, DWORD AlignBy, DWORD *ppPhysAddr);

typedef struct BPB {
    BYTE Jump[3];
    char OEMLabel[8];
    WORD BytsPerSec;
    BYTE SecPerClust;
    WORD RsvdSecCnt;
    BYTE NumFats;
    WORD RootDirEnts;
    WORD TotSec;
    BYTE Media;
    WORD TotSec16;
    WORD SecPerTrk;
    WORD NumHeads;
    DWORD HiddenSectors;
    DWORD TotSec32;
    WORD DriveNo;
    BYTE Sig;
    DWORD VolID;
    char VolLabel[11];
    char FilSyst[8];
} BPB;

typedef struct FAT_BOOTSECT {
    BPB bpb;
    BYTE BootCode[448];
    WORD Sig;
} FAT_BOOTSECT;

typedef struct FAT_DIR {
    char *pFileName;
    BYTE Flags;
    BYTE Reserved0;
    BYTE TimestampSeconds;
    WORD Timestamp;
    WORD Date;
    WORD LastAccessDate;
    WORD StartHigh;
    WORD LastModifyDate0;
    WORD LastModifyDate1;
    WORD StartLow;
    DWORD FileSize;
} FAT_DIR;

#define X86_PD_INDEX(address) ((address) >> 22)
#define X86_PT_INDEX(address) (((address) >> 12) & 0x3ff)

#define X86_PD_PRESENT          0x01
#define X86_PD_READ_WRITE       0x02
#define X86_PD_USER             0x04
#define X86_PD_WRITE_THRU       0x08
#define X86_PD_CACHE_DISABLED   0x10
#define X86_PD_ACCESSED         0x20
#define X86_PD_DIRTY            0x40
#define X86_PD_PAGE_SIZE        0x80
#define X86_PD_GLOBAL           0x100
#define X86_PD_ATTRIB_TABLE     0x2000
#define X86_PD_FRAME            0x7FFFF000

#define X86_PT_PRESENT          0x01
#define X86_PT_READ_WRITE       0x02
#define X86_PT_USER             0x04
#define X86_PT_WRITE_THRU       0x08
#define X86_PT_CACHE_DISABLED   0x10
#define X86_PT_ACCESSED         0x20
#define X86_PT_DIRTY            0x40
#define X86_PT_ATTRIB_TABLE     0x80
#define X86_PT_GLOBAL           0x100
#define X86_PT_FRAME            0x7FFFF000

DWORD GetProcessorMode();
DWORD GetProcessorPageFault();
DWORD GetProcessorPagingDirectory();
DWORD GetProcessorOther();

#define X86_IDT_TRAP        0x8f
#define X86_IDT_INTERRUPT   0x8e
#define X86_IDT_TASK        0xee

typedef DWORD PADDRESS;
typedef DWORD VADDRESS;

#define X86_PIC1            0x20
#define X86_PIC1_COMMAND    X86_PIC1
#define X86_PIC1_DATA       X86_PIC1 + 1
#define X86_PIC2            0xA0
#define X86_PIC2_COMMAND    X86_PIC2
#define X86_PIC2_DATA       X86_PIC2 + 1

// A value that signifies the end of an interrupt.
#define X86_PIC_EOI 0x20

#define X86_ICW1_ICW4       0x01
#define X86_ICW1_SINGLE     0x02
#define X86_ICW1_INTERVAL   0x04
#define X86_ICW1_LEVEL      0x08
#define X86_ICW1_INIT       0x10

#define X86_ICW4_8086       0x01
#define X86_ICW4_AUTO_EOI   0x02
#define X86_ICW4_BUF_SLAVE  0x08
#define X86_ICW4_BUF_MASTER 0x0c
#define X86_ICW4_SFNM       0x40

#define X86_PIC_READ_IRR    0x0a
#define X86_PIC_READ_ISR    0x0b

#define X86_PIC_BASE        0x20


#define X86_IRQ_TIMER       0x00
#define X86_IRQ_KEYBOARD    0x01

void
InitializeTimer(void);

void
InitializeKeyboard(void);


void StartPaging(void);

void *GetPhysicalAddress(void *pVirtualAddress);

void CreatePage();
void DeletePage();
void MapPage(void *pPhysicalAddress, void *pVirtualAddress, DWORD Flags);
DWORD FindPage();
void SetPageFlag(DWORD *pPage, DWORD Flag);


extern WORD *pVideoMemory;

extern FAT_BOOTSECT *pBootSector;
extern WORD *pFAT;

void DbgWriteLine(const char *format, ...);

void VgaPutChar(char Char);
void VgaWriteLine(int color, const char *string);

#define DISK_ROOTDIR 	0x00000600
#define DISK_FAT		0x00007e00

#pragma pack(1)

typedef struct IDT32 {
	UINT16	IsrAddressLow;
	UINT16	Selector;
	UINT8	Unused;
	UINT8	Flags;
	UINT16	IsrAddressHigh;
} IDT32;

typedef struct IDT32_REGISTER {
	UINT16 Limit;
	UINT32 Base;
} IDT32_REGISTER;

typedef struct X86_REGS {
    DWORD EDI;
    DWORD ESI;
    DWORD EBP;
    DWORD ESP;
	DWORD EBX;
	DWORD EDX;
	DWORD ECX;
	DWORD EAX;
	DWORD InterruptNumber;
	DWORD ErrorCode;
	DWORD EIP;
	DWORD CS;
	DWORD EFlags;
} X86_REGS;

#pragma options align=reset


typedef void (* PFN_X86_ISRFUNC)(X86_REGS *regs);
typedef void (* PFN_X86_IRQFUNC)(X86_REGS *regs);

void 
InitializeInterrupts(void);

void 
RegisterInterruptRequestHandler(DWORD IrqId, PFN_X86_IRQFUNC IrqFunc);

void 
IoWait(void);

void 
SetIRQMask(BYTE IrqLine);

void 
ClearIRQMask(BYTE IrqLine);

void 
SendEOI(BYTE Irq); // <- TEMPORARY

WORD 
GetInterruptRequestRoutine(void);

WORD 
GetInterruptServiceRoutine(void);


extern BYTE inportb(UINT16 port);
extern void outportb(UINT16 port, BYTE value);


typedef enum FDC_REGS {
    FDC_REG_DOR     = 2,
    FDC_REG_MSR     = 4,
    FDC_REG_FIFO    = 5,
    FDC_REG_CCR     = 7
} FDC_REGS;

typedef enum FDC_COMMANDS {
	FDC_COMMAND_READ_TRACK			= 2,
	FDC_COMMAND_SPECIFY				= 3,
	FDC_COMMAND_GET_DRIVE_STATUS	= 4,
	FDC_COMMAND_WRITE_DATA			= 5,
	FDC_COMMAND_READ_DATA			= 6,
	FDC_COMMAND_RECALIBRATE			= 7,
	FDC_COMMAND_GET_INTERRUPT		= 8,
	FDC_COMMAND_WRITE_DELETED_DATA	= 9,
	FDC_COMMAND_READ_ID				= 10,
	FDC_COMMAND_READ_DELETED_DATA	= 12,
	FDC_COMMAND_FORMAT_TRACK		= 13,
	FDC_COMMAND_DUMPREG				= 14,
	FDC_COMMAND_SEEK				= 15,
	FDC_COMMAND_VERSION				= 16,
	FDC_COMMAND_SCAN_EQUAL			= 17,
	FDC_COMMAND_PERPENDICULAR_MODE	= 18,
	FDC_COMMAND_CONFIGURE			= 19,
	FDC_COMMAND_LOCK				= 20,
	FDC_COMMAND_VERIFY				= 22,
	FDC_COMMAND_SCAN_LOW_OR_EQU		= 25,
	FDC_COMMAND_SCAN_HIGH_OR_EQU	= 29,
} FDC_COMMANDS;

typedef enum FDC_DRIVE_STATE {
    FDC_DRIVE_OFF,
    FDC_DRIVE_ON,
    FDC_DRIVE_WAITING
} FDC_DRIVE_STATE;

#define FDC_MT 0x80
#define FDC_MF 0x40
#define FDC_SK 0x20

#define BPB_BYTEPERSECTOR 512
#define BPB_SECTORSPERCLUSTER 1
#define BPB_NUMFATS 2
#define BPB_ROOTDIRCNT 224
#define BPB_SECTORSPERFAT 9
#define BPB_SECTORSPERTRACK 18
#define BPB_NUMHEADS 2

void GetDriveParams(BPB *bpb);
void Lba2Chs(UINT32 LBA, UINT16 *Cylinder, UINT16 *Head, UINT16 *Sector);

void DetectDrives();
INT ResetDrive();
void SendDriveCommand();
void WaitForDrive();

extern UCHAR KbdUs[];

void DbgDumpException(X86_REGS *regs);
void DebugMemory(void *pMem);

void *memset(void *pMem, DWORD Value, ULONG_PTR Size);

#endif
