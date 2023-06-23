#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/*
 * Return '0' if string is not number or '1'if it is number.
 * Function supports float and double, signed and unsigned number.
 */
int is_str_number(char *str, int str_len)
{
    int is_number = 0;
    int counter_coma = 0;
    int i = 0;
    if (str[0] == '-')
        i++;
    while ((str[i]>='0' && str[i]<='9') || str[i]=='.')
    {
        if (str[i] == '.')
        {
            counter_coma++;
            if (counter_coma > 1)
            {
                printf("to many '.' in number\n");
                break;
            }
        }
        i++;
    }
    if (i == str_len)
        is_number = 1;
    else
        is_number = 0;

    return is_number;
}

FILE* save_to_file(const char file_name[], char *arg)
{
    FILE *fp;
    fp = fopen(file_name, "a");
    fprintf(fp, "%s ", arg);
    fclose(fp);
    return fp;
}

/*
 * Description is at 'work_with_param.h'
 */ 
void work_with_param(char *arg)
{
    int is_number;
    int len = strlen(arg);
    const char FILE_NAME[] = "dane.txt";
    //printf("len=%i\n",len);
    
    if (is_str_number(arg,len))
    {
        if (save_to_file(FILE_NAME, arg))
            printf("%s has been saved to %s\n", arg, FILE_NAME);
        else
            fprintf(stderr,"error while saving to file\n");
    }
    else
        printf("%s\n", arg);
}
