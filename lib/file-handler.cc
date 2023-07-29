#include <fcntl.h>          // for open() system call
#include <stdio.h>
#include <iostream>
#include <unistd.h>         // for close(file_des)
#include <sys/mman.h>       // for mmap()
#include <sys/stat.h>       // for fstat()
#include <cmath>            // for pow()
#include <assert.h>         // for assert()

#include "exfat.h"
#include "file-handler.h"

// get file descriptor
int getFileDescriptor(char* sourceName, int flag)
{
    // error check
    if (sourceName == NULL || flag < 0)
    {   
        std::cout << "Null arguments are not allowed" << std::endl;
        return -1;
    }

    int file_des = open(sourceName, flag);

    // check if file open successfully
    if (file_des == -1)
    {
        std::cout << "Failed to open file: "<< sourceName << std::endl;
    }
    return file_des;
}

// get file size
size_t getFileSize(int fileDescriptor)
{   

    // error check
    if (fileDescriptor == -1)
    {
        std::cout << "Null arguments are not allowed" << std::endl;
        return -1;
    }

    struct stat fileStat;
    size_t fileSize;

    if (fstat(fileDescriptor, &fileStat)== -1)
    {
        std::cout << "Failed to retrive files information using fstat";
        // remember to close file
        close(fileDescriptor);
        return -1;
    }

    fileSize = fileStat.st_size;
    return fileSize;
}

// print out image metadata
int print_metedata(void* pa)
{   

    // error check
    if (pa == NULL)
    {
        std::cout << "Null arguments are not allowed" << std::endl;
        return -1;
    }

    // cast Main_Boot struct to pa
    Main_Boot* MB = (Main_Boot*)pa;

    // print out all exfat Mainboot element
    std::cout << "Jump Boot:\t" << MB->JumpBoot << std::endl;
    std::cout << "File System:\t" << MB->FileSystemName << std::endl;
    std::cout << "Must be zero:\t" << MB->MustBeZero << std::endl;
    std::cout << "Jump Boot" << MB->JumpBoot << std::endl;
    std::cout << "Partition offset:\t" << MB->PartitionOffset << std::endl;
    std::cout << "Volume length:\t" << MB->VolumeLength << std::endl;
    std::cout << "Fat Offset:\t" << MB->FatOffset << std::endl;
    std::cout << "Fat length:\t" << MB->FatLength << std::endl;
    std::cout << "Cluster Heap Offset:\t" << MB->ClusterHeapOffset << std::endl;
    std::cout << "Cluster count:\t" << MB->ClusterCount << std::endl;
    std::cout << "Volume serial number:\t" << MB->VolumeLength << std::endl;
    // to be continue... check microsoft's exfat documentations

    int offset = 12 * pow(2,(int)MB->BytesPerSectorShift);
    Main_Boot *BB = (Main_Boot *)((char *)pa + offset);
    std::cout << "Jump Boot:\t" << BB->JumpBoot << std::endl;
    std::cout << "File System:\t" << BB->FileSystemName << std::endl;
    std::cout << "Must be zero:\t" << BB->MustBeZero << std::endl;
    std::cout << "Jump Boot" << BB->JumpBoot << std::endl;
    std::cout << "Partition offset:\t" << BB->PartitionOffset << std::endl;
    std::cout << "Volume length:\t" << BB->VolumeLength << std::endl;
    std::cout << "Fat Offset:\t" << BB->FatOffset << std::endl;
    std::cout << "Fat length:\t" << BB->FatLength << std::endl;
    std::cout << "Cluster Heap Offset:\t" << BB->ClusterHeapOffset << std::endl;
    std::cout << "Cluster count:\t" << BB->ClusterCount << std::endl;
    std::cout << "Volume serial number:\t" << BB->VolumeLength << std::endl;


    return 0;
}

// unmap and close file descriptor
int clean_up(int file_descriptor, size_t fileSize, void* pa)
{   
    if (file_descriptor == -1 || fileSize == (size_t)(-1) || pa == NULL)
    {
        std::cout << "Invalid arguments. Either file_des/fileSize negative or mmap failed" << std::endl;
        return -1;
    }

    // unmap file from memory
    if (munmap(pa, fileSize) == -1)
    {
        std::cout << "Failed to unmap the file from memory" << std::endl;
        return -1;
    }

    // close file descriptor
    close(file_descriptor);
    return 0;
}

// modified main/backup sector of exfat image to intentially failed checksum
int modified_image(char* imageName)
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
    Main_Boot *MB = (Main_Boot *)sourceMappedAddr;
    int offset = 12 * pow(2,(int)MB->BytesPerSectorShift);
    Main_Boot *BB = (Main_Boot *)((char *)sourceMappedAddr + offset);

    // modfied file name of backup region
    (BB->FileSystemName)[0] = 'K';       // new FileSystemName is now kxfat

    // cleanup
    clean_up(fileDescriptor, imageSize, sourceMappedAddr);
    // return success
    return 0;
}