#include "lib/parse-command.h"
#include <iostream>
#include <getopt.h>
#include <string.h>

command* parse(int argc, char** argv)
{
    // dynamically alocated command structure
    command* command_ptr = new command;

    // counter for getopt
    int c;
    opterr = 0;

    // <option>: => there is an string follow an options. EX (-i inputFile.txt)
    // <option>  => yes/no option like verify
    while ((c = getopt(argc, argv, "i:o:d:hvep")) != 1)

    switch (c)
    {
        case 'i':
            command_ptr->infile = 1;
            command_ptr->infileName = new char[sizeof(optarg)];
            strcpy(command_ptr->infileName, optarg);
            break;
        case 'o':
            command_ptr->outfile = 1;
            command_ptr->outfileName = new char[sizeof(optarg)];
            strcpy(command_ptr->outfileName, optarg);
            break;
        case 'd':
            command_ptr->del_file = 1;
            command_ptr->deleteFile = new char[sizeof(optarg)];
            strcpy(command_ptr->deleteFile, optarg);
        case 'c':
            command_ptr->copy = 1;
            break;
        case 'h':
            command_ptr->help = 1;
        case 'v':
            command_ptr->verify = 1;
        case 'e':
            command_ptr->extract = 1;
        case 'p':
            command_ptr->print_dir = 1;
        case '?':
            if (optopt == 'i' || optopt == 'o' || optopt == 'd')
                std::cout << "Option " << optopt << " require an argument" << std::endl;
            else if (isprint(optopt))
                std::cout << "Unkown option " << optopt << std::endl;
        default:
            break;
        }

    return command_ptr;
}