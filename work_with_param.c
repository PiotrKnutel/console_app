#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "work_with_param.h"

const char FILE_NAME[] = "dane.txt";

/*
 * Return '0' if string isn't number or '1' if it is number.
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
 * Definition in 'work_with_param.h'
 */
int param_read_from_file(double *num)
{
    int status = STATUS_OK;
    char str_nr[100];
    FILE *fp;
    double result;
    char ch;
    char *ptr;
    int len = 0;                        // number of char in some number's string
    int num_detection_flag = 0;         // Has the program detected any number in the file, going backward?
    long int index_of_last_char_in_last_number = 0;

    fp = fopen(FILE_NAME, "r");

    if (!fp)
        return FILE_NO_EXIST;

    fseek(fp, 0L, SEEK_SET);

    if ((getc(fp)) == EOF)                  // Is it a empty file? 
        status = EMPTY_FILE;
    else
    {   
        fseek(fp, 0L, SEEK_END);            // go to end of file (EOF)
        
        do 
        {
            fseek(fp, -1L, SEEK_CUR);       // go to previous char
            ch = getc(fp);                  // get a char
            fseek(fp, -1L, SEEK_CUR);       // pointer to current char 
            if ((ch>='0' && ch<='9') || ch=='.' || ch=='-')     // check, char can be a part of number
            {
                len++;
                if (num_detection_flag == 0)
                {
                    num_detection_flag = 1;
                    index_of_last_char_in_last_number = ftell(fp);
                }
            }
            else
            {
                if (num_detection_flag == 1)    // detected a char before the first number's char
                    break;
            }
        } while (ftell(fp) != 0L);              // while current char isn't the start of file

        if(ftell(fp) != 0L)                      // if this isn't start of file
            fseek(fp, 1L, SEEK_CUR);            // go to the fist char in number's string
        
        if (len == 0)                           // program hasn't detected any number in the file 
            status = NO_DETECTED_NUM;
        else                                    // copy number string to result
        {
            for (int i=0; i < len; i++)
                str_nr[i] = getc(fp);
            
            str_nr[len+1] = '\0';
            result = strtod(str_nr, &ptr);
        }
    }
    fseek(fp, 0L, SEEK_SET);
    fclose(fp);
    
    *num = result; 
    return status;
}
