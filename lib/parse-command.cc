#include "parse-command.h"
#include <iostream>
#include <getopt.h>
#include <string.h>

command *parse(int argc, char **argv)
{
    // dynamically alocated command structure
    command *command_ptr = new command {};

    // counter for getopt
    int c;
    opterr = 0;

    // <option>: => there is an string follow an options. EX (-i inputFile.txt)
    // <option>  => yes/no option like verify
    while ((c = getopt(argc, argv, "i:o:d:chvep")) != -1)
    {
        switch (c)
        {
        case 'i':
            command_ptr->infile = 1;
            command_ptr->infileName = new char[strlen(optarg) + 1];
            strcpy(command_ptr->infileName, optarg);
            break;
        case 'o':
            command_ptr->outfile = 1;
            command_ptr->outfileName = new char[strlen(optarg) + 1];
            strcpy(command_ptr->outfileName, optarg);
            break;
        case 'd':
            command_ptr->del_file = 1;
            command_ptr->deleteFile = new char[strlen(optarg) + 1];
            strcpy(command_ptr->deleteFile, optarg);
            break;
        case 'c':
            command_ptr->copy = 1;
            break;
        case 'h':
            command_ptr->help = 1;
            break;
        case 'v':
            command_ptr->verify = 1;
            break;
        case 'e':
            command_ptr->extract = 1;
            break;
        case 'p':
            command_ptr->print_dir = 1;
            break;
        case '?':
            if (optopt == 'i' || optopt == 'o' || optopt == 'd')
                std::cout << "Option " << char(optopt) << " require an argument" << std::endl;
            else if (isprint(optopt))
                std::cout << "Unkown option " << char(optopt) << std::endl;
            return (NULL);
        default:
            return (NULL);
        }
    }

    return command_ptr;
}

void clean_up(command* cmd)
{
    if (cmd == nullptr)
        return;

    if (cmd->infileName != nullptr)
        delete[] cmd->infileName;

    if (cmd->outfileName != nullptr)
        delete[] cmd->outfileName;

    if (cmd->deleteFile != nullptr)
        delete[] cmd->deleteFile;

    delete cmd;
}
