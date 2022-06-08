#include <math.h>
#include <raylib.h>
#include <chrono>
#include <thread>

#include "ccd.h"

CCD::CCD () {}

// get skeleton used in ccd
Skeleton* CCD::getSkeleton ()
{
	return &m_skeleton;
}

// get pivot points with forward kinematic
void CCD::getPivotPositions (int count, Vector2D* pivot)
{
	float cumulative_angle = 0.0f;
	Vector2D last_end = Vector2D();

	for (int i = 0; i < count; i++)
	{
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
void CCD::setTargetPosition (float tx, float ty)
{
	m_targetPos = Vector2D(tx, ty);
}

// run ccd
bool CCD::apply (const int maxIter, const float eps)
{
	/* raylib */
	InitWindow(600, 600, "ccd");

	SetTargetFPS(60);
	/* raylib end */

	// targetposition = m_targetPos
	// calculate pivotpositions
	Vector2D pivots[m_numBones+1];
	pivots[0] = Vector2D(0, 0);
	for (int i = 1; i < m_numBones+1; i++)
	{
		pivots[i] = Vector2D(1, 0);
	}
	getPivotPositions(m_numBones, pivots);
	for (int i = 0; i < m_numBones+1; i++)
	{
		std::cout << "pivot " << i << ": ";
		pivots[i].print();
	}
	// endeffector is last pivot
	Vector2D endeffector = pivots[m_numBones];

	for (int k = 1; k < maxIter; k++)
	{
		std::cout << "--- iteration " << k << " ---" << std::endl;
		for (int i = m_numBones-1; i >= 0;i--)	// iterate through the pivots starting with the last
		{
			std::cout << "\t--- bone " << i << " ---" << std::endl;
			// vector to the endeffector
			Vector2D u = endeffector - pivots[i];
			// vector to the target position
			Vector2D v = m_targetPos - pivots[i];
			// get current bone
			SkeletonNode* bone = m_skeleton.getJoint(i);
			// get old angle
			float angle = bone->getAngle();
			// calculate new angle and add it to the old
			float local_angle = acos((u * v) / (u.norm() * v.norm()));
			// use last row of cross product for direction
			if ((u.x * v.y - u.y * v.x) < 0)
			{
				local_angle = -local_angle;
			}

			angle += local_angle;
		
			// set angle of bone
			bone->setAngle(angle);
			// update pivots with forward kinematic
			getPivotPositions(m_numBones, pivots);

			/* output */
			BeginDrawing();

			ClearBackground(RAYWHITE);
			const int length = 100;
			for (int i = 0; i < m_numBones+1; i++)
			{
				std::cout << "\t\tpivot " << i << ": ";
				pivots[i].print();
				if (i < m_numBones)
				{
					DrawLineEx(
						Vector2{pivots[i].x*length+length*3, -pivots[i].y*length+length*3},
						Vector2{pivots[i+1].x*length+length*3, -pivots[i+1].y*length+length*3},
						5.0f,
						Color{255, 0, 0, 255}
					);
					DrawCircle(
						m_targetPos.x*length+length*3,
						-m_targetPos.y*length+length*3,
						5.0f,
						GREEN
					);
					std::cout << "\t\tangle: " << m_skeleton.getJoint(i)->getAngle()/M_PI*180.0f << std::endl;
				}
			}
			EndDrawing();
			// sleep after drawing
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			/* output end */

			// endeffector is last pivot
			endeffector = pivots[m_numBones];

			if ((m_targetPos-endeffector).norm() < eps)
			{
				std::cout << "m_targetPos: ";
				m_targetPos.print();
				std::cout << "endeffector: ";
				endeffector.print();
				return true;
			}
		}
	}
	return false;
}