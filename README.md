# console_app
Program for Linux terminal.

author: Piotr Knutel (piknut@linux.pl), 2023
version: 1.0
tested with: gcc 11.3.0, Ubuntu 22.04, x86_64

## HELP

Usage: app [-v] [-h | --help] [--args]
           [-p <value> | --param <value>] [--data <value>]

Options:
  --args         Return the number of arguments and show a list of them
  --data [DMMYY] Show date DMMYY as 'day_of_week month year',
                   e.g. 71223 as Sunday December 2023
  -h, --help     Show help
  -p, --param [VALUE]
                 If VALUE is a number, then put the number to 'dane.txt';
                   if VALUE is a string, then write it on the screen;
                   if no VALUE, then show last number from 'dane.txt';
                   VALUE accepts rational number (double), also negativ
  -v             Show version
