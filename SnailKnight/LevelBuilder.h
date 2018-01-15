#pragma once
#ifndef _LEVELBUILDER_H_
#define _LEVELBUILDER_H_

#include <vector>
#include "GameObject.h"
#include "Box2D\Box2D.h"

// Forward dec SceneName enum
enum SceneName;

class BuildPosition {
public:
	b2Vec2 Point;
	float32 Angle;

	BuildPosition() {
		Point = b2Vec2(0.0f, 0.0f);
		Angle = 0.0f;
	}

	BuildPosition(float32 x, float32 y, float32 ang) {
		Point.Set(x, y);
		Angle = ang;
	}
};

class LevelBuilder {
public:
	b2World* world;

	LevelBuilder(b2World* _world);

	std::vector<StaticRectangle*> GenerateStatics(SceneName _scene);
	std::vector<StaticRectangle*>* GenerateStaticCurve(float32 _x, float32 _y, float32 _thickness, float32 _angleBegin, float32 _angleArc, int _angleSteps, float32 _curveScalarX, float32 _curveScalarY);
	std::vector<b2Vec2*>* GetBuildPoints(std::vector<BuildPosition*> _buildPositions);
	std::vector<BuildPosition*>* GetCurve(float32 _begin, float32 _arc, int _steps);

	void ScaleCurve(std::vector<b2Vec2*>* _curve, float32 _scalar);
	void ScaleCurve(std::vector<b2Vec2*>* _curve, float32 _scalarX, float32 _scalarY);
	void TransposeCurve(std::vector<b2Vec2*>* _curve, float32 _x, float32 _y);

	b2Vec2 CurvePos(float32 _angle);
};

#endif
