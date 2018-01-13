#include "GameObject.h"

Snail::Snail(b2World* _world, b2Vec2 _pos, Assets::Image* _image) {
	this->mObjectId = Object_Snail;
	this->MoveLeft = false;
	this->MoveRight = false;
	this->Jump = false;
	this->Cling = false;
	this->InShell = false;
	
	this->mPhysicsBody = *(new PhysicsBody(_world, _pos, this->angleDamping, b2Shape::e_polygon, true));
	this->GetBody()->SetCircleShape(*(new b2Vec2(0.00f, 0.00f)), this->shellRadius);
	this->GetBody()->SetPolygonShape(*(new b2Vec2(this->standWidth, this->standHeight)), 0.0f);
	this->SetStandState();
}

bool Snail::ContactFloor() {
	return (this->GetBody()->GetTouchContacts().size() > 0) ? true : false;
}

void Snail::Update() {
	//// State Update
	if (this->InShell && this->GetBody()->GetShapeType() == b2Shape::e_polygon) this->SetShellState();
	if (!this->InShell && this->GetBody()->GetShapeType() == b2Shape::e_circle) this->SetStandState();

	//// Attribute update
	// If touching one or more static bodies, get average touch vector.
	b2Vec2 touchVector = this->GetBody()->GetTouchVector();
	// Set floor touch state
	this->touchingFloor = (touchVector.Length() == 0) ? false : true;

	// Set standing angle
	this->SetStandAngle(touchVector);

	// If snail isn't clinging, set default body attributes
	if (!this->Cling || !this->touchingFloor) this->SetPhysicalAttributes();

	//// Ground Controls
	if (this->touchingFloor) {
		switch (this->InShell) {
			// In shell
		case true:
			// Roll left/right
			if (this->MoveLeft)
				this->GetBody()->mBody->ApplyTorque(this->shellRollTorque, true);
			if (this->MoveRight)
				this->GetBody()->mBody->ApplyTorque(-(this->shellRollTorque), true);

			// Jump
			if (this->Jump)
				this->GetBody()->ApplyLinearImpulseToCenter(touchVector, this->shellJumpForce);

			// Wall Cling
			if (this->Cling) {
				// Set cling physical attributes
				this->SetClingPhysicalAttributes();

				// Reduce cling force if touching more than one static body. It gets...too clingy.
				if (this->GetBody()->GetTouchContacts().size() > 1)
					this->GetBody()->ApplyLinearImpulseToCenter(touchVector, -this->clingForce * 0.01f);
				// Apply cling force
				else
					this->GetBody()->ApplyLinearImpulseToCenter(touchVector, -this->clingForce);
			}

			break;

			// Out of shell
		case false:
			// Slide left/right
			if (this->MoveLeft)
				this->GetBody()->ApplyForceToCenter(this->GetBody()->GetAngle(), -this->standMoveForce);
			if (this->MoveRight)
				this->GetBody()->ApplyForceToCenter(this->GetBody()->GetAngle(), this->standMoveForce);

			// Jump
			if (this->Jump)
				this->GetBody()->ApplyLinearImpulseToCenter(this->GetBody()->GetAngle() + (float32)(M_PI / 2.0), this->standJumpForce);
			
			break;
		}
	}

	this->ResetFlags();
}

void Snail::SetStandAngle(b2Vec2 _touchVector) {
	float32 standAngle = 0.0f;
	float32 standAngleExaggeration = 2.5f;
	float32 standAngleTolerance = 0.4f;

	// If touching floor, align to touching surface
	if(this->touchingFloor)
		standAngle = (-b2Atan2(_touchVector.y, _touchVector.x) + (float32)(M_PI / 2.0)) * standAngleExaggeration;

	// Get modulo angle between {-2PI, 2PI}
	float32 modAngle = fmod(this->GetBody()->GetAngle() + standAngle, (float32)(2.0 * M_PI));
	// Set angle between [desiredAngle, 2PI + desiredAngle}
	if (modAngle < standAngle) modAngle += (float32)(2.0 * M_PI);
	// Set angle between [PI + desiredAngle, -PI + desiredAngle}
	if (modAngle > M_PI + standAngle) modAngle -= (float32)(2.0 * M_PI);
	
	// Rotate Snail until parallel with ground
	if (!this->InShell && (modAngle < standAngle - standAngleTolerance || modAngle > standAngle + standAngleTolerance)) {
		float32 nextAngle = modAngle + this->GetBody()->mBody->GetAngularVelocity() / 3.0f;
		float32 totalRotation = standAngle - nextAngle;
		this->GetBody()->mBody->ApplyTorque((totalRotation < standAngle ? -0.01f : 0.01f), true);
	}
}

void Snail::SetPhysicalAttributes() {
	this->GetBody()->mBody->SetLinearDamping(this->linearDamping);
	this->GetBody()->mBody->SetAngularDamping(this->angleDamping);
	this->GetBody()->mBody->SetGravityScale(this->gravityScale);
}

void Snail::SetClingPhysicalAttributes() {
	this->GetBody()->mBody->SetAngularDamping(this->clingAngleDamping);
	this->GetBody()->mBody->SetLinearDamping(this->clingLinearDamping);
	this->GetBody()->mBody->SetGravityScale(this->clingGravityScale);
}

void Snail::SetStandState() {
	this->GetImageData()->SetImage(&(Assets::Instance()->images.SnailKnight));
	this->GetBody()->SetShapeType(b2Shape::e_polygon);
	this->GetBody()->mBody->DestroyFixture(this->GetBody()->mBody->GetFixtureList());
	this->mPhysicsBody.SetFixtureDef(
		this->standDensity,
		this->standFriction,
		this->standRestitution
	);
}

void Snail::SetShellState() {
	this->GetImageData()->SetImage(&(Assets::Instance()->images.SnailKnightShell));
	this->GetBody()->SetShapeType(b2Shape::e_circle);
	this->GetBody()->mBody->DestroyFixture(this->GetBody()->mBody->GetFixtureList());
	this->mPhysicsBody.SetFixtureDef(
		this->shellDensity,
		this->shellFriction,
		this->shellRestitution
	);
}

void Snail::ResetFlags() {
	// Reset jump state
	Jump = false;
}
