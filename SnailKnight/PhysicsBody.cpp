#include <vector>
#include "Box2D\Box2D.h"
#include "PhysicsBody.h"

PhysicsBody::PhysicsBody() {

}

PhysicsBody::PhysicsBody(b2World* _world, b2Vec2 _pos, float32 _ad, b2Shape::Type _shape, bool _dynamic) {
	this->SetWorld(_world);
	if(_dynamic) this->SetDynamic();
	this->SetPosition(_pos);
	if (_ad != NULL) this->SetAngularDamping(_ad);
	this->CreateBody();
	this->SetShapeType(_shape);
}

float32 PhysicsBody::GetWidth() {
	if (this->GetShapeType() == b2Shape::e_circle)
		return this->mCircleShape.m_radius;
	
	if (this->GetShapeType() == b2Shape::e_polygon)
		return b2Distance(
				this->mPolygonShape.m_vertices[0], 
				this->mPolygonShape.m_vertices[1]
			) / 2.0f;

	return 0.0f;
}

float32 PhysicsBody::GetHeight() {
	if (this->GetShapeType() == b2Shape::e_circle)
		return this->mCircleShape.m_radius;
	
	if (this->GetShapeType() == b2Shape::e_polygon)
		return b2Distance(
				this->mPolygonShape.m_vertices[0], 
				this->mPolygonShape.m_vertices[3]
			) / 2.0f;

	return 0.0f;
}

float32 PhysicsBody::GetAngle() {
	if (this->GetShapeType() == b2Shape::e_polygon && this->mBody->GetType() != b2_dynamicBody)
		return b2Atan2(
			this->mPolygonShape.m_vertices[1].y - this->mPolygonShape.m_vertices[0].y, 
			this->mPolygonShape.m_vertices[1].x - this->mPolygonShape.m_vertices[0].x
		);
	else
		return this->mBody->GetAngle();
	return 0.0f;
}

std::vector<b2Contact*> PhysicsBody::GetTouchContacts() {
	return this->GetTouchContacts(this->mBody);
}

std::vector<b2Contact*> PhysicsBody::GetTouchContacts(b2Body* _body) {
	// Initialize vector list of touching contacts
	std::vector<b2Contact*> contactVector;

	// If contacts are made, get all contacts
	if (this->mBody->GetContactList() != nullptr) {
		// Get first contact
		b2Contact* currContact = this->mBody->GetContactList()->contact;

		while (true) {
			// If contact is touching, add to vector list
			if (currContact->IsTouching())
				contactVector.push_back(currContact);

			// If next contact exists, get next contact
			if (currContact->GetNext() != nullptr)
				currContact = currContact->GetNext();
			// If no more contacts exists, exit loop.
			else
				break;
		}
	}
	
	// Return vector list of touching contacts
	return contactVector;
}

b2Vec2 PhysicsBody::GetTouchVector() {
	// Initialize average b2Vec2 of touching contacts
	b2Vec2 avgTouchVector(0.0f, 0.0f);
	
	// Get vector list of touching contacts
	std::vector<b2Contact*> touchContacts = this->GetTouchContacts();
	std::vector<b2Vec2> contactNormals(0);
	b2Vec2 currNormal;
	if (touchContacts.size() > 0) {
		// Add all touching contact normals to avgTouchVector
		for (int i = 0; i < touchContacts.size(); i++) {
			currNormal = touchContacts[i]->GetManifold()->localNormal;
			if (i == 0)
				contactNormals.push_back(currNormal);
			else if(*std::find(contactNormals.begin(), contactNormals.end(), currNormal) == *contactNormals.end())
				contactNormals.push_back(currNormal);
		}
		for (std::vector<b2Vec2>::iterator it = contactNormals.begin(); it != contactNormals.end(); it++)
			avgTouchVector += *it;
			//avgTouchVector += touchContacts[i]->GetManifold()->localNormal;

		// Divide avgTouchVector by number of contacts made
		//avgTouchVector *= (1.0f / (float32)touchContacts.size());
		avgTouchVector *= (1.0f / (float32)contactNormals.size());
	}

	// Return average b2Vec2 of touching contacts
	return avgTouchVector;
}

b2Shape* PhysicsBody::GetShape() {
	switch (this->GetShapeType()) {
	case b2Shape::e_chain:
		return &(this->mChainShape);
		break;
	case b2Shape::e_circle:
		return &(this->mCircleShape);
		break;
	case b2Shape::e_edge:
		return &(this->mEdgeShape);
		break;
	case b2Shape::e_polygon:
		return &(this->mPolygonShape);
		break;
	default:
		return nullptr;
		break;
	}
}

void PhysicsBody::SetShapeType(b2Shape::Type _shape) {
	this->mShapeType = _shape;
}

void PhysicsBody::SetCircleShape(b2Vec2 _p, float32 _radius) {
	this->mCircleShape.m_p.Set(_p.x, _p.y);
	this->mCircleShape.m_radius = _radius;
}

void PhysicsBody::SetCircleFixtureDef(b2Vec2 _p, float32 _radius, float32 _density, float32 _friction, float32 _restitution) {
	this->SetCircleShape(_p, _radius);
	this->SetFixtureDef(_density, _friction, _restitution);
}

void PhysicsBody::SetPolygonShape(b2Vec2 _size, float32 _angle) {
	this->mPolygonShape.SetAsBox(_size.x / 2.0f, _size.y / 2.0f , *(new b2Vec2(0.0f, 0.0f)), _angle);
}

void PhysicsBody::SetPolygonFixtureDef(b2Vec2 _size, float32 _angle, float32 _density, float32 _friction, float32 _restitution) {
	this->SetPolygonShape(_size, _angle);
	this->SetFixtureDef(_density, _friction, _restitution);
}

void PhysicsBody::SetFixtureDef(float32 _density, float32 _friction, float32 _restitution) {
	this->mFixtureDef.shape = this->GetShape();
	this->mFixtureDef.density = _density;
	this->mFixtureDef.friction = _friction;
	this->mFixtureDef.restitution = _restitution;
	this->mBody->CreateFixture(&(this->mFixtureDef));
}

// Apply Forces
void PhysicsBody::ApplyForceToCenter(b2Vec2 _vector) {
	this->mBody->ApplyForceToCenter(_vector, true);
}


void PhysicsBody::ApplyForceToCenter(b2Vec2 _vector, float32 _scalar) {
	_vector *= _scalar;
	this->ApplyForceToCenter(_vector);
}

void PhysicsBody::ApplyForceToCenter(float32 _angle, float32 _scalar) {
	b2Rot rotation(_angle);
	b2Vec2 vector(rotation.c, rotation.s);
	this->ApplyForceToCenter(vector, _scalar);
}

void PhysicsBody::ApplyForceToCenter(float32 _angle) {
	this->ApplyForceToCenter(_angle, 1.0f);
}

// Apply Linear Impulses
void PhysicsBody::ApplyLinearImpulseToCenter(b2Vec2 _vector) {
	this->mBody->ApplyLinearImpulseToCenter(_vector, true);
}


void PhysicsBody::ApplyLinearImpulseToCenter(b2Vec2 _vector, float32 _scalar) {
	_vector *= _scalar;
	this->ApplyLinearImpulseToCenter(_vector);
}

void PhysicsBody::ApplyLinearImpulseToCenter(float32 _angle, float32 _scalar) {
	b2Rot rotation(_angle);
	b2Vec2 vector(rotation.c, rotation.s);
	this->ApplyLinearImpulseToCenter(vector, _scalar);
}

void PhysicsBody::ApplyLinearImpulseToCenter(float32 _angle) {
	this->ApplyLinearImpulseToCenter(_angle, 1.0f);
}