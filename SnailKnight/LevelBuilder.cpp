#include "LevelBuilder.h"

std::vector<StaticRectangle*> LevelBuilder::GenerateStatics(float32 _x, float32 _y)
{
	std::vector<StaticRectangle*> statics;
	
	return statics;
}

std::vector<b2Vec2> LevelBuilder::GenerateCurve(float32 _begin, float32 _arc, Uint32 _steps)
{
	// Allocate point vector
	std::vector<b2Vec2> curvePoints(_steps);
	// Get angle length per step along arc
	float32 stepAngle = _arc / (float32) (_steps - 1);
	// Store each step along arc
	for (int i = 0; i < _steps; i++)
		curvePoints.push_back(this->CurvePos(_begin + (stepAngle * (float32) i)));
	// Return vector of points along arc
	return curvePoints;
}

b2Vec2 LevelBuilder::CurvePos(float32 _angle) {
	// Make rotation object
	b2Rot rotation(_angle);
	// Get unit b2Vec2 based on angle
	return b2Vec2(rotation.s, rotation.c);
}
