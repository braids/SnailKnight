#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Graphics.h"
#include "Assets.h"
#include "Box2D\Box2D.h"
#include "PhysicsBody.h"

// Forward dec classes
class Position;
class ImageData;
class GameObject;
class Snail;
class StaticRectangle;

enum ObjectID {
	Object_Snail,
	Object_StaticRectangle
};

class Position {
protected:
	b2Vec2	position, dposition;
	float32	angle, dangle;

public:
	void SetPosition(b2Vec2 _pos) { this->position = _pos; }
	void SetdPosition(b2Vec2 _dpos) { this->dposition = _dpos; }
	void SetAngle(float32 _angle) { this->angle = _angle; }
	void SetdAngle(float32 _dangle) { this->angle = _dangle; }
	b2Vec2 GetPosition() { return this->position; }
	b2Vec2 GetdPosition() { return this->dposition; }
	float32 GetAngle() { return this->angle; }
	float32 GetdAngle() { return this->dangle; }
};

class ImageData {
protected:
	Assets::Image*	mImage;
	SDL_Rect*		mDrawRect;
	double			DrawAngle;

public:
	void SetImage(Assets::Image* _image) { 
		this->mImage = _image; 
		this->mDrawRect = Graphics::CreateRect(0, 0, 0, 0);
		this->mDrawRect->w = this->mImage->rect->w;
		this->mDrawRect->h = this->mImage->rect->h;
	}
	void SetDrawRect(SDL_Rect* _drawrect) { this->mDrawRect = _drawrect; }
	Assets::Image* GetImage() { return this->mImage; }
	SDL_Rect* GetDrawRect() { return this->mDrawRect; }
	void SetDrawAngle(double _angle) { this->DrawAngle = _angle; }
	double GetDrawAngle() { return this->DrawAngle; }
};

class GameObject {
protected:
	ObjectID	mObjectId;
	ImageData	mImageData;
	PhysicsBody	mPhysicsBody;
	bool Player;
	
public:
	GameObject();
	~GameObject();

	void SetPosition(b2Vec2 _pos) { this->SetPosition(_pos); }
	ImageData* GetImageData() { return &mImageData; }
	PhysicsBody* GetBody() { return &mPhysicsBody; }
	void SetDrawPos(Uint32 _x, Uint32 _y);
	void UpdateDrawRect(Uint32 _offsetX, Uint32 _offsetY);
	
	virtual void Update() = 0;	
};

class Snail : public GameObject {
public:
	// Standard body attributes
	float32 linearDamping = 0.0f;
	float32 angleDamping = 2.0f;
	float32 gravityScale = 1.0f;
	// Cling attributes
	float32 clingLinearDamping = 2.0f;
	float32 clingAngleDamping = 8.0f;
	float32 clingGravityScale = 0.0f;
	float32 clingForce = 0.002f;
	// Standing attributes
	float32 standWidth = 0.35f;
	float32 standHeight = 0.26f;
	float32 standDensity = 0.1f;
	float32 standFriction = 0.1f;
	float32 standRestitution = 0.0f;
	float32 standJumpForce = 0.0225f;
	float32 standMoveForce = 0.03f;
	// In shell attributes
	float32 shellRadius = 0.14f;
	float32 shellDensity = 0.1f;
	float32 shellFriction = 0.8f;
	float32 shellRestitution = 0.0f;
	float32 shellJumpForce = 0.015f;
	float32 shellRollTorque = 0.005f;

	// State flags
	bool InShell;
	bool touchingFloor;
	// Movement flags
	bool MoveLeft;
	bool MoveRight;
	bool Jump;
	bool Cling;
	
	// Ctor
	Snail(b2World* _world, b2Vec2 _pos, Assets::Image* _image);

	// Funcs
	bool ContactFloor();
	void Update();
	void SetStandAngle(b2Vec2 _touchVector);
	void SetPhysicalAttributes();
	void SetClingPhysicalAttributes();
	void SetStandState();
	void SetShellState();
	void ResetFlags();
};

class StaticRectangle : public GameObject {
public:
	StaticRectangle(b2World* _world, b2Vec2 _pos, Assets::Image* _image);
	StaticRectangle(b2World* _world, b2Vec2 _pos, b2Vec2 _size, float32 _angle, Assets::Image* _image);
	void Update();
};

#endif