#include "GameObject.h"

Snail::Snail(b2World* _world, b2Vec2 _pos, Assets::Image* _image) {
	this->mObjectId = Object_Snail;
	RollLeft = false;
	RollRight = false;
	this->Jump = false;
	this->mImageData.SetImage(_image);
	this->mPhysicsBody = *(new PhysicsBody(_world, _pos, this->ad, b2Shape::e_circle, true));
	this->mPhysicsBody.SetCircleFixtureDef(*(new b2Vec2(0.0f, 0.0f)), radius, density, friction, restitution);
}

bool Snail::ContactFloor()
{
	if (this->GetBody()->mBody->GetContactList() != nullptr) {
		b2Contact* currContact = this->GetBody()->mBody->GetContactList()->contact;
		
		while (true) {
			if (currContact->IsTouching())
				return true;
			
			if (currContact->GetNext() != nullptr)
				currContact = currContact->GetNext();
			else
				break;
		}
	}

	return false;
}

void Snail::Update() {
	if (RollLeft) {
		this->GetBody()->mBody->ApplyTorque(this->RollTorque, true);
	}
	
	if (RollRight) {
		this->GetBody()->mBody->ApplyTorque(-(this->RollTorque), true);
	}

	if (this->Jump && this->ContactFloor()) {
		b2Vec2 jumpVector = this->GetBody()->mBody->GetContactList()->contact->GetManifold()->localNormal;
		jumpVector *= this->jumpForce;
		this->GetBody()->mBody->ApplyLinearImpulseToCenter(jumpVector, true);
		this->Jump = false;
	}
}