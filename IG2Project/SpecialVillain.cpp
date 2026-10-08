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

    Ogre::SceneNode* top = mNode->createChildSceneNode("villainTop");
    Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
    top->attachObject(ent);
    //top->setPosition();
    top->setScale(0.1, 0.1, 0.1);

    Ogre::SceneNode* head = top->createChildSceneNode("villainHead");
    ent = mSM->createEntity("DamagedHelmet.mesh");
    head->attachObject(ent);
    //head->setPosition();

    Ogre::SceneNode* wheel1 = mNode->createChildSceneNode("villainWheel1");
    ent = mSM->createEntity("Barrel.mesh");
    wheel1->attachObject(ent);
    //wheel1->setPosition();

    Ogre::SceneNode* wheelHead1 = wheel1->createChildSceneNode("villainWheelDeco1"); // front left
    ent = mSM->createEntity("ogrehead.mesh");
    wheelHead1->attachObject(ent);
    //wheelHead1->setPosition();
    wheelHead1->setScale(0.1, 0.1, 0.1);
    wheelHead1->setDirection(Vector3{1, 0, 0});

    Ogre::SceneNode* wheel2 = mNode->createChildSceneNode("villainWheel2");
    ent = mSM->createEntity("Barrel.mesh");
    wheel2->attachObject(ent);
    //wheel2->setPosition();

    Ogre::SceneNode* wheelHead2 = wheel2->createChildSceneNode("villainWheelDeco2");
    ent = mSM->createEntity("ogrehead.mesh");
    wheelHead2->attachObject(ent);
    //wheelHead2->setPosition();
    wheelHead2->setScale(0.1, 0.1, 0.1);
    wheelHead2->setDirection(Vector3{});

    Ogre::SceneNode* wheel3 = mNode->createChildSceneNode("villainWheel3");
    ent = mSM->createEntity("Barrel.mesh");
    wheel3->attachObject(ent);
    //wheel3->setPosition();

    Ogre::SceneNode* wheelHead3 = wheel3->createChildSceneNode("villainWheelDeco3");
    ent = mSM->createEntity("ogrehead.mesh");
    wheelHead3->attachObject(ent);
    wheelHead3->setScale(0.1, 0.1, 0.1);
    wheelHead3->setDirection(Vector3{});
    //wheelHead3->setPosition();

    Ogre::SceneNode* wheel4 = mNode->createChildSceneNode("villainWheel4");
    ent = mSM->createEntity("Barrel.mesh");
    wheel4->attachObject(ent);
    //wheel4->setPosition();

    Ogre::SceneNode* wheelHead4 = wheel4->createChildSceneNode("villainWheelDeco4");
    ent = mSM->createEntity("ogrehead.mesh");
    wheelHead4->attachObject(ent);
    wheelHead4->setScale(0.1, 0.1, 0.1);
    wheelHead4->setDirection(Vector3{});
    //wheelHead4->setPosition();

    Ogre::SceneNode* gun = mNode->createChildSceneNode("villainGun");
    ent = mSM->createEntity("fish.mesh");
    gun->attachObject(ent);
    //gun->setPosition();
}