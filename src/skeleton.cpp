#include <iostream>
#include <math.h>

#include "skeleton.h"

using namespace std;

SkeletonNode::SkeletonNode()
{
	m_parent = nullptr;
	m_child = nullptr;
}

SkeletonNode::~SkeletonNode()
{
	if(m_child)
		delete m_child;
}

void SkeletonNode::addChild(SkeletonNode* c)
{
	if(c)
	{
		c->m_parent = this;
		m_child = c;
	}
}

SkeletonNode* SkeletonNode::getJoint(int& index, const int searchIndex)
{
	if(index == searchIndex)
		return this;
	else
	{
		if(m_child == nullptr)
			return nullptr;
		else
		{
			SkeletonNode* searchNode = nullptr;
			index+=1;
			searchNode = m_child->getJoint(index, searchIndex);
			if(searchNode != nullptr)
				return searchNode;
		}
	}
	return nullptr;
}

void SkeletonNode::print(int einruecktiefe)
{
	for(int i=0; i<einruecktiefe; i++) cout << " ";
	cout << "angle = " << m_angle/M_PI*180.0f << endl;
	if(m_child)
		m_child->print(einruecktiefe+4);
}

Skeleton::Skeleton() : m_root(0) {}

Skeleton::~Skeleton()
{
	if(m_root)
		delete m_root;
}

SkeletonNode* Skeleton::getJoint(int index)
{
	int idx = 0;
	return m_root->getJoint(idx, index);
}

void Skeleton::print()
{
	if(m_root) m_root->print(0);
}