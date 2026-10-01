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
#include <OgreWindowEventUtilities.h>
#include <SDL_keycode.h>

class Player;
class Labyrinth;
class Character;

static const std::string MAP_NAME = "../../IG2Project/IG2Project/IG2Media/stage1b.txt";

class IG2Project: public OgreBites::ApplicationContext, OgreBites::InputListener {

public:
    explicit IG2Project() : OgreBites::ApplicationContext("IG2Project") {};
    virtual ~IG2Project() {};

    Character* createPlayer(Ogre::Vector3 position);

protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();

    Player* _player = nullptr;
    Labyrinth* _labyrinth = nullptr;

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

private:
    void createCamera();
    void createLights();
    void createFloor();
    void createMap();
};

#endif