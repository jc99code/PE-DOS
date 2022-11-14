
#include <bl.h>

/**
 * implementation
 */
void GetDriveParams(BPB *bpb)
{
}


/**
 * implementation
 */
void Lba2Chs(UINT32 LBA, UINT16 *Cylinder, UINT16 *Head, UINT16 *Sector)
{
    const UINT32 SPT = 2 * BPB_SECTORSPERTRACK;
	
    *Cylinder   = LBA / SPT;
    *Head       = ((LBA % (SPT)) / BPB_SECTORSPERTRACK);
    *Sector     = ((LBA % (SPT)) % BPB_SECTORSPERTRACK + 1);
}
