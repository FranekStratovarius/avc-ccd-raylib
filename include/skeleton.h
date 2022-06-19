#ifndef SKELETON_H
#define SKELETON_H

#include <vector>
class SkeletonNode {
	public:
		SkeletonNode();
		~SkeletonNode();
		void addChild(SkeletonNode* c);
		SkeletonNode* getJoint(int& index, const int searchIndex);
		void setAngle(float angle) { m_angle = angle; }
		float getAngle() { return m_angle; }
		void setLength(float length) { m_length = length; }
		float getLength() { return m_length; }
		void print(int einruecktiefe);
	private:
		SkeletonNode* m_child;
		SkeletonNode* m_parent;
		float m_angle;
		float m_length;
};

class Skeleton {
	public:
		Skeleton();
		~Skeleton();
		void setRoot(SkeletonNode* root) {
			m_root = root;
		}
		SkeletonNode* getRoot() { return m_root; }
		SkeletonNode* getJoint(int index);
		void print();
	private:
		SkeletonNode* m_root;
};

#endif // SKELETON_H