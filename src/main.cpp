#include <iostream>
#include <raylib.h>

#include "skeleton.h"
#include "ccd.h"

using namespace std;

int main(int argc, char** argv) {
	CCD ccd = CCD();
	// create angle array
	float angles[] = {30.0f, 30.0f, 30.0f};
	// create skeleton
	ccd.setBoneChain(angles);
	// set target position
	ccd.setTargetPosition(1.5f, 1.0f);

	// get skeleton for output
	Skeleton* skeleton = ccd.getSkeleton();

	// print skeleton
	skeleton->print();

	ccd.apply(10, 0.01f);

	// print skeleton after ccd
	skeleton->print();

	while (!WindowShouldClose());
	CloseWindow();

	return 0;
}
