#pragma once
#ifndef _LEVELBUILDER_H_
#define _LEVELBUILDER_H_

#include "GameObject.h"
#include "Box2D\Box2D.h"

class LevelBuilder {
	std::vector<StaticRectangle*> GenerateStatics(float32 _x, float32 _y);
	std::vector<b2Vec2> GenerateCurve(float32 _begin, float32 _arc, Uint32 _step);
	b2Vec2 CurvePos(float32 _angle);
};

#endif
