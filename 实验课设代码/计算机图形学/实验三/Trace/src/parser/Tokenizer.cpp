// Tokenizer.cpp
// Breaks the input stream up into tokens
#include <string> 
#include <map>
#include <sstream>

#include "../fileio/buffer.h"
#include "Tokenizer.h"
#include "Token.h"


/*
   The tokenizer's job is to convert a stream of characters
   into a stream of tokens that the parser can then handle.
   You probably aren't going to be modifying this file;
   most of the stuff that you might want to change is in
   Token.{h,cpp} and Parser.{h,cpp}.

   This tokenizer is based on the tokenizer from the
   PL0 project used for CSE401
   (http://www.cs.washington.edu/401).

*/


//////////////////////////////////////////////////////////////////////////
//
// Tokenizer::Tokenizer(istream&) constructor
//
//   This constructor sets up the initial state that we need in order
// to start scanning.  Note that we will be passed an OPEN file.  This
// simplifies the scanner part, since we don't have to open it and
// error check to see if it exists.  We assume that the caller (which
// will be the main() function) sets up everything and passes us a VALID
// file pointer.
//

Tokenizer::Tokenizer(istream& fp, bool printTokens) 
  : buffer( fp, false, false )
{ 
    TokenColumn = 0;
    CurrentCh = ' ';
    UnGetToken = NULL;
    _printTokens = printTokens;
}

//////////////////////////////////////////////////////////////////////////
//
// repeatedly scan tokens in and throw them away.  Useful if this is the
// last phase to be executed
// 
void Tokenizer::ScanProgram() {
    while (Get()->kind() != EOFSYM) ;
}


auto_ptr<Token> Tokenizer::Get() {
  return auto_ptr<Token>(GetNext());
}

//////////////////////////////////////////////////////////////////////////
//
// Token* Tokenizer::Get() method
//
// Advance through the source to find the next token. Returns peeked token,
// if there is one.
//

Token* Tokenizer::GetNext() {
  Token* T = NULL;

  // First check to see if there is an UnGetToken. If there is, use it.
  if (UnGetToken != NULL) {
    T = UnGetToken;
    UnGetToken = NULL;
    return T;
  }

  // Otherwise, crank up the scanner and get a new token.

  // Get rid of any whitespace
  SkipWhiteSpace();

  // test for end of file
  if (buffer.isEOF()) {
    T = new Token(EOFSYM);

  } else {
    
    // Save the starting position of the symbol in a variable,
    // so that nicer error messages can be produced.
    TokenColumn = buffer.CurColumn();
    
    // Check kind of current character
    
    // Note that _'s are now allowed in identifiers.
    if (isalpha(CurrentCh) || '_' == CurrentCh) {
      // grab identifier or reserved word
      T = GetIdent();
    } else if ( '"' == CurrentCh)  {
      T = GetQuotedIdent(); 
    } else if (isdigit(CurrentCh) || '-' == CurrentCh || '.' == CurrentCh) {
      T = GetScalar();
    } else { 
      //
      // Check for other tokens
      //
      
      T = GetPunct();
    }
  }
  
  if (T == NULL) {
    throw ParserFatalException("didn't get a token");
  }

  if (_printTokens) {
    std::cout << "Token read: ";
    T->Print();
    std::cout << std::endl;
  }

  return T;
}

//////////////////////////////////////////////////////////////////////////
//
// Skips spaces, tabs, newlines, and comments
//
void Tokenizer::SkipWhiteSpace() {
  while (isspace(CurrentCh) && CurrentCh ) {
    GetCh();
  }

  if( '/' == CurrentCh )  // Look for comments
  {
    GetCh();
    if( '/' == CurrentCh )
    {
      // Throw out everything until the end of the line
      while( '\n' != CurrentCh )
      {
        GetCh();
      }
    }
    else if ( '*' == CurrentCh )
    {
      int startLine = CurLine();
      while( true )
      {
        GetCh();
        if( '*' == CurrentCh )
        {
          GetCh();
          if( CondReadCh( '/' ) )
            break;
          else if ( buffer.isEOF() )
          {
            std::ostringstream ost;
            ost << "Unterminated comment in line ";
            ost << startLine;
            throw SyntaxErrorException( ost.str(), *this );
          }
        }
        else if ( buffer.isEOF() )
        {
          std::ostringstream ost;
          ost << "Unterminated comment in line ";
          ost << startLine;
          throw SyntaxErrorException( ost.str(), *this );
        }
      }
    }
    else
    {
      std::ostringstream ost;
      ost << "unexpected character: '" << CurrentCh << "'";
	  throw SyntaxErrorException( ost.str(), *this );
    }

    SkipWhiteSpace();  // We may need to throw out
                       //  more white space/comments
                       // This is admittedly tail recursion...
  }
}

Token* Tokenizer::GetQuotedIdent() {
  GetCh();   // Throw out beginning '"'

  std::ostringstream ident;
  while ( '"' != CurrentCh ) {
    if( '\n' == CurrentCh )
      throw SyntaxErrorException( "Unterminated string constant", *this );

    ident << CurrentCh;
    GetCh();
  }
  GetCh();
  return new IdentToken( ident.str() );
}

//////////////////////////////////////////////////////////////////////////
//
// Token* Tokenizer::GetIdent method
//
//   GetIdent scans an identifier-like token.  It returns an
//   identifier or a reserved word token.
//

Token* Tokenizer::GetIdent() {
  // an IDENTIFIER or a RESERVED WORD token
  std::ostringstream ident;
  while (isalnum(CurrentCh) || '_' == CurrentCh || '-' == CurrentCh) { 
    // While we still have something that can
    ident << CurrentCh;
    GetCh();
  }
  return SearchReserved(ident.str());
}

//////////////////////////////////////////////////////////////////////////
//
// Token* Tokenizer::GetInt method
//
//   GetInt scans an integer.  It returns an integer token.
//

Token* Tokenizer::GetScalar() {
  // an INTEGER token
  string ret( "" );
  while (isdigit(CurrentCh) || '-' == CurrentCh || '.' == CurrentCh || 'e' == CurrentCh ) {
    ret += CurrentCh;
    GetCh();
  }
  return new ScalarToken( atof( ret.c_str() ) );
}

//////////////////////////////////////////////////////////////////////////
//
// Token* Tokenizer::GetPunct() method
//
//   Gets a punctuation token from input stream and returns it.
//

Token* Tokenizer::GetPunct() {
  Token* T;

  switch (CurrentCh) {
  case '(':  GetCh(); T = new Token(LPAREN);     break;
  case ')':  GetCh(); T = new Token(RPAREN);     break;
  case '{':  GetCh(); T = new Token(LBRACE);     break;
  case '}':  GetCh(); T = new Token(RBRACE);     break;
  case ',':  GetCh(); T = new Token(COMMA);      break;
  case '=':  GetCh(); T = new Token(EQUALS);     break;
  case ';':  GetCh(); T = new Token(SEMICOLON);  break;

  default:
    std::ostringstream ost;
    ost << "unexpected character: '" << CurrentCh << "'";
    throw SyntaxErrorException(ost.str(), *this);
  }

  return T;
}

//////////////////////////////////////////////////////////////////////////
//
// void Tokenizer::UnGet(Token*) method
//
//   UnGet returns the last read token to the input, where it will be
//   returned for the next Get call.  At most 1 token can be pushed back
//   at a time this way and this token is pointed to by the pointer
//   TokenToUnGet.  TokenToUnGet must be non null.

void Tokenizer::UnGet(Token* TokenToUnGet) {
  if (UnGetToken != NULL) {
    throw ParserFatalException("trying to UnGet more than one token");
  }
  UnGetToken = TokenToUnGet;
}

//////////////////////////////////////////////////////////////////////////
//
// Token* Tokenizer::Peek() method
//
//   Peek reads the next token and pushes it back on the token stream
//

const Token* Tokenizer::Peek() {
  Token* T = GetNext();
  UnGet(T);
  return T;
}

//////////////////////////////////////////////////////////////////////////
//
// Token* Tokenizer::Read(SYMBOL) method
//
//   Read gets the next token and checks that it's of the expected type.
//

auto_ptr<Token> Tokenizer::Read(SYMBOL kind) {
  auto_ptr<Token> T( Get() );
  if (T->kind() != kind) {
    string msg( getNameForToken( kind ) );
    msg.append( " expected, " );
	msg.append(getNameForToken( T->kind() ));
	msg.append(" found instead!");
    throw SyntaxErrorException(msg, *this);
  }
  return T;
}

//////////////////////////////////////////////////////////////////////////
//
// bool Tokenizer::CondRead(SYMBOL) method
//
//   CondRead gets the next token and checks that it's of the expected type.
//   If it is, then consume it and return true.  Otherwise, push it back
//   and return false.
//

bool Tokenizer::CondRead(SYMBOL kind) {
  const Token* T = Peek();
  if (T->kind() == kind) {
    Get( );
    return true;
  } else {
    return false;
  }
}

//////////////////////////////////////////////////////////////////////////
//
// Token* Tokenizer::SearchReserved(const string&) private method
//
//   SearchReserved() maps a character string to an IdentToken or one of
// several possible reserved word tokens, using a binary search on the
// ReservedWords structure.
//

//
// The list of all the Reserved words and their associated symbols,
// in alphabetical order so this can be searched using binary search.
//

typedef std::map<string, SYMBOL> ReservedWordsMap;

Token* Tokenizer::SearchReserved(const string& ident) const {
  SYMBOL tokSymbol = lookupReservedWord( ident );
  if( UNKNOWN == tokSymbol )
  {
    return new IdentToken( ident );
  }
  else
  {
    return new Token( tokSymbol );
  }
}

//////////////////////////////////////////////////////////////////////////
//
// bool Tokenizer::CondReadCh(char) private method
//
//   CondReadCh checks to see if the CurrentCh is the same as the argument.
// If so, CondReadCh eats that character (by calling GetCh())
// and returns true.  If not, just return false.
//

bool Tokenizer::CondReadCh(char c) {
  if (c == CurrentCh) {
    GetCh();
    return true;
  } else {
    return false;
  }
}
