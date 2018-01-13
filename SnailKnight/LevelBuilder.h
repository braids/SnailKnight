#pragma once
#ifndef _LEVELBUILDER_H_
#define _LEVELBUILDER_H_

#include "GameObject.h"
#include "Box2D\Box2D.h"

class LevelBuilder {
	std::vector<StaticRectangle*> GenerateStatics(float32 _x, float32 _y);
	std::vector<b2Vec2> GenerateCurve(float32 _begin, float32 _arc, Uint32 _step);
	void ScaleCurve(std::vector<b2Vec2>* _curve, float32 _scalar);
	void ScaleCurve(std::vector<b2Vec2>* _curve, float32 _scalarX, float32 _scalarY);
	b2Vec2 CurvePos(float32 _angle);
};

#endif
