/*
Author: Mai Tran
Project: exFAT utility - modified version
Modification: 07/10/2023
*/
#include <iostream>
#include "lib/parse-command.h"

int main(int argc, char** argv)
{
    command* command_ptr = parse(argc, argv);
    std::cout << "input_file "<< command_ptr->infileName << std::endl;
    std::cout << "output_file "<< command_ptr->outfileName << std::endl;

    free(command_ptr);
    return 0;
}