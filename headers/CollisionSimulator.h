#pragma once
#include "OpenGLWindow.h"
#include "Point3D.h"
#include "Orbit.h"
#include<vector>

class CollisionSimulator
{
public:
	CollisionSimulator();
	~CollisionSimulator();

public:
	void drawSolarSystem(std::vector<float>& mVertices, std::vector<float>& mColors);
	void resetPositions();
	/*void setDebrisRadius(float& size);
	void setDebrisDistance(float& altitude);
	void setDebrisSpeed(float& speed);*/
	void updatePositions(int numberOfDays);
	void setSpeedMultiplier(double speedMultiplier);
	const std::vector<float>& getCurrentVertices() const { return mCurrentVertices; }
	const std::vector<float>& getCurrentColors() const { return mCurrentColors; }

private:
	void drawOrbitingDebris(std::vector<float>& vertices, std::vector<float>& colors);

private:
	QVector<float> planetOrbitPeriod;
	double* mSpeedMultiplier;
	enum { numDebris = 3};
	const float debrisRadius[numDebris] = { 0.2f, 0.3f, 0.4f};
	const float debrisDistance[3] = { 2.0f, 3.0f, 4.0f, };
	const float debrisSpeed[numDebris] = { 0.25f, 0.2f, 0.15f};
	float debrisAngles[numDebris] = { 0.0f };

	std::vector<Point3D> mDebrisColors;

	std::vector<float> mCurrentVertices;
	std::vector<float> mCurrentColors;


	CollisionSimulator* solar;
	Orbit* orbit;
};
