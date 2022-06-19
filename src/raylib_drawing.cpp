#include <math.h>
#include <raylib.h>
#include <chrono>
#include <thread>

#include "raylib_drawing.h"

void raylib_init(int width, int height, char* name) {
	InitWindow(width, height, name);
	SetTargetFPS(60);
}

void raylib_init(int width, int height) {
	raylib_init(width, height, "avc-uebung");
}

void raylib_init() {
	raylib_init(600, 600, "avc-uebung");
}

void raylib_draw_bonechain(int m_numBones, Vector2D* pivots, Vector2D& m_targetPos, Skeleton& m_skeleton) {
	BeginDrawing();

	ClearBackground(RAYWHITE);
	const int length = 100;
	for (int i = 0; i < m_numBones+1; i++) {
		//std::cout << "\t\tpivot " << i << ": ";
		//pivots[i].print();
		if (i < m_numBones) {
			DrawLineEx(
				Vector2{pivots[i].x*length+length*3, -pivots[i].y*length+length*3},
				Vector2{pivots[i+1].x*length+length*3, -pivots[i+1].y*length+length*3},
				5.0f,
				Color{255, 0, 0, 255}
			);
			//std::cout << "\t\tangle: " << m_skeleton.getJoint(i)->getAngle()/M_PI*180.0f << std::endl;
		}
		DrawCircle(
			pivots[i].x*length+length*3,
			-pivots[i].y*length+length*3,
			5.0f,
			BLUE
		);
	}
	// draw target position
	DrawCircle(
		m_targetPos.x*length+length*3,
		-m_targetPos.y*length+length*3,
		5.0f,
		GREEN
	);
	EndDrawing();
	// sleep after drawing
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
}