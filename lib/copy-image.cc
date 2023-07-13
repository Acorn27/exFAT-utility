#include <fcntl.h>          // for open() system call, O_RDONLY
#include <stdio.h>
#include <iostream>
#include <unistd.h>         // for close(file_des)
#include <sys/mman.h>       // for mmap()
#include <assert.h>         // for assert()

#include "exfat.h"
#include "copy-image.h"
#include "file-handler.h"


// copy source image to des using mmap()
int copy(char *sourceName, char* desName)
{   
    // safeguard
    if (sourceName == NULL || desName == NULL)
    {
        // add to error code table latter
        std::cout << "Null arguments are not allowed" << std::endl;
        return 1;
    }

    // create file descriptor for source file
    int file_des = getFileDescriptor(sourceName, O_RDONLY);
    assert(file_des != -1);

    // retrive file size
    size_t fileSize = getFileSize(file_des);
    // cast to supress warning
    assert(fileSize != (size_t)(-1));

    // see "man mmap"
    // also: https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-mmap-map-pages-memory
    // https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-mmap-map-pages-memory
    void* pa = mmap(NULL,                       // addr = NULL, sys will choose the starting address for mapping
                    fileSize,                   // length of bytes to map, usually equal size of file we want to map
                    PROT_READ | PROT_WRITE,     // protection: access allow for this process when mapping 
                    MAP_PRIVATE,                // type of mapping: changes are private
                    file_des,                   // file descriptor
                    0); // note the offset      // off set
    // error check
    if (pa == MAP_FAILED)
    {
        std::cout << "Failed to map the file into memory" << std::endl;
        close(file_des);
        return 1;
    }

    // print out file meta data
    print_metedata(pa);

    // cleaning up
    clean_up(file_des, fileSize, pa);
    return 0;
}