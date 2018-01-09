#include "Assets.h"
#include "Graphics.h"
#include "Scenes\Scene.h"
#include "SceneManager.h"

TitleScreen::TitleScreen() {
	// Set current scene name
	this->SetSceneName(Scene_TitleScreen);
}

void TitleScreen::LoadAssets() {
	// Load images into Assets
	this->mAssets->images.SnailKnight = { Assets::Instance()->GetTexture("snailknight_proto.png"), Graphics::CreateRect(35, 26, 10, 10) };
	this->mAssets->images.b25x25 = { Assets::Instance()->GetTexture("b25x25.png"), Graphics::CreateRect(25, 25, 0, 0) };
	this->mAssets->images.b100x25 = { Assets::Instance()->GetTexture("b100x25.png"), Graphics::CreateRect(100, 25, 0, 0) };
}

void TitleScreen::LoadGameObjects() {

}

void TitleScreen::SceneStart() {
	this->LoadAssets();
	this->StartLevel1 = false;
}

void TitleScreen::HandleEvent(SDL_Event * Event) {
	switch (Event->type) {
	case SDL_KEYDOWN:
		if (Event->key.keysym.sym == SDLK_ESCAPE) this->mManager->quitGame = true;

		if (Event->key.keysym.sym == SDLK_SPACE) this->StartLevel1 = true;

		if (Event->key.keysym.sym == SDLK_r && Event->key.repeat == 0) this->SceneStart();

		break;

	case SDL_KEYUP:

		break;
	
	default:
		break;
	}
}

void TitleScreen::Update(Uint32 timeStep) {
	if (this->StartLevel1)
		this->mManager->StartScene(Scene_Level1);
}

void TitleScreen::Render() {
	// Render graphics to buffer
	// If I find any game logic in here, I'll slap myself silly
	this->mManager->GetGraphics()->DrawTexture(this->mAssets->images.SnailKnight.texture, this->mAssets->images.SnailKnight.rect);
}
