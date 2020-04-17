#pragma once

#include "GLView.h";
#include "irrKlang.h";
#include "Sound.h";
#include "NetworkingNetMsg.h";
#include "PlayerMovement.h";
#include "PxEngine.h"
#include <WOFTGLString.h>
#include <NetMessengerClient.h>

namespace Aftr
{
   class Camera;
   class PxEngine;
   class WOPxActor;

/**
   \class GLViewPhysics
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewPhysics : public GLView
{
public:
   static GLViewPhysics* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewPhysics();
   virtual void init(float gScalar, Vector gravityNormVec, std::string confFileName, const PHYSICS_ENGINE_TYPE& physEType);
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void createPhysicsWayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );
   virtual void spawnItem(Vector pos);
   virtual void movePlayer(Vector translate, Vector rotate, Vector ltrans, Vector lrot, bool toSend = true);
   virtual void setLabel(std::string usermsg);

   std::map<WOPxActor*, int> boxes;
   int numBoxes = 0;

protected:
   GLViewPhysics( const std::vector< std::string >& args );
   virtual void onCreate();

   SoundManager* sound;
   PxEngine* physics;
   NetMessengerClient* client;
   NetworkingNetMsg nnm;
   WO* player;
   WOFTGLString* label;
   std::string usermsg;
};

/** \} */

} //namespace Aftr
