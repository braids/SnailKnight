#include "GameObject.h"

Snail::Snail(b2World* _world, b2Vec2 _pos, Assets::Image* _image) {
	this->mObjectId = Object_Snail;
	this->RollLeft = false;
	this->RollRight = false;
	this->Jump = false;
	this->Cling = false;
	this->mImageData.SetImage(_image);
	this->mPhysicsBody = *(new PhysicsBody(_world, _pos, this->ad, b2Shape::e_circle, true));
	this->mPhysicsBody.SetCircleFixtureDef(
		*(new b2Vec2(0.0f, 0.0f)), 
		this->radius, 
		this->density, 
		this->friction, 
		this->restitution
	);
}

bool Snail::ContactFloor() {
	return (this->GetBody()->GetTouchContacts().size() > 0) ? true : false;
}

void Snail::Update() {
	b2Vec2 touchVector;
	
	// If touching one or more static bodies, get average touch vector.
	if (this->ContactFloor())
		touchVector = this->GetBody()->GetTouchVector();

	// Roll snail left
	if (RollLeft) {
		this->GetBody()->mBody->ApplyTorque(this->RollTorque, true);
	}
	
	// Roll snail right
	if (RollRight) {
		this->GetBody()->mBody->ApplyTorque(-(this->RollTorque), true);
	}

	// Snail jump
	if (this->Jump && touchVector.Length() != 0) {
		// Get jump vector
		b2Vec2 jumpVector = touchVector;
		jumpVector *= this->jumpForce;
		
		// Apply jump vector
		this->GetBody()->mBody->ApplyLinearImpulseToCenter(jumpVector, true);
		
		// Reset jump state
		this->Jump = false;
	}

	// If snail isn't clinging, set default body attributes
	if (!this->Cling || touchVector.Length() == 0) {
		// Reset physical attributes when not clinging
		this->GetBody()->mBody->SetLinearDamping(0.0f);
		this->GetBody()->mBody->SetAngularDamping(this->ad);
		this->GetBody()->mBody->SetGravityScale(1.0f);
	}

	// Snail cling to surface
	if (this->Cling && touchVector.Length() != 0) {
		// Set cling physical attributes
		this->GetBody()->mBody->SetAngularDamping(8.0f);
		this->GetBody()->mBody->SetLinearDamping(2.0f);
		this->GetBody()->mBody->SetGravityScale(0.0f);
		
		// Get cling vector
		b2Vec2 clingVector = touchVector;
		clingVector *= -this->clingForce;
		// Reduce cling force if touching more than one static body. It gets...too clingy.
		if (this->GetBody()->GetTouchContacts().size() > 1)
			clingVector *= 0.01f;

		// Apply cling force
		this->GetBody()->mBody->ApplyLinearImpulseToCenter(clingVector, true);
	}

}