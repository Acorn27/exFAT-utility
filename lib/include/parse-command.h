#ifndef MAIN_PARSE_COMMAND_H
#define MAIN_PARSE_COMMAND_H

struct command 
{
    int infile,     // input file
        outfile,    // output file
        help,       // print manual
        copy,       // copy file
        verify,     // verify if this is exFAT
        extract,    // extract exFAT disk image
        print_dir,  // recursively print dir/sub-dir
        del_file;   // delete file from disk image
    
    char* infileName;
    char* outfileName;
    char* deleteFile;
};  

typedef struct command command;

// parse command line input into a defined command structure
command* parse(int argc, char** argv);

void clean_up(command* command_ptr);

#endif
