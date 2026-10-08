#pragma once
#include "Villain.h"
class SpecialVillain :
	public Villain
{
public:
	SpecialVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp = 10, int l = 3);


protected:
	void setup() override;

	//Vector3 calculateBoxSize() {
	//	Vector3 result;

	//	if (mNode->getAttachedObjects().size() > 0) {
	//		Entity* mEntity = static_cast<Entity*>(mNode->getAttachedObject(0));
	//		const AxisAlignedBox& aab = mEntity->getBoundingBox();
	//		Vector3 min = aab.getMinimum() * mNode->getScale();
	//		Vector3 max = aab.getMaximum() * mNode->getScale();
	//		Real paddingFactor = MeshManager::getSingleton().getBoundsPaddingFactor();

	//		// adjust min & max to exclude the padding factor..
	//		Vector3 newMin = min + (max - min) * paddingFactor;
	//		Vector3 newMax = max + (min - max) * paddingFactor;
	//		result = newMax - newMin;
	//	}
	//	else {
	//		result = { 0,0,0 };
	//	}


	//	return result;
	//}
};