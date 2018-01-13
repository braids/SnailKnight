#pragma once
#ifndef _LEVELBUILDER_H_
#define _LEVELBUILDER_H_

#include <vector>
#include "GameObject.h"
#include "Box2D\Box2D.h"

class BuildPosition {
public:
	b2Vec2 Point;
	float32 Angle;
};

class LevelBuilder {
public:
	b2World* world;

	LevelBuilder(b2World* _world);

	std::vector<StaticRectangle*> GenerateStatics(float32 _x, float32 _y);

	std::vector<StaticRectangle*> GenerateStaticCurve(float32 _x, float32 _y, float32 _thickness, float32 _angleBegin, float32 _angleArc, int _angleSteps, float32 _curveScalarX, float32 _curveScalarY);
	
	std::vector<b2Vec2> GetBuildPoints(std::vector<BuildPosition> _buildPositions);
	void SetBuildPoints(std::vector<BuildPosition>* _buildPosition, std::vector<b2Vec2> _buildPoints);
	std::vector<BuildPosition> GetCurve(float32 _begin, float32 _arc, int _steps);

	void ScaleCurve(std::vector<b2Vec2>* _curve, float32 _scalar);
	void ScaleCurve(std::vector<b2Vec2>* _curve, float32 _scalarX, float32 _scalarY);
	void TransposeCurve(std::vector<b2Vec2>* _curve, float32 _x, float32 _y);

	b2Vec2 CurvePos(float32 _angle);
};

#endif
