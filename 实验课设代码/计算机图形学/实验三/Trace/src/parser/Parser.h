#pragma warning (disable: 4786)

#ifndef __PARSER_H__

#define __PARSER_H__

#include <string>
#include <map>

#include "ParserException.h"
#include "Tokenizer.h"

#include "../scene/scene.h"
#include "../scene/light.h"
#include "../SceneObjects/Box.h"
#include "../SceneObjects/Cone.h"
#include "../SceneObjects/Cylinder.h"
#include "../SceneObjects/Sphere.h"
#include "../SceneObjects/Square.h"
#include "../SceneObjects/trimesh.h"

#include "../vecmath/vec.h"
#include "../vecmath/mat.h"

typedef std::map<string,Material> mmap;

/*
  class Parser:
    The Parser is where most of the heavy lifting in parsing
    goes.  This particular parser reads in a stream of tokens
    from the Tokenizer and converts them into a scene in 
    memory.  

    If you really want to know, this parser is written
    as a top-down parser with one symbol of lookahead.
    See the docs on the website if you're interested in
    modifying this somehow.
*/

class Parser
{
  public:
    // We need the path for referencing files from the
    // base file.
    Parser( Tokenizer& tokenizer, string basePath )
      : _tokenizer( tokenizer ), _basePath( basePath )
      { }

    // Parse the top-level scene
    Scene* parseScene();

private:

    // Highest level parsing routines
    void parseTransformableElement( Scene* scene, TransformNode* transform, const Material& mat );
    void parseGroup( Scene* scene, TransformNode* transform, const Material& mat );
	  void parseCamera( Scene* scene );

    void parseGeometry( Scene* scene, TransformNode* transform, const Material& mat );


    // Parse lights
	PointLight* parsePointLight( Scene* scene );
	DirectionalLight* parseDirectionalLight( Scene* scene );
	void parseAmbientLight( Scene* scene );

    // Parse geometry
    void      parseSphere(Scene* scene, TransformNode* transform, const Material& mat);
    void      parseBox(Scene* scene, TransformNode* transform, const Material& mat);
    void      parseSquare(Scene* scene, TransformNode* transform, const Material& mat);
    void      parseCylinder(Scene* scene, TransformNode* transform, const Material& mat);
    void      parseCone(Scene* scene, TransformNode* transform, const Material& mat);
    void      parseTrimesh(Scene* scene, TransformNode* transform, const Material& mat);
    void      parseFaces( std::list< Vec3d >& faces );

    // Parse transforms
    void parseTranslate(Scene* scene, TransformNode* transform, const Material& mat);
    void parseRotate(Scene* scene, TransformNode* transform, const Material& mat);
    void parseScale(Scene* scene, TransformNode* transform, const Material& mat);
    void parseTransform(Scene* scene, TransformNode* transform, const Material& mat);

    // Helper functions for parsing expressions of the form:
    //   keyword = value;
    double parseScalarExpression();
    Vec3d parseVec3dExpression();
    Vec4d parseVec4dExpression();
    bool parseBooleanExpression();
    Material* parseMaterialExpression(Scene* scene, const Material& mat);
    string parseIdentExpression();

    MaterialParameter parseVec3dMaterialParameter(Scene* scene);
    MaterialParameter parseScalarMaterialParameter(Scene* scene);


    // Helper functions for parsing things like vectors
    // and idents.
    double parseScalar();
    std::list<double> parseScalarList();
    Vec3d parseVec3d();
    Vec4d parseVec4d();
    bool parseBoolean();
    Material* parseMaterial(Scene* scene, const Material& parent);
    string parseIdent();

  private:
    Tokenizer& _tokenizer;
    mmap materials;
    std::string _basePath;
};

#endif


