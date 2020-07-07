#pragma warning (disable: 4786)

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include "Parser.h"
#include "Tokenizer.h"
#include "../scene/scene.h"
#include "../scene/material.h"

using namespace std;

template< typename T >
auto_ptr<T> wrap_auto_ptr( T* pointer )
{
	return auto_ptr<T>( pointer );
}

Scene* Parser::parseScene()
{
  _tokenizer.Read(SBT_RAYTRACER);

  auto_ptr<Token> versionNumber( _tokenizer.Read(SCALAR) );

  if( versionNumber->value() > 1.1 )
  {
    ostringstream ost;
    ost << "SBT-raytracer version number " << versionNumber->value() << 
      " too high; only able to parser v1.1 and below.";
    throw ParserException( ost.str() );
  }

  Scene* scene = new Scene;
  auto_ptr<Material> mat( new Material );

  for( ;; )
  {
    const Token* t = _tokenizer.Peek();

    switch( t->kind() )
    {
      case SPHERE:
      case BOX:
      case SQUARE:
      case CYLINDER:
      case CONE:
      case TRIMESH:
      case TRANSLATE:
      case ROTATE:
      case SCALE:
      case TRANSFORM:
      case LBRACE:
         parseTransformableElement(scene, &scene->transformRoot, *mat);
      break;
      case POINT_LIGHT:
         scene->add( parsePointLight( scene ) );
         break;
      case DIRECTIONAL_LIGHT:
         scene->add( parseDirectionalLight( scene ) );
         break;
      case AMBIENT_LIGHT:
         parseAmbientLight( scene );
         break;
      case CAMERA:
         parseCamera( scene );
         break;
      case MATERIAL:
		 {
           auto_ptr<Material> temp( parseMaterialExpression( scene, *mat ));
		   mat = temp;
		 }
         break;
      case SEMICOLON:
         _tokenizer.Read( SEMICOLON );
         break;
      case EOFSYM:
         return scene;
      default:
         throw SyntaxErrorException( "Expected: geometry, camera, or light information", _tokenizer );
    }
  }
}

void Parser::parseCamera( Scene* scene )
{
	bool hasViewDir( false ), hasUpDir( false );
	bool hasLookAt( false ), hasPosition( false );
	Vec3d viewDir, upDir, pos;

	_tokenizer.Read( CAMERA );
	_tokenizer.Read( LBRACE );

	for( ;; )
	{
		const Token* t = _tokenizer.Peek();

		Vec4d quaternian;
		switch( t->kind() )
		{
		case POSITION:
			pos = parseVec3dExpression();
			scene->getCamera().setEye( pos );
			hasPosition = true;
			break;

		case FOV:
			scene->getCamera().setFOV( parseScalarExpression() );
			break;

		case QUATERNIAN:
			quaternian = parseVec4dExpression();
			scene->getCamera().setLook(
				quaternian[0], quaternian[1], quaternian[2], quaternian[3] );
			break;

		case ASPECTRATIO:
			scene->getCamera().setAspectRatio( parseScalarExpression() );
			break;

		case VIEWDIR:
			viewDir = parseVec3dExpression();
			hasViewDir = true;
			break;

		case LOOK_AT:
			viewDir = parseVec3dExpression();
			hasLookAt = true;
			break;

		case UPDIR:
			upDir = parseVec3dExpression();
			hasUpDir = true;
			break;

		case RBRACE:
			// semantic checks
			if( hasLookAt ) {
				if( !hasPosition )
					scene->getCamera().setLookSimple(viewDir, Vec3d(1,0,0));
				else
				{
					if ( !scene->getCamera().setLookSimple(viewDir, pos) )
						throw SyntaxErrorException( "Expected: cannot look at position of the camera", _tokenizer );
					if( hasUpDir )
						scene->getCamera().setLook( scene->getCamera().getLook(), upDir );
				}
			}
			else if( hasViewDir )
			{
				if( !hasUpDir )
					throw SyntaxErrorException( "Expected: 'updir'", _tokenizer );
				scene->getCamera().setLook( viewDir, upDir );
			}
			else if( hasUpDir ) {
				if( !hasViewDir && !hasLookAt )
					throw SyntaxErrorException( "Expected: 'viewdir'", _tokenizer );
			}

			_tokenizer.Read( RBRACE );
			return;

		default:
			throw SyntaxErrorException( "Expected: camera attribute", _tokenizer );
		}
	}
}

void Parser::parseTransformableElement( Scene* scene, TransformNode* transform, const Material& mat )
{
    const Token* t = _tokenizer.Peek();
    switch( t->kind() )
    {
      case SPHERE:
      case BOX:
      case SQUARE:
      case CYLINDER:
      case CONE:
      case TRIMESH:
      case TRANSLATE:
      case ROTATE:
      case SCALE:
      case TRANSFORM:
         parseGeometry(scene, transform, mat);
      break;
      case LBRACE:
         parseGroup(scene, transform, mat);
         break;
      default:
         throw SyntaxErrorException( "Expected: transformable element", _tokenizer );
    }
}

// parse a group of geometry, i.e., enclosed in {} blocks.
void Parser::parseGroup(Scene* scene, TransformNode* transform, const Material& mat )
{
  auto_ptr<Material> newMat;
  _tokenizer.Read( LBRACE );
  for( ;; )
  {
    const Token* t = _tokenizer.Peek();
    switch( t->kind() )
    {
      case SPHERE:
      case BOX:
      case SQUARE:
      case CYLINDER:
      case CONE:
      case TRIMESH:
      case TRANSLATE:
      case ROTATE:
      case SCALE:
      case TRANSFORM:
      case LBRACE:
        parseTransformableElement( scene, transform, newMat.get() ? *newMat : mat );
        break;
      case RBRACE:
        _tokenizer.Read( RBRACE );
        return;
      case MATERIAL:
		{
          auto_ptr<Material> temp(parseMaterialExpression(scene, mat));
          newMat = temp;
		}
      default:
        throw SyntaxErrorException( "Expected: '}' or geometry", _tokenizer );
    }
  }
}


void Parser::parseGeometry(Scene* scene, TransformNode* transform, const Material& mat)
{
  const Token* t = _tokenizer.Peek();
  switch( t->kind() )
  {
    case SPHERE:
      parseSphere(scene, transform, mat);
      return;
    case BOX:
      parseBox(scene, transform, mat);
      return;
    case SQUARE:
      parseSquare(scene, transform, mat);
      return;
    case CYLINDER:
      parseCylinder(scene, transform, mat);
      return;
    case CONE:
      parseCone(scene, transform, mat);
      return;
    case TRIMESH:
      parseTrimesh(scene, transform, mat);
      return;
    case TRANSLATE:
      parseTranslate(scene, transform, mat);
      return;
    case ROTATE:
      parseRotate(scene, transform, mat);
      return;
    case SCALE:
      parseScale(scene, transform, mat);
      return;
    case TRANSFORM:
      parseTransform(scene, transform, mat);
      return;
    default:
      throw ParserFatalException( "Unrecognized geometry type." );
  }
}


void Parser::parseTranslate(Scene* scene, TransformNode* transform, const Material& mat)
{
  _tokenizer.Read( TRANSLATE );
  _tokenizer.Read( LPAREN );
  double x = parseScalar();
  _tokenizer.Read( COMMA );
  double y = parseScalar();
  _tokenizer.Read( COMMA );
  double z = parseScalar();
  _tokenizer.Read( COMMA );

  // Parse child geometry
  parseTransformableElement( scene, 
    transform->createChild( Mat4d::createTranslation( x, y, z ) ), mat );

  _tokenizer.Read( RPAREN );
  _tokenizer.CondRead(SEMICOLON);

  return;
}

void Parser::parseRotate(Scene* scene, TransformNode* transform, const Material& mat)
{
  _tokenizer.Read( ROTATE );
  _tokenizer.Read( LPAREN );
  double x = parseScalar();
  _tokenizer.Read( COMMA );
  double y = parseScalar();
  _tokenizer.Read( COMMA );
  double z = parseScalar();
  _tokenizer.Read( COMMA );
  double w = parseScalar();
  _tokenizer.Read( COMMA );

  // Parse child geometry
  parseTransformableElement( scene, 
    transform->createChild( Mat4d::createRotation( w, x, y, z ) ), mat );

  _tokenizer.Read( RPAREN );
  _tokenizer.CondRead(SEMICOLON);

  return;
}


void Parser::parseScale(Scene* scene, TransformNode* transform, const Material& mat)
{
  _tokenizer.Read( SCALE );
  _tokenizer.Read( LPAREN );
  double x, y, z;

  x = parseScalar();
  _tokenizer.Read( COMMA );

  const Token* next = _tokenizer.Peek();
  if( SCALAR == next->kind() )
  {
     y = parseScalar();
     _tokenizer.Read( COMMA );
     z = parseScalar();
     _tokenizer.Read( COMMA );
  }
  else
  {
     y = x;
     z = x;
  }

  // Parse child geometry
  parseTransformableElement( scene, 
    transform->createChild( Mat4d::createScale( x, y, z ) ), mat );

  _tokenizer.Read( RPAREN );
  _tokenizer.CondRead(SEMICOLON);

  return;
}


void Parser::parseTransform(Scene* scene, TransformNode* transform, const Material& mat)
{
  _tokenizer.Read( TRANSFORM );
  _tokenizer.Read( LPAREN );

  Vec4d row1 = parseVec4d();
  _tokenizer.Read( COMMA );
  Vec4d row2 = parseVec4d();
  _tokenizer.Read( COMMA );
  Vec4d row3 = parseVec4d();
  _tokenizer.Read( COMMA );
  Vec4d row4 = parseVec4d();
  _tokenizer.Read( COMMA );

  parseTransformableElement( scene, 
    transform->createChild( Mat4d(row1, row2, row3, row4) ), mat );

  _tokenizer.Read( RPAREN );
  _tokenizer.CondRead(SEMICOLON);

  return;
}

void Parser::parseSphere(Scene* scene, TransformNode* transform, const Material& mat)
{
  Sphere* sphere = 0;
  Material* newMat = 0;

  _tokenizer.Read( SPHERE );
  _tokenizer.Read( LBRACE );

  for( ;; )
  {
    const Token* t = _tokenizer.Peek();

    switch( t->kind() )
    {
      case MATERIAL:
        delete newMat;
        newMat = parseMaterialExpression( scene, mat );
        break;
      case NAME:
        parseIdentExpression();
        break;
      case RBRACE:
        _tokenizer.Read( RBRACE );
        sphere = new Sphere(scene, newMat ? newMat : new Material(mat));
        sphere->setTransform( transform );
        scene->add( sphere );
        return;
      default:
        throw SyntaxErrorException( "Expected: sphere attributes", _tokenizer );
        
    }
  }
}

void Parser::parseBox(Scene* scene, TransformNode* transform, const Material& mat)
{
  Box* box = 0;

  _tokenizer.Read( BOX );
  _tokenizer.Read( LBRACE );

  Material* newMat = 0;
  for( ;; )
  {
    const Token* t = _tokenizer.Peek();

    switch( t->kind() )
    {
      case MATERIAL:
        delete newMat;
        newMat = parseMaterialExpression( scene, mat );
        break;
      case NAME:
        parseIdentExpression();
        break;
      case RBRACE:
         _tokenizer.Read( RBRACE );
        box = new Box(scene, newMat ? newMat : new Material(mat) );
        box->setTransform( transform );
        scene->add( box );
        return;
      default:
        throw SyntaxErrorException( "Expected: box attributes", _tokenizer );
        
    }
  }
}

void Parser::parseSquare(Scene* scene, TransformNode* transform, const Material& mat)
{
  Square* square = 0;
  Material* newMat = 0;

  _tokenizer.Read( SQUARE );
  _tokenizer.Read( LBRACE );

  for( ;; )
  {
    const Token* t = _tokenizer.Peek();

    switch( t->kind() )
    {
      case MATERIAL:
        delete newMat;
        newMat = parseMaterialExpression( scene, mat );
        break;
      case NAME:
        parseIdentExpression();
        break;
      case RBRACE:
         _tokenizer.Read( RBRACE );
        square = new Square(scene, newMat ? newMat : new Material(mat));
        square->setTransform( transform );
        scene->add( square );
        return;
      default:
        throw SyntaxErrorException( "Expected: square attributes", _tokenizer );
        
    }
  }
}

void Parser::parseCylinder(Scene* scene, TransformNode* transform, const Material& mat)
{
  Cylinder* cylinder = 0;
  Material* newMat = 0;

  _tokenizer.Read( CYLINDER );
  _tokenizer.Read( LBRACE );

  for( ;; )
  {
    const Token* t = _tokenizer.Peek();

    switch( t->kind() )
    {
      case MATERIAL:
        delete newMat;
        newMat = parseMaterialExpression( scene, mat );
        break;
      case NAME:
        parseIdentExpression();
        break;
      case RBRACE:
         _tokenizer.Read( RBRACE );
        cylinder = new Cylinder(scene, newMat ? newMat : new Material(mat));
        cylinder->setTransform( transform );
        scene->add( cylinder );
        return;
      default:
        throw SyntaxErrorException( "Expected: cylinder attributes", _tokenizer );
    }
  }

}

void Parser::parseCone(Scene* scene, TransformNode* transform, const Material& mat)
{
  _tokenizer.Read( CONE );
  _tokenizer.Read( LBRACE );

  Cone* cone;
  Material* newMat = 0;

  double bottomRadius = 1.0;
  double topRadius = 0.0;
  double height = 1.0;
  bool capped = true;				// Capped by default

  for( ;; )
  {
    const Token* t = _tokenizer.Peek();

    switch( t->kind() )
    {
      case MATERIAL:
        delete newMat;
        newMat = parseMaterialExpression( scene, mat );
        break;
      case NAME:
         parseIdentExpression();
         break;
      case CAPPED:
        capped = parseBooleanExpression();
        break;
      case BOTTOM_RADIUS:
        bottomRadius = parseScalarExpression();
        break;
      case TOP_RADIUS:
        topRadius = parseScalarExpression();
        break;
      case HEIGHT:
        height = parseScalarExpression();
        break;
      case RBRACE:
        _tokenizer.Read( RBRACE );
        cone = new Cone( scene, newMat ? newMat : new Material(mat), 
          height, bottomRadius, topRadius, capped );
        cone->setTransform( transform );
        scene->add( cone );
        return;
      default:
        throw SyntaxErrorException( "Expected: cone attributes", _tokenizer );
    }
  }
}

void Parser::parseTrimesh(Scene* scene, TransformNode* transform, const Material& mat)
{
  Trimesh* tmesh = new Trimesh( scene, new Material(mat), transform);

  _tokenizer.Read( TRIMESH );
  _tokenizer.Read( LBRACE );

  bool generateNormals( false );
  list<Vec3d> faces;

  char* error;
  for( ;; )
  {
    const Token* t = _tokenizer.Peek();

    switch( t->kind() )
    {
      case GENNORMALS:
        _tokenizer.Read( GENNORMALS );
        _tokenizer.Read( SEMICOLON );
        generateNormals = true;
        break;

      case MATERIAL:
        tmesh->setMaterial( parseMaterialExpression( scene, mat ) );
        break;

      case NAME:
         parseIdentExpression();
         break;

      case MATERIALS:
        _tokenizer.Read( MATERIALS );
        _tokenizer.Read( EQUALS );
        _tokenizer.Read( LPAREN );
        if( RPAREN != _tokenizer.Peek()->kind() )
        {
          tmesh->addMaterial( parseMaterial( scene, tmesh->getMaterial() ) );
          for( ;; )
          {
             const Token* nextToken = _tokenizer.Peek();
             if( RPAREN == nextToken->kind() )
               break;
             _tokenizer.Read( COMMA );
             tmesh->addMaterial( parseMaterial( scene, tmesh->getMaterial() ) );
          }
        }
        _tokenizer.Read( RPAREN );
        _tokenizer.Read( SEMICOLON );
        break;

      case NORMALS:
        _tokenizer.Read( NORMALS );
        _tokenizer.Read( EQUALS );
        _tokenizer.Read( LPAREN );
        if( RPAREN != _tokenizer.Peek()->kind() )
        {
          tmesh->addNormal( parseVec3d() );
          for( ;; )
          {
             const Token* nextToken = _tokenizer.Peek();
             if( RPAREN == nextToken->kind() )
               break;
             _tokenizer.Read( COMMA );
             tmesh->addNormal( parseVec3d() );
          }
        }
        _tokenizer.Read( RPAREN );
        _tokenizer.Read( SEMICOLON );
        break;

      case FACES:
        _tokenizer.Read( FACES );
        _tokenizer.Read( EQUALS );
        _tokenizer.Read( LPAREN );
        if( RPAREN != _tokenizer.Peek()->kind() )
        {
          parseFaces( faces );
          for( ;; )
          {
             const Token* nextToken = _tokenizer.Peek();
             if( RPAREN == nextToken->kind() )
               break;
             _tokenizer.Read( COMMA );
             parseFaces( faces );
          }
        }
        _tokenizer.Read( RPAREN );
        _tokenizer.Read( SEMICOLON );
        break;

      case POLYPOINTS:
        _tokenizer.Read( POLYPOINTS );
        _tokenizer.Read( EQUALS );
        _tokenizer.Read( LPAREN );
        if( RPAREN != _tokenizer.Peek()->kind() )
        {
          tmesh->addVertex( parseVec3d() );
          for( ;; )
          {
             const Token* nextToken = _tokenizer.Peek();
             if( RPAREN == nextToken->kind() )
               break;
             _tokenizer.Read( COMMA );
             tmesh->addVertex( parseVec3d() );
          }
        }
        _tokenizer.Read( RPAREN );
        _tokenizer.Read( SEMICOLON );
        break;


      case RBRACE:
      {
        _tokenizer.Read( RBRACE );

        // Now add all the faces into the trimesh, since hopefully
        // the vertices have been parsed out
        for( list<Vec3d>::const_iterator vitr = faces.begin(); vitr != faces.end(); vitr++ )
        {
          if( !tmesh->addFace((int) (*vitr)[0], (int) (*vitr)[1], (int) (*vitr)[2] ) )
          {
            ostringstream oss;
            oss << "Bad face in trimesh: (" << (*vitr)[0] << ", " << (*vitr)[1] << 
              ", " << (*vitr)[2] << ")";
            throw ParserException( oss.str() );
          }
        }

        if( generateNormals )
          tmesh->generateNormals();

        if( error = tmesh->doubleCheck() )
          throw ParserException( error );

        scene->add( tmesh );
        return;
      }

      default:
        throw SyntaxErrorException( "Expected: trimesh attributes", _tokenizer );
    }
  }
}

void Parser::parseFaces( list< Vec3d >& faces )
{
  list< double > points = parseScalarList();

  // triangulate here and now.  assume the poly is
  // concave and we can triangulate using an arbitrary fan
  if( points.size() < 3 )
     throw SyntaxErrorException( "Faces must have at least 3 vertices.", _tokenizer );

  list<double>::const_iterator i = points.begin();
  double a = (*i++);
  double b = (*i++);
  while( i != points.end() )
  {
    double c = (*i++);
    faces.push_back( Vec3d( a, b, c ) );
    b = c;
  }
}

// Ambient lights are a bit special in that we don't actually
// create a separate Light for each ambient light; instead
// we simply sum all the ambient intensities and put them in
// the scene as the I_a coefficient.
void Parser::parseAmbientLight( Scene* scene )
{
  _tokenizer.Read( AMBIENT_LIGHT );
  _tokenizer.Read( LBRACE );
  if( _tokenizer.Peek()->kind() != COLOR )
    throw SyntaxErrorException( "Expected color attribute", _tokenizer );

  scene->addAmbient( parseVec3dExpression() );
  _tokenizer.Read( RBRACE );
  return;
}

PointLight* Parser::parsePointLight( Scene* scene )
{
  Vec3d position;
  Vec3d color;

  // Default to the 'default' system
  float constantAttenuationCoefficient = 0.0f;
  float linearAttenuationCoefficient = 0.0f;
  float quadraticAttenuationCoefficient = 1.0f;

  bool hasPosition( false ), hasColor( false );
  
  _tokenizer.Read( POINT_LIGHT );
  _tokenizer.Read( LBRACE );

  for( ;; )
  {
     const Token* t = _tokenizer.Peek();
     switch( t->kind() )
     {
       case POSITION:
         if( hasPosition )
           throw SyntaxErrorException( "Repeated 'position' attribute", _tokenizer );
         position = parseVec3dExpression();
         hasPosition = true;
         break;

       case COLOR:
         if( hasColor )
            throw SyntaxErrorException( "Repeated 'color' attribute", _tokenizer );
         color = parseVec3dExpression();
         hasColor = true;
         break;

       case CONSTANT_ATTENUATION_COEFF:
         constantAttenuationCoefficient = parseScalarExpression();
		 break;

       case LINEAR_ATTENUATION_COEFF:
         linearAttenuationCoefficient = parseScalarExpression();
		 break;
         
       case QUADRATIC_ATTENUATION_COEFF:
         quadraticAttenuationCoefficient = parseScalarExpression();
		 break;

       case RBRACE:
         if( !hasColor )
           throw SyntaxErrorException( "Expected: 'color'", _tokenizer );
         if( !hasPosition )
           throw SyntaxErrorException( "Expected: 'position'", _tokenizer );
         _tokenizer.Read( RBRACE );
         return new PointLight( scene, position, color, constantAttenuationCoefficient, 
           linearAttenuationCoefficient, quadraticAttenuationCoefficient );

        default:
          throw SyntaxErrorException( 
			  "expecting 'position' or 'color' attribute, or 'constant_attenuation_coeff', 'linear_attenuation_coeff', or 'quadratic_attenuation_coeff'", 
            _tokenizer );
     }
  }
}

DirectionalLight* Parser::parseDirectionalLight( Scene* scene )
{
  Vec3d direction;
  Vec3d color;

  bool hasDirection( false ), hasColor( false );

  _tokenizer.Read( DIRECTIONAL_LIGHT );
  _tokenizer.Read( LBRACE );

  for( ;; )
  {
     const Token* t = _tokenizer.Peek();
     switch( t->kind() )
     {
       case DIRECTION:
         if( hasDirection )
           throw SyntaxErrorException( "Repeated 'direction' attribute", _tokenizer );
         direction = parseVec3dExpression();
         hasDirection = true;
         break;

       case COLOR:
         if( hasColor )
            throw SyntaxErrorException( "Repeated 'color' attribute", _tokenizer );
         color = parseVec3dExpression();
         hasColor = true;
         break;

        case RBRACE:
          if( !hasColor )
            throw SyntaxErrorException( "Expected: 'color'", _tokenizer );
          if( !hasDirection )
            throw SyntaxErrorException( "Expected: 'position'", _tokenizer );
          _tokenizer.Read( RBRACE );
          return new DirectionalLight( scene, direction, color );

        default:
          throw SyntaxErrorException( "expecting 'position' or 'color' attribute", 
            _tokenizer );
     }
  }
}

// These ought to be done with template member functions, but compiler support for
// these is rather iffy...
double Parser::parseScalarExpression()
{
  // Throw out first token, which precedes the = sign
  _tokenizer.Get();
  _tokenizer.Read(EQUALS);
  double value( parseScalar() );
  _tokenizer.CondRead(SEMICOLON);
  return value;
}

bool Parser::parseBooleanExpression()
{
  _tokenizer.Get();
  _tokenizer.Read(EQUALS);
  bool value( parseBoolean() ); 
  _tokenizer.CondRead(SEMICOLON);
  return value;
}

Vec3d Parser::parseVec3dExpression()
{
  _tokenizer.Get();
  _tokenizer.Read(EQUALS);
  Vec3d value( parseVec3d() );
  _tokenizer.CondRead(SEMICOLON);
  return value;
}

Vec4d Parser::parseVec4dExpression()
{
  _tokenizer.Get();
  _tokenizer.Read(EQUALS);
  Vec4d value( parseVec4d() );
  _tokenizer.CondRead(SEMICOLON);
  return value;
}

Material* Parser::parseMaterialExpression( Scene* scene, const Material& parent )
{
  _tokenizer.Read(MATERIAL);
  _tokenizer.Read(EQUALS);
  Material* mat = parseMaterial( scene, parent );
  _tokenizer.CondRead( SEMICOLON );
  return mat;
}

string Parser::parseIdentExpression()
{
  _tokenizer.Get();
  _tokenizer.Read(EQUALS);
  string value( parseIdent() );
  _tokenizer.CondRead(SEMICOLON);
  return value;
}

double Parser::parseScalar()
{
  auto_ptr<Token> scalar( _tokenizer.Read( SCALAR ) );

  return scalar->value();
}

string Parser::parseIdent()
{
  auto_ptr<Token> scalar( _tokenizer.Read( IDENT ) );

  return scalar->ident();
}


list<double> Parser::parseScalarList()
{
  list<double> ret;

  _tokenizer.Read( LPAREN );
  if( RPAREN != _tokenizer.Peek()->kind() )
  {
    ret.push_back( parseScalar() );
    for( ;; )
    {
      const Token* nextToken = _tokenizer.Peek();
      if( RPAREN == nextToken->kind() )
        break;
      _tokenizer.Read( COMMA );
      ret.push_back( parseScalar() );
    }
  }
  _tokenizer.Read( RPAREN );

  return ret;

}

bool Parser::parseBoolean()
{
  const Token* next = _tokenizer.Peek();
  if( SYMTRUE == next->kind() )
  {
     _tokenizer.Read(SYMTRUE);
     return true;
  }
  if( SYMFALSE == next->kind() )
  {
     _tokenizer.Read(SYMFALSE);
     return false;
  }
  throw SyntaxErrorException( "Expected boolean", _tokenizer );
}

Vec3d Parser::parseVec3d()
{
  _tokenizer.Read( LPAREN );
  auto_ptr<Token> value1( _tokenizer.Read( SCALAR ) );
  _tokenizer.Read( COMMA );
  auto_ptr<Token> value2( _tokenizer.Read( SCALAR ) );
  _tokenizer.Read( COMMA );
  auto_ptr<Token> value3( _tokenizer.Read( SCALAR ) );
  _tokenizer.Read( RPAREN );

  return Vec3d( value1->value(), 
    value2->value(), 
    value3->value() );
}

Vec4d Parser::parseVec4d()
{
  _tokenizer.Read( LPAREN );
  auto_ptr<Token> value1( _tokenizer.Read( SCALAR ) );
  _tokenizer.Read( COMMA );
  auto_ptr<Token> value2( _tokenizer.Read( SCALAR ) );
  _tokenizer.Read( COMMA );
  auto_ptr<Token> value3( _tokenizer.Read( SCALAR ) );
  _tokenizer.Read( COMMA );
  auto_ptr<Token> value4( _tokenizer.Read( SCALAR ) );
  _tokenizer.Read( RPAREN );

  return Vec4d( value1->value(), 
    value2->value(), 
    value3->value(),
    value4->value() );
}

Material* Parser::parseMaterial( Scene* scene, const Material& parent )
{
  const Token* tok = _tokenizer.Peek();
  if( IDENT == tok->kind() )
  {
     return new Material(materials[ tok->ident() ]);
  }

  _tokenizer.Read( LBRACE );

  bool setReflective( false );
  string name;

  Material* mat = new Material(parent);

  for( ;; )
  {
    const Token* token = _tokenizer.Peek();
    switch( token->kind() )
    {
      case EMISSIVE:
        mat->setEmissive( parseVec3dMaterialParameter(scene) );
        break;

      case AMBIENT:
        mat->setAmbient( parseVec3dMaterialParameter(scene) );
        break;

      case SPECULAR:
      {
        MaterialParameter specular = parseVec3dMaterialParameter(scene);
        mat->setSpecular( specular );
        if( ! setReflective )
          mat->setReflective( specular );  // Default kr = ks if none specified
        break;
      }

      case DIFFUSE:
        mat->setDiffuse( parseVec3dMaterialParameter(scene) ); 
        break;

      case REFLECTIVE:
        mat->setReflective( parseVec3dMaterialParameter(scene) );
        setReflective = true;
        break;

      case TRANSMISSIVE:
        mat->setTransmissive( parseVec3dMaterialParameter(scene) );
        break;

      case INDEX:
        mat->setIndex( parseScalarMaterialParameter(scene) );
        break;

      case SHININESS:
        mat->setShininess( parseScalarMaterialParameter(scene) );
        break;

      case NAME:
         _tokenizer.Read(NAME);
         name = (_tokenizer.Read(IDENT))->ident();
         _tokenizer.Read( SEMICOLON );
         break;

      case RBRACE:
        _tokenizer.Read( RBRACE );
        if( ! name.empty() )
        {
           if( materials.find( name ) == materials.end() )
              materials[ name ] = *mat;
           else
           {
              ostringstream oss;
              oss << "Redefinition of material '" << name << "'.";
              throw SyntaxErrorException( oss.str(), _tokenizer );
           }
        }
        return mat;

      default:
         throw SyntaxErrorException( "Expected: material attribute", _tokenizer );

    }
  }
}

MaterialParameter Parser::parseVec3dMaterialParameter( Scene* scene )
{
  _tokenizer.Get();
  _tokenizer.Read(EQUALS);
  if( _tokenizer.CondRead( MAP ) )
  {
    _tokenizer.Read( LPAREN );
    string filename = _basePath;
    filename.append( "/" );
    filename.append(parseIdent());
    _tokenizer.Read( RPAREN );
    _tokenizer.CondRead(SEMICOLON);
    return MaterialParameter( scene->getTexture( filename ) );
  }
  else
  {
    Vec3d value( parseVec3d() );
    _tokenizer.CondRead(SEMICOLON);
    return MaterialParameter( value );
  }
}

MaterialParameter Parser::parseScalarMaterialParameter( Scene* scene )
{
  _tokenizer.Get();
  _tokenizer.Read(EQUALS);
  if( _tokenizer.CondRead(MAP) )
  {
    _tokenizer.Read( LPAREN );
    string filename = parseIdent();
    _tokenizer.Read( RPAREN );
    _tokenizer.CondRead(SEMICOLON);
    return MaterialParameter( scene->getTexture( filename ) );
  }
  else
  {
    double value = parseScalar();
    _tokenizer.CondRead(SEMICOLON);
    return MaterialParameter( value );
  }
}
