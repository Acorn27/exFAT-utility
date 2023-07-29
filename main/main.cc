/*
Author: Mai Tran
Project: exFAT utility - modified version
Modification: 07/19/2023
*/
#include <iostream>
#include "parse-command.h"
#include "copy-image.h"
#include "verify-image.h"

int main(int argc, char** argv)
{
    command* command_ptr = parse(argc, argv);
    if (command_ptr == NULL)
    {
        return 1;
    }
    if (command_ptr->infileName == NULL)
    {   
        std::cout << "Input file name is required!" << std::endl;
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

    // verify
    if (command_ptr->verify)
    {
        if (verify_image(command_ptr->infileName))
        {
            std::cout << "Passed: Main and Backup Boot Sector are equal" << std::endl;
        }
        else
        {
            std::cout << "Failed: Main and Backup Boot Sector are not equal" << std::endl;
        }
    }

    /* free dynamically allocated memmory*/
    clean_up(command_ptr);
    return 0;
}