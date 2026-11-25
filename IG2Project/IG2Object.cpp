#include "IG2Object.h"

IG2Object::IG2Object() : mNode(nullptr), mSM(nullptr), entity(nullptr) {
    this->initialPosition = Vector3::ZERO;
}

IG2Object::IG2Object(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : initialPosition(initPos), mNode(node), mSM(sceneMng), entity(nullptr) {
    this->setPosition(initialPosition);
}

IG2Object::IG2Object(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : initialPosition(initPos), mNode(node), mSM(sceneMng), entity(nullptr) {

    // Creates a new entity with the mesh and attach the entity
    entity = sceneMng->createEntity(mesh);
    mNode->attachObject(entity);
    this->setPosition(initialPosition);
}

void IG2Object::destroyNodeTree(Ogre::SceneNode* node) {
    Ogre::SceneManager* sm = node->getCreator();

    // destroy children (recursive, so destroy children of children...)
    while (node->numChildren() > 0)
        destroyNodeTree(static_cast<Ogre::SceneNode*>(node->getChild(0)));

    // destroy anything attached to this node
    while (node->numAttachedObjects() > 0) {
        Ogre::MovableObject* o = node->getAttachedObject(0);
        node->detachObject(o);
        sm->destroyMovableObject(o);
    }

    sm->destroySceneNode(node);
}

IG2Object::~IG2Object() {
    if (mNode != nullptr) {
        destroyNodeTree(mNode);
        mNode = nullptr;
    }
    entity = nullptr;
    mSM = nullptr;
}

SceneNode* IG2Object::createChildSceneNode() {
    return mNode->createChildSceneNode();
}

void IG2Object::setInitialPosition(Vector3 v) {
    this->initialPosition = v;
}

Vector3 IG2Object::getInitialPosition() {
    return this->initialPosition;
}

void IG2Object::move(Vector3 v) {
    mNode->translate(v);
}

void IG2Object::yaw(const Radian& angle) {
    mNode->yaw(angle);
}

void IG2Object::roll(const Radian& angle) {
    mNode->roll(angle);
}

void IG2Object::pitch(const Radian& angle) {
    mNode->pitch(angle);
}

void IG2Object::rotate(const Quaternion& q) {
    mNode->rotate(q);
}

void IG2Object::setPosition(Vector3 v) {
    mNode->setPosition(v);
}

Vector3 IG2Object::getPosition() const {
    return mNode->getPosition();
}

void IG2Object::setScale(Vector3 vScale) {
    mNode->setScale(vScale);
}

void IG2Object::setVisible(bool visible) {
    mNode->setVisible(visible);
}

Vector3 IG2Object::getOrientation() {
    Vector3 result = mNode->_getDerivedOrientation() * Vector3::UNIT_Z;
    result.normalise();
    return result;
}

Vector3 IG2Object::getGridOrientation() {
    return getOrientation().primaryAxis();
}

void IG2Object::setMaterialName(std::string materialName) {
    entity->setMaterialName(materialName);
}

bool IG2Object::hasEntity() {
    return (entity != nullptr);
}

void IG2Object::removeEntity() {

    if (hasEntity() && (entity != nullptr)) {
        mSM->destroyEntity(entity);
        entity = nullptr;
    }
}

Vector3 IG2Object::calculateBoxSize() {

    Vector3 result;

    if (mNode->getAttachedObjects().size() > 0) {
        Entity* mEntity = static_cast<Entity*>(mNode->getAttachedObject(0));
        const AxisAlignedBox& aab = mEntity->getBoundingBox();
        Vector3 min = aab.getMinimum() * mNode->getScale();
        Vector3 max = aab.getMaximum() * mNode->getScale();
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

const AxisAlignedBox& IG2Object::getAABB() {
    return mNode->_getWorldAABB();
}

