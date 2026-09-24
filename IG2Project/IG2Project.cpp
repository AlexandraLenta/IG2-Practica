#include "IG2Project.h"
#include "Labyrinth.h"
#include "Player.h"

using namespace std;
using namespace Ogre;


bool IG2Project::keyPressed(const OgreBites::KeyboardEvent& evt) {

    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    else if (evt.keysym.sym == SDLK_k) {
        //cout << "Position of Sinbad: " << mSinbadNode->getPosition() << endl;
        cout << "Position of the camera: " << mCamNode->getPosition() << endl;
    }

    else if (evt.keysym.sym == SDLK_UP || evt.keysym.sym == SDLK_w) {
        cout << "Pressed UP" << endl;
        _playerDirection = UP;
    }
    else if (evt.keysym.sym == SDLK_DOWN || evt.keysym.sym == SDLK_s) {
        cout << "Pressed DOWN" << endl;
        _playerDirection = DOWN;
    }
    else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) {
        cout << "Pressed LEFT" << endl;
        _playerDirection = LEFT;
    }
    else if (evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) {
        cout << "Pressed RIGHT" << endl;
        _playerDirection = RIGHT;
    }

    return true;
}


void IG2Project::shutdown() {

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
    createLabyrinth();
    createPlayer();
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

void IG2Project::createLabyrinth() {
    Labyrinth* labyrinth = new Labyrinth({ 0, Labyrinth::BLOCK_SIZE/2., 0 }, mSM->getRootSceneNode()->createChildSceneNode("labyrinth"), mSM, MAP_NAME);
}

void IG2Project::createPlayer() {
    _player = new Player({0, 0, 0}, mSM->getRootSceneNode()->createChildSceneNode("Player"), mSM, "Sinbad.mesh");
    _player->setInitialPosition({ 0, _player->calculateBoxSize().y / 2.f, 0 });
    _player->setPosition(_player->getInitialPosition());
}

Vector3 IG2Project::getNextDirVector() {
    Vector3 newDirVector = Vector3::ZERO;

    if (_playerDirection == RIGHT)
        newDirVector = Vector3::UNIT_X;
    else if (_playerDirection == LEFT)
        newDirVector = Vector3::NEGATIVE_UNIT_X;
    else if (_playerDirection == DOWN)
        newDirVector = Vector3::UNIT_Z;
    else if (_playerDirection == UP)
        newDirVector = Vector3::NEGATIVE_UNIT_Z;
    return newDirVector;

}

bool IG2Project::isDirectionModified() {
    return _player->getGridOrientation() != getNextDirVector();
}

Quaternion IG2Project::getQuaternionForNewDirection() {
    Vector3 newDirVector = getNextDirVector();
    Quaternion q = _player->getOrientation().getRotationTo(newDirVector);
    return q;
}

void IG2Project::frameRendered(const Ogre::FrameEvent& evt) {

    if (_player != nullptr) {
        if (!isDirectionModified())
            _player->move(getNextDirVector() * _player->getSpeed() * evt.timeSinceLastFrame);
        else
            _player->rotate(getQuaternionForNewDirection());
    }
}