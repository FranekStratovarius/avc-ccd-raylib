#include <math.h>
#include <raylib.h>
#include <chrono>
#include <thread>

#include "raylib_drawing.h"
#include "fabrik.h"

FABRIK::FABRIK () {}

// get skeleton used in ccd
Skeleton* FABRIK::getSkeleton () {
	return &m_skeleton;
}

// get pivot points with forward kinematic
void FABRIK::getPivotPositions (int count, Vector2D* pivot) {
	float cumulative_angle = 0.0f;
	Vector2D last_end = Vector2D();

	for (int i = 0; i < count; i++) {
		// get bone from skeleton
		SkeletonNode* bone = m_skeleton.getJoint(i);
		// get current angle and accumulate it with all the other angles
		cumulative_angle += bone->getAngle();
		// forward kinematic
		Vector2D local_pivot = Vector2D(cos(cumulative_angle), sin(cumulative_angle));
		last_end = last_end + local_pivot;

		// set pivot
		pivot[i+1] = last_end;
	}
}

// set target position
void FABRIK::setTargetPosition (float tx, float ty) {
	m_targetPos = Vector2D(tx, ty);
}

// run fabrik
bool FABRIK::apply (const int maxIter, const float eps) {
	/* raylib */
	InitWindow(600, 600, "ccd");

	SetTargetFPS(60);
	/* raylib end */

	// calculate pivotpositions
	Vector2D pivots[m_numBones+1];
	pivots[0] = Vector2D(0, 0);
	for (int i = 1; i < m_numBones+1; i++) {
		SkeletonNode* bone = m_skeleton.getJoint(i-1);
		pivots[i] = Vector2D(bone->getLength(), 0);
	}
	getPivotPositions(m_numBones, pivots);
	for (int i = 0; i < m_numBones+1; i++) {
		std::cout << "pivot " << i << ": ";
		pivots[i].print();
	}
	// save base position as first pivot
	Vector2D base = pivots[0];
	// endeffector is last pivot
	Vector2D endeffector = pivots[m_numBones];

	raylib_draw_bonechain(m_numBones, pivots, m_targetPos, m_skeleton);

	for (int i = 0; i < maxIter; i++) {
		// forward reaching
		std::cout << "forward reaching" << std::endl;
		// set end effector to target when first pivot
		pivots[m_numBones] = m_targetPos;
		raylib_draw_bonechain(m_numBones, pivots, m_targetPos, m_skeleton);
		for (int i = m_numBones-1; i >= 0; i--) {
			std::cout << " " << i << std::endl;
			// get direction vector from previous pivot
			Vector2D direction = pivots[i+1] - pivots[i];
			// norm direction vector
			direction = direction / direction.norm();
			// get current bone
			SkeletonNode* bone = m_skeleton.getJoint(i);
			// walk length of bone
			direction = direction * bone->getLength();
			// go length of bone in direction
			pivots[i] = pivots[i+1] - direction;
			raylib_draw_bonechain(m_numBones, pivots, m_targetPos, m_skeleton);
		}

		// backward reaching
		std::cout << "backward reaching" << std::endl;
		// set first pivot to base
		pivots[0] = base;
		raylib_draw_bonechain(m_numBones, pivots, m_targetPos, m_skeleton);
		for (int i = 1; i <= m_numBones; i++) {
			std::cout << " " << i << std::endl;
			// get direction vector from previous pivot
			Vector2D direction = pivots[i-1] - pivots[i];
			// norm direction vector
			direction = direction / direction.norm();
			// get current bone
			SkeletonNode* bone = m_skeleton.getJoint(i-1);
			// walk length of bone
			direction = direction * bone->getLength();
			// go length of bone in direction
			pivots[i] = pivots[i-1] - direction;
			raylib_draw_bonechain(m_numBones, pivots, m_targetPos, m_skeleton);
		}

		// endeffector is last pivot
		endeffector = pivots[m_numBones];
		
		if ((m_targetPos-endeffector).norm() < eps) {
			std::cout << "m_targetPos: ";
			m_targetPos.print();
			std::cout << "endeffector: ";
			endeffector.print();
			return true;
		}
	}
	
	return false;
}