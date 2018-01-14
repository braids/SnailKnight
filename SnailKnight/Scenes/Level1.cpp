#include "Assets.h"
#include "Camera.h"
#include "GameObject.h"
#include "Graphics.h"
#include "LevelBuilder.h"
#include "Scenes\Scene.h"
#include "SceneManager.h"

Level1::Level1() {
	// Set current scene name
	this->SetSceneName(Scene_Level1);
	
}

void Level1::LoadAssets() {
	// Load images into Assets
	this->mAssets->images.SnailKnight = { Assets::Instance()->GetTexture("snailknight_proto.png"), Graphics::CreateRect(35, 26, 0, 0) };
	this->mAssets->images.SnailKnightShell = { Assets::Instance()->GetTexture("snailknight_inshell.png"), Graphics::CreateRect(28, 28, 0, 0) };
	this->mAssets->images.b25x25 = { Assets::Instance()->GetTexture("b25x25.png"), Graphics::CreateRect(25, 25, 0, 0) };
	this->mAssets->images.b100x25 = { Assets::Instance()->GetTexture("b100x25.png"), Graphics::CreateRect(100, 25, 0, 0) };
}

void Level1::LoadGameObjects() {
	this->mGameObjects.clear();
	this->mGameObjects.push_back(new Snail(this->world, *(new b2Vec2(3.0f, 7.0f)), &this->mAssets->images.SnailKnight));
	this->Player = dynamic_cast<Snail*>(this->mGameObjects[0]);

	// Static collision rects
	this->AddRect(-0.55f, 3.75f, 3.0f, 0.5f, (float32)M_PI / -2.0f);
	this->AddRect(0.4f, 1.0f, 3.0f, 0.5f, (float32)M_PI / -3.5f);
	this->AddRect(1.5f, 0.0f, 1.0f, 0.5f, -0.3f);
	this->AddRect(3.0f, 0.0f, 3.0f, 0.5f, 0.0f);
	this->AddRect(3.0f, 3.0f, 4.0f, 0.1f, 0.0f);
	this->AddRect(5.5f, 0.5f, 3.0f, 0.5f, 0.45f);
	this->AddRect(7.0f, 2.0f, 3.0f, 0.5f, (float32)M_PI / 3.0f);
	this->AddRect(7.75f, 4.75f, 3.0f, 0.5f, (float32)M_PI / 2.0f);
	
	std::vector<StaticRectangle*> builderStatics = *(this->mLevelBuilder->GenerateStaticCurve(3.5f, 5.0f, 0.1f, 0.0f, (float32) M_PI, 40, 3.0f, 3.0f));
	std::vector<StaticRectangle*>::iterator iter = builderStatics.begin();
	for (; iter != builderStatics.end(); iter++)
		this->mGameObjects.push_back(*iter);
		
}

void Level1::SceneStart() {
	this->LoadAssets();

	this->ExitToMainMenu = false;
	this->gravity.Set(0.0f, -4.0f);
	this->world = new b2World(this->gravity);

	this->mLevelBuilder = new LevelBuilder(this->world);
	this->LoadGameObjects();
	this->mCamera.SetTargetGameObject(this->Player);
}

void Level1::HandleEvent(SDL_Event * Event) {
	switch (Event->type) {
	case SDL_KEYDOWN:
		if (Event->key.keysym.sym == SDLK_ESCAPE) this->ExitToMainMenu = true;
		if (Event->key.keysym.sym == SDLK_r && Event->key.repeat == 0) this->SceneStart();
		if (Event->key.keysym.sym == SDLK_LEFT)	this->Player->MoveLeft = true;
		if (Event->key.keysym.sym == SDLK_RIGHT) this->Player->MoveRight = true;
		if (Event->key.keysym.sym == SDLK_DOWN) this->Player->InShell = true;
		if (Event->key.keysym.sym == SDLK_SPACE && Event->key.repeat == 0) this->Player->Jump = true;
		if (Event->key.keysym.sym == SDLK_LSHIFT) this->Player->Cling = true;
		break;

	case SDL_KEYUP:
		if (Event->key.keysym.sym == SDLK_LEFT) this->Player->MoveLeft = false;
		if (Event->key.keysym.sym == SDLK_RIGHT) this->Player->MoveRight = false;
		if (Event->key.keysym.sym == SDLK_DOWN) this->Player->InShell = false;
		if (Event->key.keysym.sym == SDLK_SPACE) this->Player->Jump = false;
		if (Event->key.keysym.sym == SDLK_LSHIFT) this->Player->Cling = false;
		break;

	default:
		break;
	}
}

void Level1::Update(Uint32 timeStep) {
	// Return to title screen if quitting
	if (this->ExitToMainMenu)
		this->mManager->StartScene(Scene_TitleScreen);
	
	// Update player
	this->Player->Update();
	// Update world physics
	this->world->Step(this->boxTimeStep * (float32)timeStep, this->velocityIterations, this->positionIterations);
	this->world->ClearForces();

	// Update camera and camera target
	this->mCamera.target->UpdateDrawRect(this->mCamera.CameraOffsetX(), this->mCamera.CameraOffsetY());
	this->mCamera.CenterOnTarget();
	// Update draw positions of game objects
	for (int i = 0; i < (int) this->mGameObjects.size(); i++) {
		// Skip camera target
		if (this->mGameObjects[i] == this->mCamera.target) 
			continue;

		this->mGameObjects[i]->UpdateDrawRect(this->mCamera.CameraOffsetX(), this->mCamera.CameraOffsetY());
	}
	// Set camera target to center
	this->mCamera.target->SetDrawPos(Graphics::GAMEAREA_WIDTH / 2, Graphics::GAMEAREA_HEIGHT / 2);
}

void Level1::Render() {
	// Render graphics to buffer
	// If I find any game logic in here, I'll slap myself silly
	if (this->Player->ContactFloor())
			this->mManager->GetGraphics()->DrawTexture(this->mAssets->images.b25x25.texture, this->mAssets->images.b25x25.rect);
	
	for (int i = 0; i < (int) this->mGameObjects.size(); i++) {
		this->mManager->GetGraphics()->DrawTextureAtLocation(
			this->mGameObjects[i]->GetImageData()->GetImage()->texture, 
			this->mGameObjects[i]->GetImageData()->GetImage()->rect,
			this->mGameObjects[i]->GetImageData()->GetDrawRect(),
			this->mGameObjects[i]->GetImageData()->GetDrawAngle()
			);			
	}
}
