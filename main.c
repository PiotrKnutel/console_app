/* Simply Linux console program 
 * author: Piotr Knutel (piknut[at]linux.pl)
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "work_with_param.h"
#include "data.h"

#define CASE_DATA   1000

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
char *data_arg_value;
double nr;

int main(int argc, char **argv)
{
    int status;
    int c;
    int help_flag = 0;
    int version_flag = 0;
    int param_read_from_file_flag = 0;
    int param_flag = 0;
    static int args_flag = 0;
    static int data_flag = 0;
    char *buff;                         // buffor for copy of argv

    param_value = NULL;

    if (argc == 1)      // show only program name
        help_flag = 1;
    else
    {
        while(1)
        {
            static struct option getopt_long_options[] = {
            {"args",    optional_argument,  &args_flag,     1           },
            {"data",    required_argument,  NULL,           CASE_DATA   },
            {"help",    no_argument,        NULL,           'h'         },
            {"param",   required_argument,  NULL,           'p'         },
            {0, 0, 0, 0}
            };

        int option_index = 0;
        c = getopt_long(argc, argv, ":hvp:", getopt_long_options, &option_index);

        if (c == -1)    // end of options 
            break;

            switch (c)
            {
                case 0:
                    // neccessery for --args
                    if (getopt_long_options[option_index].flag != NULL)
                        break;
                    break;
                case 'h':
                    help_flag = 1;
                    break;
                case 'v':
                    version_flag = 1;
                    break;
                case 'p':
                    if (optarg)
                    {
                        param_flag = 1;
                        param_value = optarg;
                    }
                    else
                    {
                        /* Ten else nigdy nie nastąpi, bo jeśli brak
                           argumentu po -p to wykonuje się case ':'.   */
                        param_read_from_file_flag = 1;
                    }
                    break;
                case CASE_DATA:
                    if (optarg)
                    {
                        data_flag = 1;
                        data_arg_value = optarg;
                    }
                    else
                    {
                        /* Ten else nigdy nie nastąpi, bo jeśli brak
                           argumentu po --data to wykonuje się case ':'. */
                        fprintf(stderr,"option --data needs an argument\n");
                    }
                    break;
                case ':':
                    switch (optopt)
                    {
                        case 'p':
                            param_read_from_file_flag = 1;
                            break;
                        case CASE_DATA:
                            fprintf(stderr,"option --data needs an argument\n");
                            break;
                        default:
                            fprintf(stderr,"it is wrong option\n");
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

    if (data_flag)
        data(data_arg_value);

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

    if (args_flag)
    {
        printf("------------------------\n");
        printf("Number of arguments: %d\n", argc-1);
        printf("List of all arguments:\n");
        for (int i=1; i < argc; i++)
            printf("%s\n", *++argv);
        printf("------------------------\n");
    }

    return 0;
}
