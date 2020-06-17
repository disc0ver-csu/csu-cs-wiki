#pragma warning (disable: 4786)

#include <stdio.h>
#include "Token.h"

#include <map>
#include <sstream>

#include <iostream>



using std::ostringstream;
using std::ostream;
using std::endl;

/* This function is more of a convenience than
   anything; for debugging purposes and intelligent
   error messages we'd like to be returning something
   other than "token #2843" for human-readable output;
   this lookup table solves that.

   If you add tokens, simply add them to this table
   with 
     tokenNames[ MY_TOKEN_NAME ] = "string representation";
*/ 
string getNameForToken( const SYMBOL kind )
{
  static std::map<int, string> tokenNames;

  if( tokenNames.empty() )
  {
    tokenNames[ EOFSYM ]            = "EOF";
    tokenNames[ SBT_RAYTRACER ]     = "SBT-raytracer";
    tokenNames[ IDENT ]             = "Identifier";
    tokenNames[ SCALAR ]            = "Scalar";
    tokenNames[ SYMTRUE ]           = "true";
    tokenNames[ SYMFALSE ]          = "false";
    tokenNames[ LPAREN ]            = "Left paren";
    tokenNames[ RPAREN ]            = "Right paren";
    tokenNames[ LBRACE ]            = "Left brace";
    tokenNames[ RBRACE ]            = "Right brace";
    tokenNames[ COMMA ]             = "Comma";
    tokenNames[ EQUALS ]            = "Equals";
    tokenNames[ SEMICOLON ]         = "Semicolon";
    tokenNames[ CAMERA ]            = "camera";
	tokenNames[ AMBIENT_LIGHT ]     = "ambient_light";
    tokenNames[ POINT_LIGHT ]       = "point_light";
    tokenNames[ DIRECTIONAL_LIGHT ] = "directional_light";
    tokenNames[ CONSTANT_ATTENUATION_COEFF ] = "constant_attenuation_coeff";
    tokenNames[ LINEAR_ATTENUATION_COEFF ] = "linear_attenuation_coeff";
    tokenNames[ QUADRATIC_ATTENUATION_COEFF ] = "quadratic_attenuation_coeff";
    tokenNames[ SPHERE ]            = "sphere";
    tokenNames[ BOX ]               = "box";
    tokenNames[ SQUARE ]            = "square";
    tokenNames[ CYLINDER ]          = "cylinder";
    tokenNames[ CONE ]              = "cone";
    tokenNames[ TRIMESH ]           = "trimesh";
    tokenNames[ POSITION ]          = "position";
    tokenNames[ VIEWDIR ]           = "viewdir";
    tokenNames[ UPDIR ]             = "updir";
    tokenNames[ ASPECTRATIO ]       = "aspectratio";
    tokenNames[ COLOR ]             = "color";
    tokenNames[ DIRECTION ]         = "direction";
    tokenNames[ CAPPED ]            = "capped";
    tokenNames[ HEIGHT ]            = "height";
    tokenNames[ BOTTOM_RADIUS ]     = "bottom_radius";
    tokenNames[ TOP_RADIUS ]        = "top_radius";
    tokenNames[ QUATERNIAN ]        = "quaternian";
    tokenNames[ POLYPOINTS ]        = "points";
    tokenNames[ HEIGHT ]            = "height";
    tokenNames[ NORMALS ]           = "normals";
    tokenNames[ MATERIALS ]         = "materials";
    tokenNames[ FACES ]             = "faces";
    tokenNames[ TRANSLATE ]         = "translate";
    tokenNames[ SCALE ]             = "scale";
    tokenNames[ ROTATE ]            = "rotate";
    tokenNames[ TRANSFORM ]         = "transform";
    tokenNames[ MATERIAL ]          = "material";
    tokenNames[ EMISSIVE ]          = "emissive";
    tokenNames[ AMBIENT ]           = "ambient";
    tokenNames[ SPECULAR ]          = "specular";
    tokenNames[ REFLECTIVE ]        = "reflective";
    tokenNames[ DIFFUSE ]           = "diffuse";
    tokenNames[ TRANSMISSIVE ]      = "transmissive";
    tokenNames[ SHININESS ]         = "shininess";
    tokenNames[ INDEX ]             = "index";
    tokenNames[ NAME ]              = "name";
    tokenNames[ MAP ]               = "map";
	tokenNames[ LOOK_AT ]			= "look_at";
  }
  // search tokenNames table
  std::map<int, string>::const_iterator itr = 
    tokenNames.find( kind );
  if( itr == tokenNames.end() )
    return string("Unknown token type");
  else
    return (*itr).second;

}

/* This function is used by the parser to lookup 
   "reserved" words (i.e., things like "sphere", "cone",
   etc.).  What you will be concerned with is adding
   entries to the reservedWords map as appropriate;
   if you add a new reserved word to the parser, 
   simply add it to the list below.  I.e., if you had
   the reserved word "regular17gon" as your new primitive,
   for example, and the SYMBOL representing it was
   "SEVENTEENGON", you'd add the line
      reservedWords["regular17gon"] = SEVENTEENGON;
   to the list below.
*/
SYMBOL lookupReservedWord(const string& ident) {
  static std::map<string, SYMBOL> reservedWords;

  if( reservedWords.empty() )
  {
    reservedWords["ambient_light"] = AMBIENT_LIGHT;
    reservedWords["ambient"] = AMBIENT;
    reservedWords["aspectratio"] = ASPECTRATIO;
    reservedWords["bottom_radius"] = BOTTOM_RADIUS;
    reservedWords["box"] = BOX;
    reservedWords["camera"] = CAMERA;
    reservedWords["capped"] = CAPPED;
    reservedWords["color"] = COLOR;
    reservedWords["colour"] = COLOR;
    reservedWords["cone"] = CONE;
    reservedWords["constant_attenuation_coeff"] = CONSTANT_ATTENUATION_COEFF;
    reservedWords["cylinder"] = CYLINDER;
    reservedWords["diffuse"] = DIFFUSE;
    reservedWords["direction"] = DIRECTION;
    reservedWords["directional_light"] = DIRECTIONAL_LIGHT;
    reservedWords["emissive"] = EMISSIVE;
    reservedWords["faces"] = FACES;
    reservedWords["false"] = SYMFALSE;
    reservedWords["fov"] = FOV;
    reservedWords["gennormals"] = GENNORMALS;
    reservedWords["height"] = HEIGHT;
    reservedWords["index"] = INDEX;
    reservedWords["linear_attenuation_coeff"] = LINEAR_ATTENUATION_COEFF;
    reservedWords["material"] = MATERIAL;
    reservedWords["materials"] = MATERIALS;
    reservedWords["map"] = MAP;
    reservedWords["name"] = NAME;
    reservedWords["normals"] = NORMALS;
    reservedWords["point_light"] = POINT_LIGHT;
    reservedWords["points"] = POLYPOINTS;
    reservedWords["polymesh"] = TRIMESH;
    reservedWords["position"] = POSITION;
    reservedWords["quadratic_attenuation_coeff"] = QUADRATIC_ATTENUATION_COEFF;
    reservedWords["quaternian"] = QUATERNIAN;
    reservedWords["reflective"] = REFLECTIVE;
    reservedWords["rotate"] = ROTATE;
    reservedWords["SBT-raytracer"] = SBT_RAYTRACER;
    reservedWords["scale"] = SCALE;
    reservedWords["shininess"] = SHININESS;
    reservedWords["specular"] = SPECULAR;
    reservedWords["sphere"] = SPHERE;
    reservedWords["square"] = SQUARE;
    reservedWords["top_radius"] = TOP_RADIUS;
    reservedWords["transform"] = TRANSFORM;
    reservedWords["translate"] = TRANSLATE;
    reservedWords["transmissive"] = TRANSMISSIVE;
    reservedWords["trimesh"] = TRIMESH;
    reservedWords["true"] = SYMTRUE;
    reservedWords["updir"] = UPDIR;
    reservedWords["viewdir"] = VIEWDIR;
	reservedWords["look_at"] = LOOK_AT;

  }

  // search ReservedWords table
  std::map<string, SYMBOL>::const_iterator itr = 
    reservedWords.find( ident );
  if( itr == reservedWords.end() )
    return UNKNOWN;
  else
    return (*itr).second;
}

string Token::toString() const
{
  return getNameForToken( kind() );
}

void Token::Print( ostream& out ) const {
  out << toString();
}

void Token::Print( ) const {
  Print( std::cout );
}

string IdentToken::toString( ) const {
  ostringstream oss( Token::toString() );
  oss << ": \"" << _ident << "\"";
  return oss.str();
}

string ScalarToken::toString( ) const {
  ostringstream oss( Token::toString() );
  oss << ": " << _value;
  return oss.str();
}
 
