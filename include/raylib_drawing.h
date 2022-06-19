#include <raylib.h>
#include <chrono>
#include <thread>

#include "skeleton.h"
#include "vector2d.h"

void raylib_draw_bonechain(int m_numBones, Vector2D* pivots, Vector2D m_targetPos, Skeleton m_skeleton) {
	/* output */
	BeginDrawing();

	ClearBackground(RAYWHITE);
	const int length = 100;
	for (int i = 0; i < m_numBones+1; i++) {
		std::cout << "\t\tpivot " << i << ": ";
		pivots[i].print();
		if (i < m_numBones) {
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
}