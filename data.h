#ifndef _DATA_H
#define _DATA_H

#define DATA_ERR -1
#define DATA_OK  0

/*
 * Change data_in "dmmyy" (e.g. "71223") to "day_of_week month year"
 * (e.g. Sunday December 2023) and write it on the sceen or send
 * error message to stderr. 
 * INPUT:
 *   char *data_in      - input data [DMMYY]   
 */
int data(char* data_in);


#endif // _DATA_H
