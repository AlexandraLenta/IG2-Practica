#pragma once
#include "Block.h"
class InvisibleBlock :
    public Block
{
public:
    static constexpr float INVISIBLE_TIMER = 4.0f;
    /**
     * Constructor without parameters.
     */
    InvisibleBlock();

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    InvisibleBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     * @param mesh Mesh that is applied to this element.
     */
    InvisibleBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);

    void update(Real time) override;

private:
    bool _isVisible = false;
    float _timer = 0.0f;
};

