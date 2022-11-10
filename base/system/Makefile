
include $(BASEPATH)\include\make\sdktools.inc

compiler-defines = \
	/D HOST_MACHINE_TARGET_I386

compiler-header-include-paths = \
	/I $(BASEPATH)\sdk\include \
	/I $(BASEPATH)\public\sdk\include 

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
	/O0 \
	/Obi \
	/Oi- \
	/X \
	/Zc:wchar_t \
	/ZI \
	/Zp4

linker-symbol-include-paths =

linker-switches = \
	$(linker-symbol-include-paths) \
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
	/NXCOMPAT:NO \
	/ALLOWBIND \
	/ALLOWISOLATION	\
	/LARGEADDRESSAWARE \
	/HIGHENTROPYVA:NO \
	/TSAWARE:NO

bootldr-compiler-switches := $(compiler-switches)
bootldr-linker-switches := $(linker-switches)

SOURCES = \
	krnl386.obj 

BIN = krnl386.exe

all: $(BIN) $(SOURCES)
	
.PHONY: all

$(BIN): $(SOURCES)
	$(linker) $(bootldr-linker-switches) /OUT:$@ $^

%.obj: %.c
	$(compiler) $(bootldr-compiler-switches) $<

%.obj: %.asm
	$(asm) -f win32 -o $@ $<