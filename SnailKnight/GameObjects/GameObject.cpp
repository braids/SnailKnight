#include "GameObject.h"

GameObject::GameObject() {
	
}

GameObject::~GameObject() {

}

void GameObject::SetDrawPos(Uint32 _x, Uint32 _y) {
	this->mImageData.GetDrawRect()->x = _x;
	this->mImageData.GetDrawRect()->y = _y;
	this->mImageData.GetDrawRect()->w = (int)(this->GetBody()->GetWidth() * 2.0f * M2P_DRAWSCALE);
	this->mImageData.GetDrawRect()->h = (int)(this->GetBody()->GetHeight() * 2.0f * M2P_DRAWSCALE);
	this->mImageData.SetDrawAngle((double)(this->GetBody()->GetAngle() * -180.0f) / M_PI);
}

void GameObject::UpdateDrawRect(Uint32 _offsetX, Uint32 _offsetY) {
	this->mImageData.GetDrawRect()->x = (int)((this->GetBody()->GetWorldCenter().x - this->GetBody()->GetWidth()) * M2P_DRAWSCALE) - _offsetX;
	this->mImageData.GetDrawRect()->y = (int)((this->GetBody()->GetWorldCenter().y + this->GetBody()->GetHeight()) * -M2P_DRAWSCALE) - _offsetY;
	this->mImageData.GetDrawRect()->w = (int)(this->GetBody()->GetWidth() * 2.0f * M2P_DRAWSCALE);
	this->mImageData.GetDrawRect()->h = (int)(this->GetBody()->GetHeight() * 2.0f * M2P_DRAWSCALE);
	this->mImageData.SetDrawAngle((double)(this->GetBody()->GetAngle() * -180.0f) / M_PI);
}