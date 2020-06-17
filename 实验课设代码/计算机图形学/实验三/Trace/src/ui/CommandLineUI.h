//
// CommandLineUI.h
//
// The header file for the command line UI
//

#ifndef __CommandLineUI_h__
#define __CommandLineUI_h__

#include "TraceUI.h"


class CommandLineUI 
	: public TraceUI
{
public:
	CommandLineUI( int argc, char** argv );
	int		run();

	void		alert( const string& msg );

private:
	void		usage();

	char*	rayName;
	char*	imgName;
	char*	progName;
};

#endif
