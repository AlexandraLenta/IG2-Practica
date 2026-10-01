#include "IG2Project.h"
#include "Labyrinth.h"
#include "Player.h"
#include <fstream>

using namespace Ogre;


bool IG2Project::keyPressed(const OgreBites::KeyboardEvent& evt) {

    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    else if (evt.keysym.sym == SDLK_k) {
        //cout << "Position of Sinbad: " << mSinbadNode->getPosition() << endl;
        std::cout << "Position of the camera: " << mCamNode->getPosition() << std::endl;
    }

    else if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_w) {
        std::cout << "Pressed UP" << std::endl;
        _player->setNewDir(Player::UP);
    }
    else if (evt.keysym.sym == SDLK_DOWN || evt.keysym.sym == SDLK_s) {
        std::cout << "Pressed DOWN" << std::endl;
        _player->setNewDir(Player::DOWN);
    }
    else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) {
        std::cout << "Pressed LEFT" << std::endl;
        _player->setNewDir(Player::LEFT);
    }
    else if (evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) {
        std::cout << "Pressed RIGHT" << std::endl;
        _player->setNewDir(Player::RIGHT);
    }

    return true;
}


void IG2Project::shutdown() {
    delete _labyrinth; _labyrinth = nullptr;
    delete _player; _player = nullptr;

    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);

    mRoot->destroySceneManager(mSM);

    delete mTrayMgr;  mTrayMgr = nullptr;
    delete mCamMgr; mCamMgr = nullptr;

    // do not forget to call the base 
    OgreBites::ApplicationContext::shutdown();
}

void IG2Project::setup(void) {

    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);
        
    mSM->addRenderQueueListener(mOverlaySystem);
    //mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", getRenderWindow());
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);

    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2Project::setupScene(void) {

    createCamera();
    createLights();
    createFloor();
    createMap();
}

void IG2Project::createCamera() {
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);

    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

    // tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
}

void IG2Project::createLights() {
    mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(-1, -1, -1));
}

void IG2Project::createFloor() {
    MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        1500, 1500, 50, 50, true, 1, 5, 5,
        Vector3::UNIT_Z);

    Entity* entFloor = mSM->createEntity("exampleFloor", "floor");
    entFloor->setMaterialName("example/stonesFloor");
    SceneNode* floorNode = mSM->getRootSceneNode()->createChildSceneNode();
    floorNode->attachObject(entFloor);
}

void IG2Project::createMap() {
    std::ifstream file;
    file.open(MAP_NAME);

    if (!file) {
        throw "File not found" + MAP_NAME;
    }

    _labyrinth = new Labyrinth({ 0, Labyrinth::BLOCK_SIZE/2., 0 }, mSM->getRootSceneNode()->createChildSceneNode("labyrinth"), mSM, file, this);

    file.close();
}

Character* IG2Project::createPlayer(Vector3 position) {
    _player = new Player(position, mSM->getRootSceneNode()->createChildSceneNode("player"), mSM, "Sinbad.mesh");
    _player->setInitialPosition({ _player->getPosition().x, _player->getPosition().y + _player->calculateBoxSize().y / 2.f, _player->getPosition().z });
    _player->setPosition(_player->getInitialPosition());

    return _player;
}

void IG2Project::frameRendered(const Ogre::FrameEvent& evt) {
    if (_labyrinth != nullptr) {
        _labyrinth->updateLabyrinth(evt.timeSinceLastFrame);
    }
}