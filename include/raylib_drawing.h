#ifndef RAYLIB_DRAWING_H
#define RAYLIB_DRAWING_H

#include "skeleton.h"
#include "vector2d.h"

void raylib_init(int width, int height, char* name);
void raylib_init(int width, int height);
void raylib_init();
void raylib_draw_bonechain(int m_numBones, Vector2D* pivots, Vector2D& m_targetPos, Skeleton& m_skeleton);

#endif //RAYLIB_DRAWING_H