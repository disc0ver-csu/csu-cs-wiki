#ifndef __TOKENIZER_H__

#define __TOKENIZER_H__

#include "Token.h"
#include "../fileio/buffer.h"

#include <string>
#include <memory>

// Needed to correct for annoying "feature" in MSVC's compiler
#pragma warning (disable: 4786)

using std::string;
using std::istream;
using std::auto_ptr;


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

class Tokenizer {
  public:
    Tokenizer(istream& fp, bool printTokens);

    // destructively read & return the next token, skipping over whitespace
    auto_ptr<Token> Get();

    // non-destructively get the next token, pushing it back to be read again
    const Token* Peek();

    // Get() the next token, and check that it's of the expected SYMBOL type
    auto_ptr<Token> Read(SYMBOL expected);

    // read the next token only if it matches the expected token type.
    // Return whether it matches.
    bool CondRead(SYMBOL expected);

    // display the current source line onto the screen.
    void PrintLine( ostream& out) const { buffer.PrintLine(out); }

    // return the column number/line number of the current token.
    int CurColumn() const { return TokenColumn; }
    int CurLine() const { return buffer.CurLine(); }

    // Repeatedly scan tokens and throw them away.  Useful if this is the
    // last phase to be executed
    void ScanProgram();

protected:
    // private methods:

    // push the argument token back onto the scanner's token stream;
    // it will be returned by the next Get/Peek/Read/CondRead call
    Token* GetNext();
    void UnGet(Token* t);

    Token* SearchReserved(const string&) const; // Convert ident string into token

    void GetCh() { CurrentCh = buffer.GetCh(); }
    bool CondReadCh(char expected);        // consume a character, if it matches

    void SkipWhiteSpace();        // skip spaces, tabs, newlines

    Token* GetPunct();            // scan punctuation token
    Token* GetScalar();           // scan integer token
    Token* GetIdent();            // scan identifier token
    Token* GetQuotedIdent();


    // private data:

    Buffer buffer;                // The file buffer
    char CurrentCh;               // The current character in the current line

    Token* UnGetToken;            // The token that has been "ungot"

    int TokenColumn;              // The column where the last read token starts,
                                  // for generating error messages

    bool _printTokens;            // printing flag
};

#endif

