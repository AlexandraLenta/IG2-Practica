#pragma once
#include "IG2Object.h"

class Block : public IG2Object
{
public:
    static constexpr char MESH_NAME[] = "cube.mesh";
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

    virtual void update(Real time);

protected:
    bool _canPassThrough;
};

