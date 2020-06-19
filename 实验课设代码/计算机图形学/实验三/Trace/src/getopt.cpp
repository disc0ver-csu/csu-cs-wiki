///////////////////////////////////////////////////////////////////////////////
//
//  FILE: getopt.cpp
//
//      GetOption function
//
//  FUNCTIONS:
//
//      GetOption() - Get next command line option and parameter
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////

//
// For Unix, we do have the standard function called getopt. However, we need to
// make up one for NT. So, I just stick to this one. If you prefer, you can call
// the standard getops() on Linux.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: GetOption()
//
//      Get next command line option and parameter
//
//  PARAMETERS:
//
//      argc - count of command line arguments
//      argv - array of command line argument strings
//      pszValidOpts - string of valid, case-sensitive option characters,
//                     a colon ':' following a given character means that
//                     option can take a parameter
//      ppszParam - pointer to a pointer to a string for output
//
//  RETURNS:
//
//      If valid option is found, the character value of that option
//          is returned, and *ppszParam points to the parameter if given,
//          or is NULL if no param
//      If standalone parameter (with no option) is found, 1 is returned,
//          and *ppszParam points to the standalone parameter
//      If option is found, but it is not in the list of valid options,
//          -1 is returned, and *ppszParam points to the invalid argument
//      When end of argument list is reached, 0 is returned, and
//          *ppszParam is NULL
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////////

char* optarg = NULL;
int optind, opterr, optopt;

int GetOption (
    int argc,
    char** argv,
    char* pszValidOpts,
    char** ppszParam)
{
    static int iArg = 1;
    char chOpt;
    char* psz = NULL;
    char* pszParam = NULL;

    if (iArg < argc)
    {
        psz = &(argv[iArg][0]);
        if (*psz == '-' || *psz == '/')
        {
            // we have an option specifier
            chOpt = argv[iArg][1];
            if (isalnum(chOpt) || ispunct(chOpt))
            {
                // we have an option character
                psz = strchr(pszValidOpts, chOpt);
                if (psz != NULL)
                {
                    // option is valid, we want to return chOpt
                    if (psz[1] == ':')
                    {
                        // option can have a parameter
                        psz = &(argv[iArg][2]);
                        if (*psz == '\0')
                        {
                            // must look at next argv for param
                            if (iArg+1 < argc)
                            {
                                psz = &(argv[iArg+1][0]);
                                if (*psz == '-' || *psz == '/')
                                {
                                    // next argv is a new option, so param
                                    // not given for current option
                                }
                                else
                                {
                                    // next argv is the param
                                    iArg++;
                                    pszParam = psz;
                                }
                            }
                            else
                            {
                                // reached end of args looking for param
                            }

                        }
                        else
                        {
                            // param is attached to option
                            pszParam = psz;
                        }
                    }
                    else
                    {
                        // option is alone, has no parameter
                    }
                }
                else
                {
                    // option specified is not in list of valid options
                    chOpt = -1;
                    pszParam = &(argv[iArg][0]);
                }
            }
            else
            {
                // though option specifier was given, option character
                // is not alpha or was was not specified
                chOpt = -1;
                pszParam = &(argv[iArg][0]);
            }
        }
        else
        {
            // standalone arg given with no option specifier
            chOpt = 1;
            pszParam = &(argv[iArg][0]);
        }
    }
    else
    {
        // end of argument list
        chOpt = 0;
    }

    iArg++;
    *ppszParam = pszParam;
	optind = iArg-1;
    return (chOpt);
}

int getopt(int argc, char **argv, char *optstring)
{
	int i;
	
	i = GetOption(argc, argv, optstring, &optarg);

	if (i==0 || i==1) return EOF;
	else if (i==-1) {
		char c=*(optarg+1);
		return c;
	}
	else return i;
}
			
