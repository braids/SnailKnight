#include "GameObject.h"

GameObject::GameObject() {
	
}

GameObject::~GameObject() {

}

void GameObject::UpdateDrawRect() {
	this->mImageData.GetDrawRect()->x = (int)((this->GetBody()->GetWorldCenter().x - this->GetBody()->GetWidth()) * M2P_DRAWSCALE) + 100;
	this->mImageData.GetDrawRect()->y = (int)((this->GetBody()->GetWorldCenter().y + this->GetBody()->GetHeight()) * -M2P_DRAWSCALE) + 600;
	this->mImageData.GetDrawRect()->w = (int)(this->GetBody()->GetWidth() * 2.0f * M2P_DRAWSCALE);
	this->mImageData.GetDrawRect()->h = (int)(this->GetBody()->GetHeight() * 2.0f * M2P_DRAWSCALE);
	this->mImageData.SetDrawAngle((double)(this->GetBody()->GetAngle() * -180.0f) / M_PI);
}