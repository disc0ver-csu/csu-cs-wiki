// Needed to correct for annoying "feature" in MSVC's compiler
#pragma warning (disable: 4786)

#ifndef _BUFFER_H_
#define _BUFFER_H_


/*
  The Buffer class is essentially a wrapper for an istream.
  It is here mainly to keep track of the current file location
  (line number, column number) to print intelligent error messages.


  If you find yourself changing stuff in this file, you're probably
  doing something wrong.

  This class was borrowed from the stock PL0 source code used for
  CSE401, because I didn't feel like rewriting it. 
  ( see http://www.cs.washington.edu/401 for details )
*/

#include <iostream>
#include <string>


using std::istream;
using std::ostream;
using std::string;

class Buffer {
 public:
  Buffer(std::istream& file, bool printChars, bool printLines);

  char GetCh();			// Read and return next character
  bool isEOF() { return !(inStream); }	// Return whether is end of file

  void PrintLine(std::ostream& out) const;		// Print current line

  int  CurColumn() const { return ColNumber; }
  int  CurLine() const { return LineNumber; }	// Return current line #
  
protected:
  void  GetLine();		// Read next line from file

  std::istream& inStream;            // The file pointer to the source file

  std::string Line;                  // The line buffer
  std::string::const_iterator PositionInCurrentLine;

  int   ColNumber;		// The number of the current column
  int   LineNumber;             // The number of the line in the file
  mutable int   LastPrintedLine;        // The line number of the last printed line

  bool _printLines, _printChars; // printing flags
  bool _bHasData; // Whether the Buffer has data to read
};

#endif
