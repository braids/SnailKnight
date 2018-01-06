#include "Assets.h"
#include "Graphics.h"
#include "SceneManager.h"

TitleScreen::TitleScreen() {
	// Set current scene name
	this->SetSceneName(Scene_TitleScreen);
}

void TitleScreen::LoadAssets() {
	// Load images into Assets
	this->mAssets->images.SnailKnight = { Assets::Instance()->GetTexture("snailknight_proto.png"), Graphics::CreateRect(35, 26, 10, 10) };
}

void TitleScreen::SceneStart() {
	// Eventually things will go here
}

void TitleScreen::HandleEvent(SDL_Event * Event) {
	switch (Event->type) {
	case SDL_KEYDOWN:
		if(Event->key.keysym.sym == SDLK_ESCAPE) mManager->quitGame = true;
		break;

	case SDL_KEYUP:
		break;
	
	default:
		break;
	}
}

void TitleScreen::Update(Uint32 timeStep) {
	// Eventually things will go here
}

void TitleScreen::Render() {
	// Render graphics to buffer
	// If I find any game logic in here, I'll slap myself silly
	this->mManager->GetGraphics()->DrawTexture(this->mAssets->images.SnailKnight.texture, this->mAssets->images.SnailKnight.rect);
}
