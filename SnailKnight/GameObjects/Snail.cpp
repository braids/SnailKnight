#include "GameObject.h"

Snail::Snail(b2World* _world, b2Vec2 _pos, Assets::Image* _image) {
	this->mObjectId = Object_Snail;
	RollLeft = false;
	RollRight = false;
	this->mImageData.SetImage(_image);
	this->mPhysicsBody = *(new PhysicsBody(_world, _pos, 0.5f, b2Shape::e_circle, true));
	this->mPhysicsBody.SetCircleFixtureDef(*(new b2Vec2(0.0f, 0.0f)), 0.125f, 0.1f, 0.4f, 0.5f);
}

void Snail::Update() {
	if (RollLeft) {
		this->GetBody()->mBody->ApplyTorque(this->RollTorque, true);
	}
	
	if (RollRight) {
		this->GetBody()->mBody->ApplyTorque(-(this->RollTorque), true);
	}
}