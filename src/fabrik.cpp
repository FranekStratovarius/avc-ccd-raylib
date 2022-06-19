#include <math.h>
#include <raylib.h>
#include <chrono>
#include <thread>

#include "fabrik.h"

FABRIK::FABRIK () {}

// get skeleton used in ccd
Skeleton* FABRIK::getSkeleton () {
	return &m_skeleton;
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

	

	for (int i = 0; i < maxIter; i++) {
	}
	
	return false;
}