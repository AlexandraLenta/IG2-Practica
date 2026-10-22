#include "SpecialVillain.h"

SpecialVillain::SpecialVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp, int l) : Villain(initPos, node, sceneMng, sp, l) {
    setup();
    mNode->setScale(mNode->getScale() * 0.6);
    _timer = new Ogre::Timer();
}

SpecialVillain::~SpecialVillain() {
    delete _timer;
    _timer = nullptr;
}

void SpecialVillain::update(Real dt) {
    // total seconds passed -- for periodical movement
    float t = _timer->getMilliseconds() / 1000.f;

    // WHEEL SPIN -------------
    float wheelDegPerSec = 360.f; // full spin in one second

    // uses dt for continuous movement
    for (int i = 0; i < _wheelsSign.size(); i++) {
        _wheelsSign[i].first->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(_wheelsSign[i].second * wheelDegPerSec * dt));
        _swords[i]->setPosition(Ogre::Vector3{ 0, 0, 0 } + Ogre::Vector3(0, 5.f * std::sin(t * 6.f), 0));
    }

    // TOP TURN -----------------------
    float yaw = 30.f * std::sin(t * 1.5f);
    _top->setOrientation(Ogre::Quaternion(Ogre::Degree(yaw), Vector3::UNIT_Y));

    // HEAD UP & DOWN --------------------
    _head->setPosition(_headBasePos + Ogre::Vector3(0, 5.f * std::sin(t * 6.f), 0));
}

Ogre::Vector3 SpecialVillain::chooseDirection(const Labyrinth& l) {
    return { 0, 0, 0 };
}

void SpecialVillain::setup() {
    // BODY --------------------------
    entity = mSM->createEntity(BODY_MESH); 
    mNode->attachObject(entity);
    this->setPosition(initialPosition);
    mNode->setScale(0.15, 0.1, 0.15);

    Vector3 bodySize = calculateNodeBoxSize(mNode);

    Real halfH = bodySize.y / 2.0f;

    mNode->setPosition(initialPosition.x, initialPosition.y + halfH/7.f, initialPosition.z);

    // TOP ----------------------------
    _top = createPart(mNode, TOP_MESH, TOP_SCALE);

    Vector3 topSize = calculateNodeBoxSize(_top);

    Real topHalfH = topSize.y / (2.0f * mNode->getScale().y);

    _top->setPosition(0, halfH + topHalfH/3.f, 0);

    // HEAD ----------------------------
    _head = createPart(_top, HEAD_MESH, HEAD_SCALE);

    Vector3 headSize = calculateNodeBoxSize(_head);

    Real headHalfH = headSize.y / 2.0f / _top->getScale().y;

    _head->setPosition(0, headHalfH/5.f, 0);
    _headBasePos = _head->getPosition();

    // GUN ------------------------------
    _gun = createPart(_top, GUN_MESH, GUN_SCALE);

    Vector3 gunSize = calculateNodeBoxSize(_gun);

    Real gunHalfD = gunSize.z / 2.0f / _top->getScale().z;
    Real topHalfD = topSize.z / 2.0f / _top->getScale().z;

    _gun->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    _gun->rotate(Ogre::Vector3::UNIT_Z, Ogre::Degree(-45));
    _gun->setPosition(0, 1.5f*topHalfH, topHalfD + gunHalfD/2.f);

    // WHEELS ----------------------------
    _wheelsSign.push_back({ createWheel(1, true, true), -1 });   // front left
    _wheelsSign.push_back({ createWheel(2, false, true), 1 });   // front right
    _wheelsSign.push_back({ createWheel(3, true, false), -1 });  // back left
    _wheelsSign.push_back({ createWheel(4, false, false), 1 });  // back right
}

Ogre::SceneNode* SpecialVillain::createPart(Ogre::SceneNode* parent, const std::string& mesh, const Vector3& scale) {
    Ogre::SceneNode* node = parent->createChildSceneNode();
    node->attachObject(mSM->createEntity(mesh));
    node->setScale(scale);
    return node;
}

Ogre::SceneNode* SpecialVillain::createWheel(int id, bool left, bool front) {
    const Vector3 WHEEL_SCALE = { 6, 1.8, 6 };
    const Vector3 WHEEL_HEAD_SCALE = { 0.08, 0.27, 0.03 };
    const Vector3 WHEEL_SWORD_SCALE = { 1, 3.33, 1 };

    const std::string idStr = std::to_string(id);

    // signs depend on bools
    const Real sideX = left ? -1.f : 1.f;   // left: -X, right: +X
    const Real sideZ = front ? 1.f : -1.f;  // front: +Z, back: -Z

    // Altura media del cuerpo (para colocar la rueda debajo)
    Real halfH = calculateNodeBoxSize(mNode).y / 2.0f;

    // Rueda
    Ogre::SceneNode* wheel = createPart(mNode, WHEEL_MESH, WHEEL_SCALE);

    Vector3 wheelSize = calculateNodeBoxSize(wheel);
    Real wheelHalfW = wheelSize.x / 2.0f / mNode->getScale().x;
    Real wheelHalfH = wheelSize.y / 4.0f / mNode->getScale().y;

    Real WHEEL_POS_Y = -wheelHalfH - halfH;
    Real WHEEL_POS_X = wheelHalfW / 1.95f;
    Real WHEEL_POS_Z = wheelHalfW / 2.1f;

    // izquierda: +90 en Z, derecha: -90 en Z
    wheel->rotate(Ogre::Vector3::UNIT_Z, Ogre::Degree(-sideX * 90));
    wheel->setPosition(sideX * WHEEL_POS_X, WHEEL_POS_Y, sideZ * WHEEL_POS_Z);

    // Decoración (cabeza de ogro) dentro de la rueda
    Ogre::SceneNode* wheelHead = createPart(wheel, WHEEL_DECO_MESH, WHEEL_HEAD_SCALE);
    wheelHead->setPosition(0, wheelHalfH / 4.f, 0);
    wheelHead->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(sideX * 90), Ogre::Node::TS_WORLD);
    wheelHead->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(90), Ogre::Node::TS_WORLD);

    // Decoración (espada) dentro de la rueda
    Ogre::SceneNode* wheelSword = createPart(wheel, WHEEL_DECO2_MESH, WHEEL_SWORD_SCALE);
    wheelSword->setPosition(0, 0, 0);
    wheelSword->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(sideX * 90), Ogre::Node::TS_WORLD);
    wheelSword->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(90), Ogre::Node::TS_WORLD);

    _swords.push_back(wheelSword);

    return wheel;
}

Vector3 SpecialVillain::calculateNodeBoxSize(Ogre::SceneNode* node) {

    Vector3 result;

    if (node->getAttachedObjects().size() > 0) {
        Entity* mEntity = static_cast<Entity*>(node->getAttachedObject(0));
        const AxisAlignedBox& aab = mEntity->getBoundingBox();
        Vector3 min = aab.getMinimum() * node->getScale();
        Vector3 max = aab.getMaximum() * node->getScale();
        Real paddingFactor = MeshManager::getSingleton().getBoundsPaddingFactor();

        // adjust min & max to exclude the padding factor..
        Vector3 newMin = min + (max - min) * paddingFactor;
        Vector3 newMax = max + (min - max) * paddingFactor;
        result = newMax - newMin;
    }
    else {
        result = { 0,0,0 };
    }
    return result;
}
