#include "GameObject.h"

StaticRectangle::StaticRectangle(b2World* _world, b2Vec2 _pos, Assets::Image* _image) {
	this->mObjectId = Object_StaticRectangle;
	this->mImageData.SetImage(_image);
	this->mPhysicsBody = *(new PhysicsBody(_world, _pos, 0.0f, b2Shape::e_polygon, false));
	this->mPhysicsBody.SetPolygonFixtureDef(*(new b2Vec2(1.0f, 0.25f)), 90.0f, 0.0f, 1.0f, 0.0f);
}

StaticRectangle::StaticRectangle(b2World* _world, b2Vec2 _pos, b2Vec2 _size, float32 _angle, Assets::Image* _image) {
	this->mObjectId = Object_StaticRectangle;
	this->mImageData.SetImage(_image);
	this->mPhysicsBody = *(new PhysicsBody(_world, _pos, 0.0f, b2Shape::e_polygon, false));
	this->mPhysicsBody.SetPolygonFixtureDef(_size, _angle, 0.0f, 1.0f, 0.0f);
}

void StaticRectangle::Update() {

}
