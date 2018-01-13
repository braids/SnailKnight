#pragma once
#ifndef _LEVELBUILDER_H_
#define _LEVELBUILDER_H_

#include "GameObject.h"
#include "Box2D\Box2D.h"

class LevelBuilder {
public:
	b2World* world;

	LevelBuilder(b2World* _world);

	std::vector<StaticRectangle*> GenerateStatics(float32 _x, float32 _y);

	std::vector<StaticRectangle*> GenerateStaticCurve(float32 _x, float32 _y, float32 _begin, float32 _arc, float32 _scalar);
	std::vector<b2Vec2> GetCurve(float32 _begin, float32 _arc, Uint32 _step);
	
	void ScaleCurve(std::vector<b2Vec2>* _curve, float32 _scalar);
	void ScaleCurve(std::vector<b2Vec2>* _curve, float32 _scalarX, float32 _scalarY);
	void TransposeCurve(std::vector<b2Vec2>* _curve, float32 _x, float32 _y);

	b2Vec2 CurvePos(float32 _angle);
};

#endif
