#ifndef __IG2PROJECT_H__
#define __IG2PROJECT_H__

#include <OgreApplicationContext.h>
#include <OgreSceneManager.h>
#include <OgreRTShaderSystem.h>       
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include "Ogre.h"
#include <OgreWindowEventUtilities.h>
#include <SDL_keycode.h>

class Player;

static const std::string MAP_NAME = "../../IG2Project/IG2Project/IG2Media/stage1.txt";

class IG2Project: public OgreBites::ApplicationContext, OgreBites::InputListener {

public:
    explicit IG2Project() : OgreBites::ApplicationContext("IG2Project") {};
    virtual ~IG2Project() {};

    enum PlayerDirections {
        RIGHT, 
        LEFT,
        UP,
        DOWN
    };

protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();

    Player* _player = nullptr;

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    PlayerDirections _playerDirection = DOWN;

private:
    void createCamera();
    void createLights();
    void createFloor();
    void createLabyrinth();
    void createPlayer();
    Ogre::Vector3 getNextDirVector();
    bool isDirectionModified();
    Ogre::Quaternion getQuaternionForNewDirection();
};

#endif