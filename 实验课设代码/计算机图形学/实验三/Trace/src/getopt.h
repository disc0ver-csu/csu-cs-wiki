#ifndef __RAY_GETOPT_H__
#define __RAY_GETOPT_H__

//use our getopt if on Windows, POSIX version otherwise

#ifdef _WIN32

int getopt(int argc, char **argv, char *optstring);
extern char* optarg;
extern int optind, opterr, optopt;

#else 
#include <getopt.h>
#endif

#endif //__RAY_GETOPT_H__
