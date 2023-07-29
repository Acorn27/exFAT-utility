#include <iostream>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <unistd.h>
#include <memory.h> // for memcmp
#include <stdint.h> // for UInt32
#include <sys/stat.h>
#include <cmath>    // for pow(0)

#include "exfat.h"
#include "verify-image.h"
#include "file-handler.h"

// Boot/Backup Checksum computation
uint32_t BootChecksum(char* Sectors, short BytesPerSector)
{
    uint32_t NumberOfBytes = (uint32_t)BytesPerSector * 11;
    uint32_t Checksum = 0;
    uint32_t Index;

    for (Index = 0; Index < NumberOfBytes; Index++) {
        if ((Index == 106) || (Index == 107) || (Index == 112)) {
            continue; // Skip bytes at positions 106, 107, and 112
        }
        Checksum = ((Checksum & 1) ? 0x80000000 : 0) + (Checksum >> 1) + (uint32_t)Sectors[Index];
    }
    return Checksum;
}

int verify_image(char *imageName)
{
    // error check
    if (imageName == NULL)
    {
        std::cout << "Null arguments are not allowed" << std::endl;
        return 1;
    }

    // get file desciptor
    int fileDescriptor = getFileDescriptor(imageName, O_RDWR);
    assert(fileDescriptor != -1);

    // retrive file size
    size_t imageSize = getFileSize(fileDescriptor);

    // cast to supress warning
    assert(imageSize != (size_t)(-1));

    void *sourceMappedAddr = mmap(NULL,
                                  imageSize,
                                  PROT_READ | PROT_WRITE,
                                  MAP_PRIVATE,
                                  fileDescriptor,
                                  0);
    // error check
    if (sourceMappedAddr == MAP_FAILED)
    {
        std::cout << "Failed to map the input file into memory" << std::endl;
        close(fileDescriptor);
        return 1;
    }


    // cast MB and BB
    // compute offset of Backup Region
    // Read microsoft docs: Backup is 12 section offset from MainBoot
    // size of each offset is store in BytesPerSectorShift as log of 2
    Main_Boot *MB = (Main_Boot *)sourceMappedAddr;
    int offset = 12 * pow(2,(int)MB->BytesPerSectorShift);
    Main_Boot *BB = (Main_Boot *)((char *)sourceMappedAddr + offset);

    // compute checksum
    uint32_t mb_checksum = BootChecksum((char*)(MB), MB->BytesPerSectorShift);
    uint32_t bu_checksum = BootChecksum((char*)(BB), MB->BytesPerSectorShift);
    std::cout << "Main Boot CheckSum:\t" << mb_checksum << std::endl;
    std::cout << "Backup Boot CheckSum:\t" << bu_checksum << std::endl;
    
    //clean up and return comparision
    clean_up(fileDescriptor, imageSize, sourceMappedAddr);
    return mb_checksum == bu_checksum;
}