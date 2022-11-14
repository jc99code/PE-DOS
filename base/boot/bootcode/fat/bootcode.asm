

;
; BOOTCODE.ASM
;
; This file is licensed under the BSD 2-Clause License. 
;


INIT_ADDR		EQU 7c00h
ROOTDIR_ADDR	EQU 600h
BOOTLDR_LOADSEG	EQU 1000h

		use16
		org INIT_ADDR

; Skip file system descriptor table and continue boot sector.
		jmp		SHORT main
		nop

		DB "        " 
bpb_BytesPerSector:		
		DW 512
bpb_SectorsPerCluster:	
		DB 1
		DW 1	        
bpb_NumFATs:			
		DB 2
bpb_RootDirCnt:	
		DW 224
		DW 2880
		DB 0F0h
bpb_SectorsPerFAT:		
		DW 9
bpb_SectorsPerTrack:	
		DW 18
bpb_NumHeads:			
		DW 2
		DD 0
		DD 0
		DW 0
		DB 41
		DD 0
		DB "           "
		DB "FAT     "

;
main:
		xor		ax, ax
		cli
		mov		ss, ax
		mov		sp, WORD INIT_ADDR
		mov		bp, sp
		sti
		mov		ds, ax
		mov		es, ax
		mov		ax, 1
		mov		cx, WORD [bpb_SectorsPerFAT]
		lea		bx, [FAT]
		call	ReadSectors
		mov		ax, 19
		mov		cx, 14
		mov		bx, WORD ROOTDIR_ADDR
		push	bx
		call	ReadSectors
		
		
;
; The boot sector requires that BOOTLDR be located before all other files on the volume.
;
; CX = file capacity of the volume.
; SI = filename string
; DI = address of the root directory structure
;
		
FindFile:
		pop		di
		mov		cx, WORD [bpb_RootDirCnt]
FindFileNextEntry:
		pusha
		mov		cx, 11
		lea		si, [FileName]
		repz	cmpsb
		popa
		jnz		SHORT HandleStartupMessage
		mov		si, WORD [es:di + 1ah]


;
; Read a file into memory.
;
; The general algorith used here is derived from "alexfru's" BootProg FAT12 boot sector.
; The main difference here is that 'ReadCluster' and 'ReadSector' are meshed into a single function.
;
; BootProg: https://github.com/alexfru/BootProg/blob/master/boot12.asm
;
; AX:DX = 
; CX =
; ES:[BX] =
;

ReadFile:
		mov		ax, 33
		xor		dx, dx
		mov		cx, 64
		push	WORD BOOTLDR_LOADSEG
		pop		es
		mov		bx, bp
ReadFileNextCluster:
		call	ReadSectors
IsEven:
	

; The file is now in memory, so transfer CPU execution to that memory segment.
ReadFileDone:
		push	es
		push	bp		; WORD INIT_ADDR
		retf
		
ReadSectors:
		pusha
		mov		di, 5
ReadSectorsNextSector:
		pusha
		div		WORD [bpb_SectorsPerTrack]
		mov		cx, dx
		inc		cx
		xor		dx, dx
		div		WORD [bpb_NumHeads]
		mov		ch, al
		shl		ah, 6
		or		cl, ah
		mov		dh, dl
		xor		dl, dl
		mov		ax, 201h
		int		13h
		jnc		SHORT ReadSectorsNextSectorDone
		popa
		dec		di
		jnz		SHORT ReadSectorsNextSector
		
; SI must be the ddress of character string to be displayed.
HandleStartupMessage:
		mov		ah, 0eh
		lea		si, [StartupMessage]
PutChar:
		lodsb
		or		al, 0
		jz		SHORT BE_Loop
		int		10h
		jmp		PutChar
BE_Loop:
		cli
		hlt
		
ReadSectorsNextSectorDone:
		popa
		dec		cx
		jz		SHORT ReadSectorsDone
		add		bx, WORD [bpb_BytesPerSector]
		add		ax, 1
		adc		dx, 0
		jmp		SHORT ReadSectorsNextSector
ReadSectorsDone:
		popa
		ret
			
FileName:			
		DB "BOOTLDR    ", 0
StartupMessage:	
		DB "DISK BOOT FAILURE - INSERT SYSTEM DISK AND PRESS ANY KEY", 0

		times 510 - ($ - $$) DB 0
		
; END BOOTCODE
		DW 0aa55h

FAT:
