#ifndef FABRIK_H
#define FABRIK_H

#include <math.h>
#include "skeleton.h"
#include "vector2d.h"

class FABRIK {
	private:
		// Bone Chain
		Skeleton m_skeleton;
		int m_numBones;
		// Target Position
		Vector2D m_targetPos;

	public:
		FABRIK();
		Skeleton* getSkeleton();
		template <int boneCount>
		inline void setBoneChain(const float (&angle)[boneCount], const float (&length)[boneCount]);
		void setTargetPosition(float tx, float ty);
		bool apply(const int maxIter, const float eps);
};

template <int boneCount>
inline void FABRIK::setBoneChain(const float (&angle)[boneCount], const float (&length)[boneCount]) {
	if(boneCount < 1) return;
	m_numBones = boneCount;
	SkeletonNode* node = new SkeletonNode();
	node->setAngle(angle[0]/180.0f*M_PI);
	node->setLength(length[0]);
	m_skeleton.setRoot(node);
	
	for(int i=1; i<boneCount; i++) {
		SkeletonNode* parent = node;
		node = new SkeletonNode();
		node->setAngle(angle[i]/180.0f*M_PI);
		node->setLength(length[i]);
		parent->addChild(node);
	}
}

#endif // FABRIK_H