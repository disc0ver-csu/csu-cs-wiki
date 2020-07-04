// token.h
// Defines the tokens that may be encountered in a .ray file;
// see tokenizer.{h,c} for details.

#ifndef __TOKEN_H__

#define __TOKEN_H__

#include <string>
#include <iostream>
#include <map>

#include "ParserException.h"


/* These are possible tokens we might encounter in a
   .ray file.  These include things like punctuation,
   keywords, etc.

   If you are adding your own token, you must add it 
   to the list below (I recommend at the bottom) and 
   also to the lookup table (see Token.cpp).  If you
   are adding a reserved word (you probably are) you
   need also to add it to the reserved words lookup 
   table in Token.cpp.
*/

enum SYMBOL {
  UNKNOWN,					// Placeholder
  EOFSYM,					// End of file
  SBT_RAYTRACER,

  IDENT,					// Ident (gets enclosed in quotes in trace files)
  SCALAR,				 	// Scalar values
  SYMTRUE,
  SYMFALSE,

  LPAREN, RPAREN,			// Punctuation
  LBRACE, RBRACE,
  COMMA,
  EQUALS,
  SEMICOLON,

  CAMERA,					// camera primitive
  POINT_LIGHT,				// lights
  DIRECTIONAL_LIGHT,
  AMBIENT_LIGHT,

  CONSTANT_ATTENUATION_COEFF,	// Terms affecting the intensity dropoff
  LINEAR_ATTENUATION_COEFF,		// of point lights (see the PointLight 
  QUADRATIC_ATTENUATION_COEFF,	// class)

  SPHERE,					// primitives
  BOX,
  SQUARE,
  CYLINDER,
  CONE,
  TRIMESH,  

  POSITION, VIEWDIR,		// keywords affecting primitives
  UPDIR, ASPECTRATIO,
  FOV,
  COLOR,
  DIRECTION,
  CAPPED,
  HEIGHT,
  BOTTOM_RADIUS,
  TOP_RADIUS,
  QUATERNIAN,               // ???

  POLYPOINTS, NORMALS,			// keywords affecting polygons
  MATERIALS, FACES,
  GENNORMALS,

  TRANSLATE, SCALE,			// Transforms
  ROTATE, TRANSFORM,

  MATERIAL, 				// Material settings
  EMISSIVE, AMBIENT, 
  SPECULAR, REFLECTIVE,
  DIFFUSE, TRANSMISSIVE,
  SHININESS, INDEX,
  NAME,
  MAP,
  LOOK_AT
};

// Helper functions
string getNameForToken( const SYMBOL kind );
SYMBOL lookupReservedWord( const string& name );

class Token {
  public:
    Token(SYMBOL kind) : _kind( kind ) { }

    SYMBOL kind() const { return _kind; }

    // Note that these errors should not ever be encountered at runtime,
    // and signify parser bugs of some kind.
    virtual std::string ident() const   
      { throw ParserFatalException("not an IdentToken"); return std::string(); }
    virtual double value() const   
      { throw ParserFatalException("not a ScalarToken"); return 0.0; }


    // Utility functions
    virtual void Print(std::ostream& out) const;
    virtual void Print() const;
    virtual string toString() const;

	virtual ~Token() {}
  protected:
    const SYMBOL _kind;
};

class IdentToken : public Token {
  public:
    IdentToken(std::string ident) : Token(IDENT), _ident( ident ) { 
    }

    std::string ident() const { return _ident; }

    string toString() const;

  protected:
    const std::string _ident;
};

class ScalarToken : public Token {
  public:
    ScalarToken(double value) : Token(SCALAR), _value( value ) { }
    
    double value() const { return _value; }

    string toString() const;

  protected:
    const double _value;
};


#endif
