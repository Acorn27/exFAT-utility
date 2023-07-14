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
        if (copy(command_ptr->infileName, command_ptr->outfileName) == 1)
        {
            std::cout << "Failed to copy from " << command_ptr->infileName << " to " << command_ptr->outfileName << std::endl;
        }
        else
        {
            std::cout << "Succesfully copy from " << command_ptr->infileName << " to " << command_ptr->outfileName << std::endl;
        }
    }

    /* free dynamically allocated memmory*/
    clean_up(command_ptr);
    return 0;
}