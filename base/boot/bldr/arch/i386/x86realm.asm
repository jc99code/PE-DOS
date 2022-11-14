
INIT_ADDR EQU 7c00h

		use16
		org INIT_ADDR
		
main:
		mov		ax, cs
		cli
		mov		ss, ax
		mov		sp, WORD INIT_ADDR
		mov		bp, sp
		sti
		mov		ds, ax
		mov		es, ax
		mov		ax, 3
		int		10h
		mov		ah, 1
		xor		cx, cx
		int 	10h

InitializeHardware:
		cli

SetGDT:
		lgdt	[GDT_PTR]
SetGDTDone:
		mov		eax, cr0
		or		eax, 1
		mov		cr0, eax
		jmp		DWORD 8h:(10000h + ResetProcessor)
		nop

GDT:
		DD 0h
		DD 0h
GDT_BOOTLDR_CODE:
		DW 0ffffh
		DW 0h
		DB 0h
		DB 10011010b
		DB 11001111b
		DB 0h
GDT_BOOTLDR_DATA:
		DW 0ffffh
		DW 0h
		DB 0h
		DB 10010010b
		DB 11001111b
		DB 0h
GDT_END:
GDT_PTR:
		DW GDT_END - GDT - 1
		DD 10000h + GDT

		use32

ResetProcessor:
		mov		ax, 10h
		mov		ss, ax
		mov		ds, ax
		mov		es, ax
		mov		fs, ax
		mov		gs, ax
		mov		esp, 0x7ffff
		mov		ebp, esp

main32:

EnableA20:
EnableA20KeyboardController:
        call    EnableA20KeyboardControllerWait1
        mov     al, 0adh
        out     64h, al
        call    EnableA20KeyboardControllerWait1
        mov     al, 0d0h
        out     64h, al
        call    EnableA20KeyboardControllerWait2
        in      al, 60h
        push    eax
        call    EnableA20KeyboardControllerWait1
        mov     al, 0d1h
        out     64h, al
        call    EnableA20KeyboardControllerWait1
        pop     eax
        or      al, 2
        out     60h, al
        call    EnableA20KeyboardControllerWait1
        mov     al, 0aeh
        out     64h, al
        call    EnableA20KeyboardControllerWait1
        jmp		SHORT EnableA20Done
EnableA20KeyboardControllerWait1:
        in      al, 64h
        test    al, 2
        jnz     EnableA20KeyboardControllerWait1
        ret
EnableA20KeyboardControllerWait2: 
		in      al, 64h
		test    al, 1
		jz      EnableA20KeyboardControllerWait2
EnableA20Done:

RunOS:
		mov		ebx, 17e00h
		mov		eax, 200h
		add		ebx, eax
		jmp		ebx
		
IsA20Enabled:
		ret

		times 510 - ($ - $$) DB 0
		DW 0aa55h
		
