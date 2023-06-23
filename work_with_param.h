#ifndef _WORK_WITH_PARAM_H
#define _WORK_WITH_PARAM_H

#define EMPTY_FILE      -1
#define STATUS_OK       0
#define FILE_NO_EXIST   -2

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
 * Return '-1' when empty_file.
 * Return '0' when file isn't empty.
 * Return '0' when file doesn't exist.
 * FILE_NAME is declared in 'work_with_param.c'.
 */
 int param_read_from_file(double *result);


#endif // _WORK_WITH_PARAM_H