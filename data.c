#include <stdio.h>
#include <string.h>
#include "data.h"

typedef int status; 

#define STATUS_CORRECT      1
#define STATUS_INVALID      0

#define ARGUMENT_LEN        5
#define MAX_DATA_STR_OUT    40

char *day_tab[] = { "poniedzialek", "wtorek", "sroda",
    "czwartek", "piatek", "sobota", "niedziela" };
char *month_tab[] = { "styczen", "luty", "marzec", "kwiecien",
    "maj", "czerwiec", "lipiec", "sierpien", "wrzesien",
    "pazdziernik", "listopad", "grudzien" };

int day;
int month;
int year;
char data_out[MAX_DATA_STR_OUT+1];


/*
 * Return STATUS_CORRECT if every char is number and the lenght
 * of string is equal ARGUMENT_LEN. If not, return STATUS_INVALID.
 */
status is_data_string_correct(char* data_in)
{
    status stat = STATUS_CORRECT;

    if (strlen(data_in) == ARGUMENT_LEN)
    {
        for (int i=0; i < ARGUMENT_LEN; i++)
        {
            if (data_in[i] < '0' || data_in[i] > '9')
            {
                stat = STATUS_INVALID;
                break;
            }
        }
    }
    else
    {
        stat = STATUS_INVALID;
    }

    return stat;
}


/*
 * Build the numbers of: day, month, year; from string.    
 */
void change_data_str_to_num(char *data_str, int *day, int *month, int *year)
{
    *day = data_str[0] - '0';
    *month = 10*(data_str[1] - '0') + (data_str[2] - '0');
    *year = 2000 + 10*(data_str[3] - '0') + (data_str[4] - '0');
}


/*
 * Return STATUS_INVALID if a number of week's day or month is invalid.
 * Return STATUS_CORRECT if both numbers are correct.  
 */
status is_data_num_correct(int *day, int *month, int *year)
{
    status stat = STATUS_CORRECT;

    if ((*day)<1 || (*day)>7)
    {
        fprintf(stderr, "Day of the week '%d' doesn't exist\n", *day);
        stat = STATUS_INVALID;
    }
    if ((*month)<1 || (*month)>12)
    {
        fprintf(stderr, "Month '%d' doesn't exist\n", *month);
        stat = STATUS_INVALID;
    }

    return stat;
}


/*
 * Description on the 'data.h' file
 */
int data(char *data_in)
{
    day = 0;
    month = 0;
    year = 0;
    
    if (is_data_string_correct(data_in) == STATUS_INVALID)
    {
        fprintf(stderr, "invalid argument, correct argument is [DMMYY]\n");
        return DATA_ERR;
    }
    
    change_data_str_to_num(data_in, &day, &month, &year);
    
    if (!is_data_num_correct(&day, &month, &year))
        return DATA_ERR;

    snprintf(data_out, MAX_DATA_STR_OUT-1, "%s %s %d", day_tab[day-1], month_tab[month-1], year);
    printf("%s\n", data_out);

    return DATA_OK;
}
