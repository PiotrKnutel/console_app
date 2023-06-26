#ifndef _WORK_WITH_PARAM_H
#define _WORK_WITH_PARAM_H

#define STATUS_OK       0
#define EMPTY_FILE      -1
#define FILE_NO_EXIST   -2
#define NO_DETECTED_NUM -3


/*
 * Function 'work_with_param()' decides what to do with option argument
 * (argument of option -p or --param) and prints optional result.
 * The function is shared to 'main.c'.
 * INPUT: 
     char *option_arg   - pointer to argument of option -p or --param
 */
void work_with_param(char *arg);


/*
 * Functon gives last number from file.
 * Return '0' when file isn't empty.
 * Return '-1' when file is empty.
 * Return '-2' when file doesn't exist.
 * FILE_NAME is declared on 'work_with_param.h'.
 * OUTPUT:
 *   return int         - Status
 *   double* result     - readed number from file
 */
 int param_read_from_file(double *result);


#endif // _WORK_WITH_PARAM_H