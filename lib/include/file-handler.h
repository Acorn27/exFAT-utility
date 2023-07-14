#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

// get file descriptor
int getFileDescriptor(char* sourceName, int flag);

// obtain file size to passed to mmap using stat struct and fstat
// see: https://man7.org/linux/man-pages/man2/fstat.2.html
size_t getFileSize(int fileDescriptor);

// obtain file size to passed to mmap using stat struct and fstat
// see: https://man7.org/linux/man-pages/man2/fstat.2.html
size_t getFileSize(int fileDescriptor);

// print out exfat image metadate
int print_metedata(void* pa);

// clean_up by unmap and close file descriptor
int clean_up(int file_descriptor, size_t fileSize, void* pa);

#endif