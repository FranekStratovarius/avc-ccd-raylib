#include <iostream>
#include <raylib.h>

#include "skeleton.h"
#include "ccd.h"
#include "fabrik.h"

using namespace std;

int main(int argc, char** argv) {
	bool ccd = false;
	if (ccd) {
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
	} else {
		FABRIK fabrik = FABRIK();
		// create angle array
		float angles[] = {30.0f, 30.0f, 30.0f};
		// create length array
		float lengthes[] = {1.0f, 1.0f, 1.0f};
		//create skeleton
		fabrik.setBoneChain(angles, lengthes);
		// set target position
		fabrik.setTargetPosition(1.5f, 1.0f);
		// run fabrik
		fabrik.apply(10, 0.01f);
	}

	while (!WindowShouldClose());
	CloseWindow();

	return 0;
}
