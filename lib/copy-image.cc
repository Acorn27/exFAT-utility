#include <fcntl.h>          // for open() system call, O_RDONLY
#include <stdio.h>
#include <iostream>
#include <unistd.h>         // for close(inFileDes)
#include <sys/mman.h>       // for mmap()
#include <assert.h>         // for assert()
#include <string.h>         // for memcpy()

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
    int inFileDes = getFileDescriptor(sourceName, O_RDONLY);
    assert(inFileDes != -1);

    // retrive file size
    size_t inFileSize = getFileSize(inFileDes);
    // cast to supress warning
    assert(inFileSize != (size_t)(-1));

    // see "man mmap"
    // also: https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-mmap-map-pages-memory
    // https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-mmap-map-pages-memory
    void* sourceMappedAddr = mmap(NULL,                       // addr = NULL, sys will choose the starting address for mapping
                    inFileSize,                   // length of bytes to map, usually equal size of file we want to map
                    PROT_READ | PROT_WRITE,     // protection: access allow for this process when mapping 
                    MAP_PRIVATE,                // type of mapping: changes are private
                    inFileDes,                   // file descriptor
                    0); // note the offset      // off set
    // error check
    if (sourceMappedAddr == MAP_FAILED)
    {
        std::cout << "Failed to map the input file into memory" << std::endl;
        close(inFileDes);
        return 1;
    }
    
    // create output file using fopen() for read and write
    // man fopen
    int outFileDes = getFileDescriptor(desName, O_RDWR | O_CREAT);
    assert(outFileDes != -1);

    // increase size of outFile to match inFile
    // see man ftruncate
    size_t outFileSize = inFileSize;
    ftruncate(outFileDes, outFileSize);

    // map outfile to memory
    void *desMappedAddr = mmap(NULL, outFileSize, PROT_WRITE, MAP_SHARED, outFileDes,0);
    // error check
    if (sourceMappedAddr == MAP_FAILED)
    {
        std::cout << "Failed to map the output file into memory" << std::endl;
        close(inFileDes);
        close(outFileDes);
        return 1;
    }

    // map src to des
    memcpy(desMappedAddr, sourceMappedAddr, inFileSize);

    // cleaning up
    clean_up(inFileDes, inFileSize, sourceMappedAddr);
    clean_up(outFileDes, outFileSize, desMappedAddr);
    return 0;
}