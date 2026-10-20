#include "SpecialVillain.h"

SpecialVillain::SpecialVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp, int l) : Villain(initPos, node, sceneMng, sp, l) {
    setup();
}

void SpecialVillain::setup() {
    // Creates a new entity with the mesh and attach the entity
    entity = mSM->createEntity("cube.mesh"); // body
    mNode->attachObject(entity);
    this->setPosition(initialPosition);
    mNode->setScale(0.25, 0.25, 0.25);

    Vector3 bodySize = calculateNodeBoxSize(mNode);

    Real halfW = bodySize.x / 2.0f;
    Real halfH = bodySize.y / 2.0f;
    Real halfD = bodySize.z / 2.0f;

    mNode->setVisible(false);

    Ogre::SceneNode* top = mNode->createChildSceneNode("villainTop"); // top part
    Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
    top->attachObject(ent);

    top->setScale(0.2, 0.1, 0.2);
    Vector3 topSize = calculateNodeBoxSize(top);

    Real topHalfH = topSize.y / 2.0f / mNode->getScale().y;

    top->setPosition(0, halfH + topHalfH, 0);

    Ogre::SceneNode* head = top->createChildSceneNode("villainHead"); // head of the tank user
    ent = mSM->createEntity("DamagedHelmet.mesh");
    head->attachObject(ent);

    Vector3 headSize = calculateNodeBoxSize(head);

    Real headHalfH = headSize.y / 2.0f / top->getScale().y;

    head->setPosition(0, topSize.y / 2.0f / top->getScale().y + headHalfH, 0);

    // WHEELS

    Vector3 WHEEL_SCALE = { 1, 0.25, 1 };
    Vector3 WHEEL_HEAD_SCALE = { 0.08, 0.08 / 0.25, 0.08 };
     
    // wheel 1
    Ogre::SceneNode* wheel1 = mNode->createChildSceneNode("villainWheel1"); // front left
    ent = mSM->createEntity("Barrel.mesh");
    wheel1->attachObject(ent);
    
    Vector3 wheel1Size = calculateNodeBoxSize(wheel1);

    Real wheelHalfW = wheel1Size.x / 2.0f / mNode->getScale().x;

    Real wheelHalfH = wheel1Size.y / 4.0f / mNode->getScale().y;

    wheel1->rotate(Ogre::Vector3::UNIT_Z, Ogre::Degree(90));
    wheel1->setPosition(-(halfW + wheelHalfW), -halfH * 0.3f, halfD * 0.6f);
    wheel1->setScale(WHEEL_SCALE);
    //wheel1->setVisible(false);

    Ogre::SceneNode* wheelHead1 = wheel1->createChildSceneNode("villainWheelDeco1"); // decoration inside of wheel
    ent = mSM->createEntity("ogrehead.mesh");
    wheelHead1->attachObject(ent);
    wheelHead1->setPosition(0, wheelHalfH, 0);
    wheelHead1->setScale(WHEEL_HEAD_SCALE);
    wheelHead1->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(-90), Ogre::Node::TS_WORLD);
    wheelHead1->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(90), Ogre::Node::TS_WORLD);

    // wheel 2
    Ogre::SceneNode* wheel2 = mNode->createChildSceneNode("villainWheel2"); // front right
    ent = mSM->createEntity("Barrel.mesh");
    wheel2->attachObject(ent);

    Vector3 wheel2Size = calculateNodeBoxSize(wheel2);

    wheelHalfW = wheel2Size.x / 2.0f / mNode->getScale().x;

    wheel2->setPosition(halfW + wheelHalfW, -halfH * 0.3f, halfD * 0.6f);
    wheel2->rotate(-Ogre::Vector3::UNIT_Z, Ogre::Degree(90));
    wheel2->setScale(WHEEL_SCALE);
    //wheel2->setVisible(false);

    Ogre::SceneNode* wheelHead2 = wheel2->createChildSceneNode("villainWheelDeco2"); // decoratin inside of wheel
    ent = mSM->createEntity("ogrehead.mesh");
    wheelHead2->attachObject(ent);
    wheelHead2->setScale(WHEEL_HEAD_SCALE);
    wheelHead2->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90), Ogre::Node::TS_WORLD);
    wheelHead2->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(90), Ogre::Node::TS_WORLD);
    wheelHead2->setPosition(0, wheelHalfH, 0);

    // wheel 3
    Ogre::SceneNode* wheel3 = mNode->createChildSceneNode("villainWheel3"); // back left
    ent = mSM->createEntity("Barrel.mesh");
    wheel3->attachObject(ent);
    wheel3->rotate(Ogre::Vector3::UNIT_Z, Ogre::Degree(90));

    Vector3 wheel3Size = calculateNodeBoxSize(wheel3);

    wheelHalfW = wheel3Size.x / 2.0f / mNode->getScale().x;

    wheel3->setPosition(-(halfW + wheelHalfW), -halfH * 0.3f, -halfD * 0.6f);
    wheel3->setScale(WHEEL_SCALE);
    //wheel3->setVisible(false);

    Ogre::SceneNode* wheelHead3 = wheel3->createChildSceneNode("villainWheelDeco3"); // decoratin inside of wheel
    ent = mSM->createEntity("ogrehead.mesh");
    wheelHead3->attachObject(ent);
    wheelHead3->setScale(WHEEL_HEAD_SCALE);

    wheelHead3->setPosition(0, wheelHalfH, 0);
    wheelHead3->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(-90), Ogre::Node::TS_WORLD);
    wheelHead3->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(90), Ogre::Node::TS_WORLD);

    // wheel 4
    Ogre::SceneNode* wheel4 = mNode->createChildSceneNode("villainWheel4"); // back right
    ent = mSM->createEntity("Barrel.mesh");
    wheel4->attachObject(ent);
    wheel4->rotate(-Ogre::Vector3::UNIT_Z, Ogre::Degree(90));

    Vector3 wheel4Size = calculateNodeBoxSize(wheel4);

    wheelHalfW = wheel4Size.x / 2.0f / mNode->getScale().x;

    wheel4->setPosition(halfW + wheelHalfW, -halfH * 0.3f, -halfD * 0.6f);
    wheel4->setScale(WHEEL_SCALE);
    //wheel4->setVisible(false);

    Ogre::SceneNode* wheelHead4 = wheel4->createChildSceneNode("villainWheelDeco4"); // decoratin inside of wheel
    ent = mSM->createEntity("ogrehead.mesh");
    wheelHead4->attachObject(ent);
    wheelHead4->setScale(WHEEL_HEAD_SCALE);

    wheelHead4->setPosition(0, wheelHalfH, 0);
    wheelHead4->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90), Ogre::Node::TS_WORLD);
    wheelHead4->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(90), Ogre::Node::TS_WORLD);

    // gun attached to the top part
    Ogre::SceneNode* gun = mNode->createChildSceneNode("villainGun");
    ent = mSM->createEntity("fish.mesh");
    gun->attachObject(ent);

    Vector3 gunSize = calculateNodeBoxSize(gun);

    Real gunHalfD = gunSize.z / 2.0f / top->getScale().z;
    Real topHalfD = topSize.z / 2.0f / top->getScale().z;

    gun->setPosition(0, 0, topHalfD + gunHalfD);
    gun->setDirection(Ogre::Vector3::UNIT_Z);
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
