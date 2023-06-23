#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "work_with_param.h"

const char version_text[] = "version 1.0\n";
const char help_text[] = 
    "Usage: app [-v] [-h | --help] [--args] \n"
    "           [-p <value> | --param <value>] [--data <value>]\n"
    "Options:\n"
    "  --args         Return the number of arguments and show a list of them\n"
    "  --data [DMMYY] Show date DMMYY as 'day_of_week month year',\n"
    "                   e.g. 71223 as Sunday December 2023\n"
    "  -h, --help     Show help\n"
    "  -p, --param [VALUE] \n"
    "                 If VALUE is a number, then put the number to 'dane.txt';\n"
    "                   if VALUE is a string, then write it on the screen;\n"
    "                   if no VALUE, then show last number from 'dane.txt';\n"
    "                   VALUE accepts rational number (double), also negativ\n"
    "  -v             Show version\n";

char *param_value;


double nr;

int main(int argc, char **argv)
{
    int status;
    int err = 0;
    int c;
    int help_flag = 0;
    int version_flag = 0;
    int param_read_from_file_flag = 0;
    int param_flag = 0;
    
    param_value = NULL;

    if (argc == 1)      // only program name
    {
        help_flag = 1;
    }
    else
    {
        while ((c = getopt(argc, argv, ":hvp:")) != -1)
        {
            switch (c)
            {
                case 'h':
                    help_flag = 1;
                    break;
                case 'v':
                    version_flag = 1;
                    break;
                case 'p':
                    param_flag = 1;
                    param_value = optarg;
                    break;
                case ':':
                    switch (optopt)
                    {
                        case 'p':
                            param_read_from_file_flag = 1;
                            break;
                        default:
                            fprintf(stderr,"option need some argument\n");
                            break;
                    }
                    break;
                case '?':
                    fprintf(stderr, "wrong option\n");
                    break;
                default:
                    break;
            }
        }
    }
    if (version_flag)
        printf(version_text);
    if (help_flag)
        printf(help_text);
    if (param_flag)
        work_with_param(param_value);
    if (param_read_from_file_flag)
    {
        status = param_read_from_file(&nr);
        if (status == STATUS_OK) 
            printf("%lf\n", nr);
        else if (status == EMPTY_FILE) 
            fprintf(stderr,"empty file\n");
        else if (status == FILE_NO_EXIST)
            fprintf(stderr,"file doesn't exist\n");
        else
            fprintf(stderr,"error\n");
    }

    return 0;
}