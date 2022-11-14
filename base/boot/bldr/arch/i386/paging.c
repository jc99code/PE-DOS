
#include <bl.h>

DWORD *pPageDir = NULL;
DWORD *pBootPageTable = NULL;

void StartPaging(void)
{
    pPageDir = (DWORD *)0x100000;
    pBootPageTable = pPageDir + 0x1000;
    
    DWORD i;
    DWORD address = 0;
    
    for (i = 0; i < 1024; i++)
    {
        pBootPageTable[i] = address | (X86_PD_READ_WRITE | X86_PD_PRESENT);
        address += 4096;
    }

    for (i = 0; i < 1024; i++)
    {
        pPageDir[i] = X86_PD_READ_WRITE;
    }
    
    pPageDir[0] = pBootPageTable;
    pPageDir[0] = pPageDir[0] | (X86_PD_READ_WRITE | X86_PD_PRESENT);

    __asm
    {
        mov     ebx, DWORD PTR pPageDir
        mov     cr3, ebx
        mov     ebx, cr0
        or      ebx, 0x80000000
        mov     cr0, ebx
    }
}

void *GetPhysicalAddress(void *pVirtualAddress)
{
    //UINT_PTR *pPageDirEntry = (UINT_PTR *)0xfffff000;
    //if (*pPageDirEntry & X86_PD_PRESENT)
    //{
    //    UINT_PTR *pPageTableEntry = ((UINT_PTR *)0xffc00000) + (0x400 * X86_PD_INDEX(*pVirtualAddress));
    //    if (*pPageTableEntry & X86_PT_PRESENT)
    //    {
    //       return (void *)((pBootPageTable[X86_PT_INDEX(*pVirtualAddress)] & ~0xfff) + ((DWORD)pVirtualAddress & 0xfff));
    //    }
    //}
        
    return NULL;
}

void CreatePage()
{
}

void DeletePage()
{
}

void MapPage(void *PhysicalAddress, void *VirtualAddress, DWORD Flags)
{
    //UINT_PTR *pPageDirEntry = (UINT_PTR *)0xfffff000;
    //if (*pPageDirEntry & X86_PD_PRESENT)
    //{
    //    UINT_PTR *pPageTableEntry = ((UINT_PTR *)0xffc00000) + (0x400 * X86_PD_INDEX(VirtualAddress));
    //    if (*pPageTableEntry & X86_PT_PRESENT)
    //    {
    //        pBootPageTable[X86_PT_INDEX(VirtualAddress)] = ((DWORD)PhysicalAddress) | (Flags & 0xfff) | X86_PT_PRESENT;
    //    }
    //}
}


DWORD FindPage()
{
    return 0;
}
