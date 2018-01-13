#pragma once
#ifndef _PHYSICSBODY_H_
#define _PHYSICSBODY_H_

#include <vector>
#include "Box2D\Box2D.h"

class PhysicsBody;

class PhysicsBody {
public:
	// PhysicsBody Body properties
	b2World*		mParentWorld;
	b2BodyDef		mBodyDef;
	b2Body*			mBody;
	// PhysicsBody Shape properties
	b2ChainShape	mChainShape;
	b2CircleShape	mCircleShape;
	b2EdgeShape		mEdgeShape;
	b2PolygonShape	mPolygonShape;
	b2FixtureDef	mFixtureDef;
	b2Shape::Type	mShapeType;

	// PhysicsBody ctors
	PhysicsBody();
	PhysicsBody(b2World* _world, b2Vec2 _pos, float32 _ad, b2Shape::Type _shape, bool _dynamic);

	// Get properties
	b2Vec2 GetPosition() { return this->mBody->GetPosition(); }
	b2Vec2 GetWorldCenter() { return this->mBody->GetWorldCenter(); }
	float32 GetWidth();
	float32 GetHeight();
	float32 GetAngle();
	b2Shape::Type GetShapeType() { return this->mShapeType; }
	std::vector<b2Contact*> GetTouchContacts();
	std::vector<b2Contact*> GetTouchContacts(b2Body* _body);
	b2Vec2 GetTouchVector();

	// Get shape object
	b2Shape* GetShape();

	// Set body properties
	void SetWorld(b2World* _world) { this->mParentWorld = _world; }
	void SetDynamic() { this->mBodyDef.type = b2_dynamicBody; }
	void SetPosition(b2Vec2 _pos) { this->mBodyDef.position.Set(_pos.x, _pos.y); }
	void SetAngularDamping(float32 _ad) { this->mBodyDef.angularDamping = _ad; }
	void CreateBody() { this->mBody = this->mParentWorld->CreateBody(&(this->mBodyDef)); }

	// Set shape properties
	void SetShapeType(b2Shape::Type _shape);
	void SetCircleShape(b2Vec2 _p, float32 _radius);
	void SetCircleFixtureDef(b2Vec2 _p, float32 _radius, float32 _density, float32 _friction, float32 _restitution);
	void SetPolygonShape(b2Vec2 _size, float32 _angle);
	void SetPolygonFixtureDef(b2Vec2 _size, float32 _angle, float32 _density, float32 _friction, float32 _restitution);
	void SetFixtureDef(float32 _density, float32 _friction, float32 _restitution);

	// Apply Forces
	void ApplyForceToCenter(b2Vec2 _vector);
	void ApplyForceToCenter(b2Vec2 _vector, float32 _scalar);
	void ApplyForceToCenter(float32 _angle, float32 _scalar);
	void ApplyForceToCenter(float32 _angle);
	// Apply Linear Impulses
	void ApplyLinearImpulseToCenter(b2Vec2 _vector);
	void ApplyLinearImpulseToCenter(b2Vec2 _vector, float32 _scalar);
	void ApplyLinearImpulseToCenter(float32 _angle, float32 _scalar);
	void ApplyLinearImpulseToCenter(float32 _angle);
};

#endif