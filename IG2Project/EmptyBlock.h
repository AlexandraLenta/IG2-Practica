#pragma once
#include "IG2Object.h"
class EmptyBlock :
    public IG2Object
{
public:
    /**
     * Constructor without parameters.
     */
    EmptyBlock();

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     * @param mesh Mesh that is applied to this element.
     */
    EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);
};

