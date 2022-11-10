
#ifndef _BL_H_
#define _BL_H_

#define B_DECLSPEC_NORETURN __declspec(noreturn)

void VgaWriteLine(int color, const char *string);

#define DISK_ROOTDIR 	0x00000600
#define DISK_FAT		0x00007e00

#include <basedef.h>

#define IRET	\
	__asm		\
	{			\
		iret	\
	}

#define DECLSPEC_INTERRUPT_HANDLER __declspec(naked)

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

typedef struct REGS {
	//UINT32 EAX;
	//UINT32 EBX;
	//UINT32 ECX;
	//UINT32 EDX;
	//UINT32 ESI;
	//UINT32 EDI;
	//UINT32 ESP;
	//UINT32 EBP;
	//UINT32 SS;
	//UINT32 DS;
	//UINT32 ES;
	//UINT32 FS;
	//UINT32 GS;
	UINT32 EFlags;
	UINT32 CS;
	UINT32 EIP;
	UINT32 ErrorCode;
} REGS;

#pragma options align=reset


typedef void (* PFN_BOOTLDR_ISR_HANDLER)(void);

void CreateInterruptDescriptor(UINT32 id, PFN_BOOTLDR_ISR_HANDLER isr, UINT8 flags);
void SetIRQMask(UINT8 IrqLine);
void ClearIRQMask(UINT8 IrqLine);
void RemapPIC(void);
void SetInterruptsTable(void);

extern __forceinline UINT8 inportb(UINT16 port);
extern __forceinline void outportb(UINT16 port, UINT8 value);

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

#define FDC_MT 0x80
#define FDC_MF 0x40
#define FDC_SK 0x20

#endif
