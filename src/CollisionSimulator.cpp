#include "stdafx.h"
#include "CollisionSimulator.h"

CollisionSimulator::CollisionSimulator()
{
	mDebrisColors =
	{
	Point3D(1.0, 0.0, 0.0),  // Red
	Point3D(0.0, 1.0, 0.0),  // Green
	Point3D(0.0, 0.0, 1.0),  // Blue
	};
	mSpeedMultiplier = new double;
	orbit = new Orbit();
	*mSpeedMultiplier = 1.0;

	planetOrbitPeriod = {
		87.97f,
		224.7f,
		365.0f
	};
}

CollisionSimulator::~CollisionSimulator()
{

}

void CollisionSimulator::drawSolarSystem(std::vector<float>& mVertices, std::vector<float>& mColors)
{
	//orbit->drawColoredCircle(mVertices, mColors, 0.0f, 0.0f, 0.5f, 600, Point3D(1.0, 1.0, 0.0));
	drawOrbitingDebris(mVertices, mColors);
}

void CollisionSimulator::drawOrbitingDebris(std::vector<GLfloat>& mVertices, std::vector<GLfloat>& mColors)
{

	for (int i = 0; i < numDebris; ++i) {
		float theta = float(debrisAngles[i]) * 3.1415926f / 180.0f;
		float x = debrisDistance[i] * cosf(theta);
		float y = debrisDistance[i] * sinf(theta);
		orbit->drawCircle(mVertices, mColors, 0, 0, debrisDistance[i], 100);

		// Angle Should be 360 degrees
		if (debrisAngles[i] >= 360.0f) {
			debrisAngles[i] -= 360.0f;
		}
	}
}

void CollisionSimulator::setSpeedMultiplier(double speedMultiplier)
{
	*mSpeedMultiplier = speedMultiplier;
}

void CollisionSimulator::resetPositions()
{
	for (int i = 0; i < numDebris; ++i)
	{
		debrisAngles[i] = 0.0f;
	}
}

void CollisionSimulator::updatePositions(int numberOfDays)
{
	for (int i = 0; i < numDebris; ++i)
	{
		float rotationAngle = 360.0f * (static_cast<float>(numberOfDays) / planetOrbitPeriod[i]);
		debrisAngles[i] += rotationAngle;
	}

}

//void CollisionSimulator::setDebrisRadius(float& size) {
//
//	for (int i = 0; i < numDebris; ++i)
//	{
//		debrisRadius[i] += size / 2;
//	}
//}
//
//void CollisionSimulator::setDebrisDistance(float& altitude) {
//	for (int i = 0; i < numDebris; ++i)
//	{
//		debrisDistance[i] += altitude / 2;
//	}
//}
//
//void CollisionSimulator::setDebrisSpeed(float& speed) {
//	debrisSpeed = speed;
//}