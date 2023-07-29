#ifndef _VERIFY_IMAGE_H
#define _VERIFY_IMAGE_H

#include <stdint.h>


uint32_t BootChecksum
(
    char  * Sectors,        // points to an in-memory copy of the 11 sectors
    short   BytesPerSector
);

uint32_t BootChecksum(char* Sectors, short BytesPerSector);

int verify_image(char* imageName);

#endif