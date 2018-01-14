#include <vector>
#include "Box2D\Box2D.h"
#include "GameObject.h"
#include "LevelBuilder.h"

LevelBuilder::LevelBuilder(b2World* _world) {
	this->world = _world;
}

std::vector<StaticRectangle*> LevelBuilder::GenerateStatics(float32 _x, float32 _y)
{
	std::vector<StaticRectangle*> statics;
	
	return statics;
}

std::vector<StaticRectangle*>* LevelBuilder::GenerateStaticCurve(float32 _x, float32 _y, float32 _thickness, float32 _angleBegin, float32 _angleArc, int _angleSteps, float32 _curveScalarX, float32 _curveScalarY)
{
	// Init static object vector
	std::vector<StaticRectangle*>* statics = new std::vector<StaticRectangle*>(_angleSteps);
	// Init build positions
	std::vector<BuildPosition*>* buildPos = this->GetCurve(_angleBegin, _angleArc, _angleSteps);
	
	// Scale and transpose build points
	std::vector<b2Vec2*>* buildPoints = this->GetBuildPoints(*buildPos);
	this->ScaleCurve(buildPoints, _curveScalarX, _curveScalarY);
	this->TransposeCurve(buildPoints, _x, _y);
	//this->SetBuildPoints(buildPos, *buildPoints);
	
	// Get rectangle size
	float32 pointDistance = b2Distance(*(*buildPoints)[0], *(*buildPoints)[1]);
	b2Vec2 size(pointDistance, _thickness);
	
	// Create static objects
	std::vector<BuildPosition*>::iterator bPosIter = buildPos->begin();
	std::vector<StaticRectangle*>::iterator staticIter = statics->begin();
	for (; bPosIter != buildPos->end(); bPosIter++, staticIter++)
		*staticIter = new StaticRectangle(this->world, *((*bPosIter)->Point), size, (*((*bPosIter)->Angle)) + ((float32)M_PI/2.0f), &Assets::Instance()->images.b100x25);

	// Return vector list of static objects
	return statics;
}

std::vector<b2Vec2*>* LevelBuilder::GetBuildPoints(std::vector<BuildPosition*> _buildPositions)
{
	// Init buildPoints vector list
	std::vector<b2Vec2*>* buildPoints = new std::vector<b2Vec2*>(_buildPositions.size());
	// Declare iterators
	std::vector<BuildPosition*>::iterator bPosIter = _buildPositions.begin();
	std::vector<b2Vec2*>::iterator bPointIter = buildPoints->begin();

	// Copy points from BuildPosition vector list to buildPoints vector list
	for (; bPosIter != _buildPositions.end(); bPosIter++, bPointIter++)
		*bPointIter = (*bPosIter)->Point;//buildPoints->push_back((*iter)->Point);
	
	// Return point vector list
	return buildPoints;
}

void LevelBuilder::SetBuildPoints(std::vector<BuildPosition*>* _buildPosition, std::vector<b2Vec2*> _buildPoints) {
	// Init vector iterators
	std::vector<BuildPosition*>::iterator bPositionIter = _buildPosition->begin();
	std::vector<b2Vec2*>::iterator bPointIter = _buildPoints.begin();

	// Set buildPosition points from buildPoint vector
	for (; bPositionIter != _buildPosition->end() || bPointIter != _buildPoints.end(); bPositionIter++, bPointIter++)
		(*bPositionIter)->Point = *bPointIter;
}

std::vector<BuildPosition*>* LevelBuilder::GetCurve(float32 _begin, float32 _arc, int _steps)
{
	// Allocate point vector
	std::vector<BuildPosition*>* curvePositions = new std::vector<BuildPosition*>(_steps);
	// Get angle length per step along arc
	float32 stepAngle = _arc / (float32) (_steps - 1);
	BuildPosition* buildPos;
	// Store each step along arc
	for (int i = 0; i < _steps; i++) {
		buildPos = new BuildPosition();
		*buildPos->Angle = _begin + (stepAngle * (float32)i);
		buildPos->Point = this->CurvePos(*buildPos->Angle);
		(*curvePositions)[i] = buildPos;
	}	
	// Return vector of points along arc
	return curvePositions;
}

void LevelBuilder::ScaleCurve(std::vector<b2Vec2*>* _curve, float32 _scalar) {
	this->ScaleCurve(_curve, _scalar, _scalar);
}

void LevelBuilder::ScaleCurve(std::vector<b2Vec2*>* _curve, float32 _scalarX, float32 _scalarY) {
	// Define b2Vec2 iterator
	std::vector<b2Vec2*>::iterator it;
	// Scale each element of vector by scalar
	for (it = _curve->begin(); it != _curve->end(); it++) {
		(*it)->x *= _scalarX;
		(*it)->y *= _scalarY;
	}
}

void LevelBuilder::TransposeCurve(std::vector<b2Vec2*>* _curve, float32 _x, float32 _y) {
	// Define b2Vec2 iterator
	std::vector<b2Vec2*>::iterator it;
	// Scale each element of vector by scalar
	for (it = _curve->begin(); it != _curve->end(); it++) {
		(*it)->x += _x;
		(*it)->y += _y;
	}
}

b2Vec2* LevelBuilder::CurvePos(float32 _angle) {
	// Make rotation object
	b2Rot rotation(_angle);
	// Get unit b2Vec2 based on angle
	return new b2Vec2(rotation.c, rotation.s);
}
