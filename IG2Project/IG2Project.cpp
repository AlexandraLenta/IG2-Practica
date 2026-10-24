#include "IG2Project.h"
#include "Labyrinth.h"
#include "Player.h"
#include "SpecialVillain.h"
#include <fstream>
#include "GameInfoOverlay.h"

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
        _player->setNewDir(Player::UP);
    }
    else if (evt.keysym.sym == SDLK_DOWN || evt.keysym.sym == SDLK_s) {
        _player->setNewDir(Player::DOWN);
    }
    else if (evt.keysym.sym == SDLK_LEFT || evt.keysym.sym == SDLK_a) {
        _player->setNewDir(Player::LEFT);
    }
    else if (evt.keysym.sym == SDLK_RIGHT || evt.keysym.sym == SDLK_d) {
        _player->setNewDir(Player::RIGHT);
    }

    return true;
}


void IG2Project::shutdown() {
    delete _labyrinth; _labyrinth = nullptr;

    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);

    mRoot->destroySceneManager(mSM);

    delete mTrayMgr;  mTrayMgr = nullptr;
    delete mCamMgr; mCamMgr = nullptr;
    delete _infoOverlay; _infoOverlay = nullptr;

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
    createOverlay();
    createCamera();
    createLights();
    createMap();
    createEnvironment();

    _infoOverlay->setPlayer(_player);
    _infoOverlay->updateGameInfo();
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
    mSM->setAmbientLight(ColourValue(0.2, 0.2, 0.2));

    auto* vp = getRenderWindow()->getViewport(0);
    vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
}

void IG2Project::createMap() {
    std::ifstream file;
    file.open(MAP_NAME);

    if (!file) {
        throw "File not found" + MAP_NAME;
    }

    int rows, cols;
    std::string wallMaterial;

    file >> rows >> cols >> wallMaterial >> _floorMaterial;

    _labyrinth = new Labyrinth({ 0, 0, 0 }, mSM->getRootSceneNode()->createChildSceneNode("labyrinth"), mSM, rows, cols, wallMaterial, file, this);

    file.close();
}

void IG2Project::createEnvironment() {
    // FLOOR
    std::pair<int, int> size = _labyrinth->getLabyrinthSize();

    MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        size.first, size.second, 50, 50, true, 1, 5, 5,
        Vector3::UNIT_Z);

    Entity* entFloor = mSM->createEntity("floor", "floor");
    entFloor->setMaterialName(_floorMaterial);
    SceneNode* floorNode = mSM->getRootSceneNode()->createChildSceneNode();
    floorNode->attachObject(entFloor);
    floorNode->translate({ -_labyrinth->BLOCK_SIZE / 2.f, 0, -_labyrinth->BLOCK_SIZE / 2.f });

    // SKY
    Ogre::Plane skyPlane;
    skyPlane.d = 1000;
    skyPlane.normal = Ogre::Vector3::UNIT_Y;
    mSM->setSkyPlane(true, skyPlane, "game/sky", 1500, 50, true, 1.5, 50, 50);
}


Character* IG2Project::createPlayer(Vector3 position) {
    _player = new Player(position, mSM->getRootSceneNode()->createChildSceneNode("player"), mSM, "Sinbad.mesh");
    _player->setInitialPosition({ _player->getPosition().x, _player->getPosition().y + _player->calculateBoxSize().y / 2.f, _player->getPosition().z });
    _player->setPosition(_player->getInitialPosition());

    return _player;
}

void IG2Project::createOverlay() {
    Real width = getRenderWindow()->getWidth() / 4.f;

    _infoOverlay = new GameInfoOverlay(mTrayMgr, width);
}

void IG2Project::frameRendered(const Ogre::FrameEvent& evt) {
    if (_labyrinth != nullptr) {
        _labyrinth->updateLabyrinth(evt.timeSinceLastFrame);
    }
}

void IG2Project::updateInfo() {
    _infoOverlay->updateGameInfo();
}

void IG2Project::endGame() {
    getRoot()->queueEndRendering();
}

GameInfoOverlay* IG2Project::getInfoOverlay() const {
    return _infoOverlay;
}