#pragma once
#include "IG2Object.h"

class Block : public IG2Object
{
public:
public:
    /**
     * Constructor without parameters.
     */
    Block();

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     * @param mesh Mesh that is applied to this element.
     */
    Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);

	bool canPassThrough();
};

