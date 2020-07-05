#include <iostream>
#include <sstream>

#include "ParserException.h"
#include "Tokenizer.h"

/* These are some exceptions used by the parser class. */


SyntaxErrorException::SyntaxErrorException( const string& msg, const Tokenizer& tokenizer )
	: ParserException( msg )
{
  std::ostringstream out;
  tokenizer.PrintLine( out );
  out << "  ";
  for( int i = 0; i < tokenizer.CurColumn(); i++ ) {
    out << " ";
  }
  out << "^" << std::endl;

  out << "Line " << tokenizer.CurLine() << ": syntax error: "
    << message() << std::endl;

  _formattedMsg = out.str();

}



