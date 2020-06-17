#include <iostream>
#include <time.h>
#include <stdarg.h>

#include <assert.h>

#include "CommandLineUI.h"
#include "../fileio/imageio.h"

#include "../RayTracer.h"
#include "../getopt.h"

using namespace std;

// ***********************************************************


// The command line UI simply parses out all the arguments off
// the command line and stores them locally.
CommandLineUI::CommandLineUI( int argc, char** argv )
	: TraceUI()
{
	int i;

	progName=argv[0];

	while( (i = getopt( argc, argv, "r:w:bBaAh" )) != EOF )
	{
		switch( i )
		{
			case 'r':
				m_nDepth = atoi( optarg );
				break;

			case 'w':
				m_nSize = atoi( optarg );
				break;
			case 'b':
				// TODO: Add code to ENABLE accelerated intersection testing!
				break;
			case 'B':
				// TODO: Add code to DISABLE accelerated intersection testing!
				break;
			case 'h':
				usage();
				exit(1);
				break;

			default:
			// Oops; unknown argument
			std::cerr << "Invalid argument: '" << i << "'." << std::endl;
			usage();
			exit(1);
		}
	}

	if( optind >= argc-1 )
	{
		std::cerr << "no input and/or output name." << std::endl;
		exit(1);
	}

	rayName = argv[optind];
	imgName = argv[optind+1];
}

int CommandLineUI::run()
{
	assert( raytracer != 0 );
	raytracer->loadScene( rayName );

	if( raytracer->sceneLoaded() )
	{
		int width = m_nSize;
		int height = (int)(width / raytracer->aspectRatio() + 0.5);

		raytracer->traceSetup( width, height );

		clock_t start, end;
		start = clock();

		for( int j = 0; j < height; ++j )
			for( int i = 0; i < width; ++i )
				raytracer->tracePixel(i,j);

		end=clock();

		// save image
		unsigned char* buf;

		raytracer->getBuffer(buf, width, height);

		if (buf)
			save(imgName, buf, width, height, ".png", 95);

		double t=(double)(end-start)/CLOCKS_PER_SEC;
		std::cout << "total time = " << t << " seconds" << std::endl;
        return 0;
	}
	else
	{
		std::cerr << "Unable to load ray file '" << rayName << "'" << std::endl;
		return( 1 );
	}
}

void CommandLineUI::alert( const string& msg )
{
	std::cerr << msg << std::endl;
}

void CommandLineUI::usage()
{
	std::cerr << "usage: " << progName << " [options] [input.ray output.bmp]" << std::endl;
	std::cerr << "  -r <#>      set recursion level (default " << m_nDepth << ")" << std::endl; 
	std::cerr << "  -w <#>      set output image width (default " << m_nSize << ")" << std::endl;
	std::cerr << "  -b          (TODO) enable accelerated intersection testing (default)" << std::endl;
	std::cerr << "  -B          (TODO) disable accelerated intersection testing" << std::endl;
	std::cerr << "  -a          (TODO) enable antialiasing" << std::endl;
	std::cerr << "  -A          (TODO) disable antialiasing (default)" << std::endl;
	std::cerr << "  -h          display this help message" << std::endl;
}
