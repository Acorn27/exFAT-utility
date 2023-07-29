#include <iostream>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <unistd.h>
#include <memory.h> // for memcmp
#include <stdint.h> // for UInt32
#include <sys/stat.h>

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
    // open the file system image file
   int fd = open(imageName, O_RDWR);
   if (fd == -1)
   {
      perror("file open: ");
      exit(0);
   }

   off_t size = 0;
   struct stat statbuf;
   if (fstat(fd, &statbuf))
   {
      perror("stat of file:");
      exit(0);
   }
   size = statbuf.st_size;
   printf("The file size is %ld\n", size);

   // mmap the entire file into memory
   // every data item we reference, will be relative to fp...
   void *fp = (void *)mmap(NULL,
                           size,
                           PROT_READ | PROT_WRITE,
                           MAP_PRIVATE,
                           fd,
                           0); // note the offset

   if (fp == (void *)-1)
   {
      perror("mmap:");
      exit(0);
   }

   // first, is the Main Boot record
   Main_Boot *MB = (Main_Boot *)fp;

   // print out some things we care about

   printf("FileSystemName %s\n", MB->FileSystemName); // warning, not required to be terminated
   printf("\n");
   printf("BytesPerSectorShift %d\n", MB->BytesPerSectorShift);
   printf("SectorsPerClusterShift %d\n", MB->SectorsPerClusterShift);
   printf("NumberOfFats %d\n", MB->NumberOfFats);
    // // error check
    // if (imageName == NULL)
    // {
    //     std::cout << "Null arguments are not allowed" << std::endl;
    //     return 1;
    // }

    // // get file desciptor
    // int fileDescriptor = getFileDescriptor(imageName, O_RDWR);
    // assert(fileDescriptor != -1);

    // // retrive file size
    // size_t imageSize = getFileSize(fileDescriptor);

    // // cast to supress warning
    // assert(imageSize != (size_t)(-1));

    // void *sourceMappedAddr = mmap(NULL,
    //                               imageSize,
    //                               PROT_READ | PROT_WRITE,
    //                               MAP_PRIVATE,
    //                               fileDescriptor,
    //                               0);
    // // error check
    // if (sourceMappedAddr == MAP_FAILED)
    // {
    //     std::cout << "Failed to map the input file into memory" << std::endl;
    //     close(fileDescriptor);
    //     return 1;
    // }

    // print_metedata(sourceMappedAddr);

    // // Main_Boot *MB = (Main_Boot *)sourceMappedAddr;
    // // Main_Boot *BB = (Main_Boot *)(sourceMappedAddr + sizeof(Main_Boot));

    // // std::cout << "Byte persector is" << MB->BytesPerSectorShift << std::endl;
    // // std::cout << "File system name is" << MB->FileSystemName << std::endl;

    // // uint32_t mb_checksum = BootChecksum((char*)(exfat->M_Boot), exfat->M_Boot->BytesPerSectorShift);
    // // uint32_t bu_checksum = BootChecksum((char*)(exfat->B_Boot), exfat->B_Boot->BytesPerSectorShift);
    // // std::cout << "Main Boot check sum: " << mb_checksum << std::endl;
    // // std::cout << "Backup check sum: " << bu_checksum << std::endl;


    // //clean up and return sucess
    // clean_up(fileDescriptor, imageSize, sourceMappedAddr);
    // return 0;
}