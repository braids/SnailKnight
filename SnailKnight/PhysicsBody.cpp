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
		return std::abs(
			b2Distance(
				this->mPolygonShape.m_vertices[0], 
				this->mPolygonShape.m_vertices[1]
			) / 2.0f
		);

	return 0.0f;
}

float32 PhysicsBody::GetHeight() {
	if (this->GetShapeType() == b2Shape::e_circle)
		return this->mCircleShape.m_radius;
	
	if (this->GetShapeType() == b2Shape::e_polygon)
		return std::abs(
			b2Distance(
				this->mPolygonShape.m_vertices[0], 
				this->mPolygonShape.m_vertices[3]
			) / 2.0f
		);

	return 0.0f;
}

float32 PhysicsBody::GetAngle() {
	if (this->GetShapeType() == b2Shape::e_circle)
		return this->mBody->GetAngle();
	
	if (this->GetShapeType() == b2Shape::e_polygon)
		return b2Atan2(
			this->mPolygonShape.m_vertices[1].y - this->mPolygonShape.m_vertices[0].y, 
			this->mPolygonShape.m_vertices[1].x - this->mPolygonShape.m_vertices[0].x
		);

	return 0.0f;
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