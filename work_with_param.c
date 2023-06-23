#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "work_with_param.h"

const char FILE_NAME[] = "dane.txt";

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


/*
 * Save string to end of file.
 */
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


/*
 * Read number from file FILE_NAME
 * Definition on 'work_with_param.h'
 */
int param_read_from_file(double *num)
{
    char str_nr[100];
    FILE *fp;
    double result;
    char ch;
    char *ptr;
    int len = 0;

    fp = fopen(FILE_NAME, "r");
    if (!fp)
        return FILE_NO_EXIST;
    fseek(fp, 0L, SEEK_SET);
    if ((getc(fp)) == EOF)   // Looking for end of file
        return EMPTY_FILE;
    else
    {   
        fseek(fp, 0L, SEEK_END);
        fseek(fp, -2L, SEEK_CUR);
        
        while (getc(fp) != ' ')
        {
            len++;
            fseek(fp, -2L, SEEK_CUR);
        }
        
        for (int i=0; i < len; i++)
        {
            str_nr[i] = getc(fp);
        }
        str_nr[len] = '\0';
        //printf ("%s\n", str_nr);
        
        result = strtod(str_nr, &ptr);
        //printf("String part is: %s\n", ptr);
    }
    fclose(fp);
    
    *num = result; 
    return STATUS_OK;
}
