#include "LevelBuilder.h"

LevelBuilder::LevelBuilder(b2World* _world) {
	this->world = _world;
}

std::vector<StaticRectangle*> LevelBuilder::GenerateStatics(float32 _x, float32 _y)
{
	std::vector<StaticRectangle*> statics;
	
	return statics;
}

std::vector<StaticRectangle*> LevelBuilder::GenerateStaticCurve(float32 _x, float32 _y, float32 _begin, float32 _arc, float32 _scalar)
{
	return std::vector<StaticRectangle*>();
}

std::vector<b2Vec2> LevelBuilder::GetCurve(float32 _begin, float32 _arc, Uint32 _steps)
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

void LevelBuilder::ScaleCurve(std::vector<b2Vec2>* _curve, float32 _scalar) {
	this->ScaleCurve(_curve, _scalar, _scalar);
}

void LevelBuilder::ScaleCurve(std::vector<b2Vec2>* _curve, float32 _scalarX, float32 _scalarY) {
	// Define b2Vec2 iterator
	std::vector<b2Vec2>::iterator it;
	// Scale each element of vector by scalar
	for (it = _curve->begin(); it != _curve->end(); it++) {
		it->x *= _scalarX;
		it->y *= _scalarY;
	}
}

void LevelBuilder::TransposeCurve(std::vector<b2Vec2>* _curve, float32 _x, float32 _y) {
	// Define b2Vec2 iterator
	std::vector<b2Vec2>::iterator it;
	// Scale each element of vector by scalar
	for (it = _curve->begin(); it != _curve->end(); it++) {
		it->x += _x;
		it->y += _y;
	}
}

b2Vec2 LevelBuilder::CurvePos(float32 _angle) {
	// Make rotation object
	b2Rot rotation(_angle);
	// Get unit b2Vec2 based on angle
	return b2Vec2(rotation.s, rotation.c);
}
