#ifndef CCD_H
#define CCD_H

#include <math.h>
#include "skeleton.h"
#include "vector2d.h"

class CCD
{
	private:
		// Bone Chain
		Skeleton m_skeleton;
		int m_numBones;
		// Target Position
		Vector2D m_targetPos;

	public:
		CCD();
		Skeleton* getSkeleton();
		template <int boneCount>
		inline void setBoneChain(const float (&angle)[boneCount]);
		void getPivotPositions(int count, Vector2D* pivot);
		void setTargetPosition(float tx, float ty);
		bool apply(const int maxIter, const float eps);
};

template <int boneCount>
inline void CCD::setBoneChain(const float (&angle)[boneCount])
{
	if(boneCount < 1) return;
	m_numBones = boneCount;
	SkeletonNode* node = new SkeletonNode();
	node->setAngle(angle[0]/180.0f*M_PI);
	m_skeleton.setRoot(node);
	
	for(int i=1; i<boneCount; i++)
	{
		SkeletonNode* parent = node;
		node = new SkeletonNode();
		node->setAngle(angle[i]/180.0f*M_PI);
		parent->addChild(node);
	}
}

#endif // CCD_H