
include $(BASEPATH)\include\make\sdktools.inc

compiler-defines = \
	/D HOST_MACHINE_TARGET_I386

compiler-header-include-paths = \
	/I $(BASEPATH)\sdk\include \
	/I $(BASEPATH)\public\sdk\include \
	/I include
    
compiler-undefines =

compiler-llvm-clang-switches = \
	-fno-builtin \
	-fno-lto \
	-fms-compatibility \
	-fms-extensions \
	-m32 \
	-nobuiltininc

compiler-switches = \
	$(compiler-llvm-clang-switches) \
	$(compiler-header-include-paths) \
	$(compiler-defines) \
	$(compiler-undefines) \
	/TC \
	/c \
	/GF \
	/GS- \
	/openmp- \
	/Od \
	/Obi \
	/Oi- \
	/X \
	/Zc:wchar_t \
	/ZI \
	/Zp4

linker-symbol-include-paths =

linker-switches = \
	$(linker-symbol-include-paths) \
	/BASE:0x17e00 \
	/FILEALIGN:0x80 \
	/ALIGN:0x80 \
	/ENTRY:main \
	/DYNAMICBASE:NO	\
	/INCREMENTAL:NO	\
	/NODEFAULTLIB \
	/OPT:NOREF \
	/OPT:NOICF \
	/SUBSYSTEM:NATIVE \
	/MACHINE:X86 \
	/SAFESEH:NO \
	/NXCOMPAT:NO
   
bootldr-compiler-switches := $(compiler-switches)
bootldr-linker-switches := $(linker-switches)

SOURCES = \
	main.obj \
	arch\i386\a20.obj \
	arch\i386\int.obj \
    arch\i386\idtasm.obj \
	arch\i386\paging.obj \
	devices\disk.obj \
	devices\keyboard.obj \
	devices\pit.obj \
    fs\fastfat.obj \
	video\vga.obj

BIN = BOOTLDR

all: arch\i386\x86realm.bin $(BIN)
	
clean:

.PHONY: all clean

$(BIN): $(SOURCES)
	$(linker) $(bootldr-linker-switches) /OUT:$@ $^

%.obj: %.c
	$(compiler) $(bootldr-compiler-switches) /Fo$@ $<

%.obj: %.asm
	$(asm) -f win -o $@ $<

include arch\Makefile
include devices\Makefile
include fs\Makefile
include video\Makefile
	
arch\i386\x86realm.bin: arch\i386\x86realm.asm
	$(asm) -f bin -o $@ $<

