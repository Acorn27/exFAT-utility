/*
Author: Mai Tran
Project: exFAT utility - modified version
Modification: 07/10/2023
*/
#include <iostream>
#include "parse-command.h"
#include "copy-image.h"

int main(int argc, char** argv)
{
    command* command_ptr = parse(argc, argv);
    if (command_ptr == NULL)
    {
        return 1;
    }

    if (command_ptr->copy)
    {
        copy(command_ptr->infileName, command_ptr->outfileName);
    }

    /* free dynamically allocated memmory*/
    clean_up(command_ptr);
    return 0;
}