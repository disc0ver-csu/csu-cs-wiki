/*
  The Buffer class is essentially a wrapper for an istream.
  It is here mainly to keep track of the current file location
  (line number, column number) to print intelligent error messages.


  If you find yourself changing stuff in this file, you're probably
  doing something wrong.
*/

#include <string>
#include "buffer.h"

#include "../parser/Parser.h"


//////////////////////////////////////////////////////////////////////////
//
// Buffer::Buffer(FILE*,...) constructor
//
//   This constructor sets up the initial state that we need in order
// to read files.
//

Buffer::Buffer(istream& is, bool printChars, bool printLines)
  : inStream( is )
{ 
    PositionInCurrentLine = Line.begin();
    LineNumber            = 0;
    ColNumber             = 0;
    LastPrintedLine       = 0;
    
    _printChars = printChars;
    _printLines = printLines;
	_bHasData = false;
}


//////////////////////////////////////////////////////////////////////////
//
// char Buffer::GetCh() private method
//
//   GetCh() gets a new character from the buffer and returns it
//

char Buffer::GetCh() {
  if (!inStream) {
    return '\0';
  }

  // test for data
  if ( !_bHasData )
  {
	   // Nothing has been read-in yet, so read the first line
	   GetLine();
	   if ( !_bHasData )
	   {
		   return '\0';
	   }
  }
  else
  {
	  // advance position
	  PositionInCurrentLine++;
	  ColNumber++;
  }

  while (PositionInCurrentLine == Line.end() || Line.empty()) {
    // need to read another line of input from the file

    GetLine();
    if (!inStream) {
      return '\0';
    }
  }

  // extract character from line buffer
  char CurrentCh = *PositionInCurrentLine;

  if (_printChars) {
    std::cout << "Read character `" << CurrentCh << "'" << std::endl;
  }

  return CurrentCh;
}


//////////////////////////////////////////////////////////////////////////
//
// void Buffer::GetLine() private method
//
//   GetLine() reads a new line from the file into the Line buffer
// variable.  It also handles listings, if necessary.  Returns are false
// for EOF or true for got a new buffer.
//
// This function is weak, in that it can't handle arbitrarily long lines
// in a file.  Ideally it would be rewritten so that it can do this fine.
// The real difficulty is in being able to print out, on demand, the whole
// line of input, of arbitrary length.
//

void Buffer::GetLine() {
  std::getline(inStream, Line);
  Line.append( "\n" ); // because iostreams strip out the end-of-line char
  PositionInCurrentLine = Line.begin();

  _bHasData = ( PositionInCurrentLine != Line.end() && !Line.empty() );

  ColNumber = 0;
  LineNumber ++;

  if (_printLines) PrintLine( std::cout );
}


//////////////////////////////////////////////////////////////////////////
//
// void Buffer::PrintLine() method
//
//   This method displays the current line on the screen.
//

void Buffer::PrintLine( ostream& out ) const {
  if (LineNumber > LastPrintedLine) {
    out << "# " << Line << std::endl;
    LastPrintedLine = LineNumber;
  }
}
