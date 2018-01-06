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
	this->mAssets->images.b25x25 = { Assets::Instance()->GetTexture("25x25.png"), Graphics::CreateRect(25, 25, 0, 0) };
	this->mAssets->images.b100x25 = { Assets::Instance()->GetTexture("100x25.png"), Graphics::CreateRect(100, 25, 0, 0) };
}

void TitleScreen::SceneStart() {
	
}

void TitleScreen::HandleEvent(SDL_Event * Event) {
	switch (Event->type) {
	case SDL_KEYDOWN:
		if (Event->key.keysym.sym == SDLK_ESCAPE) this->mManager->quitGame = true;

		if (Event->key.keysym.sym == SDLK_r && Event->key.repeat == 0) SceneStart();

		break;

	case SDL_KEYUP:

		break;
	
	default:
		break;
	}
}

void TitleScreen::Update(Uint32 timeStep) {

}

void TitleScreen::Render() {
	// Render graphics to buffer
	// If I find any game logic in here, I'll slap myself silly
	this->mManager->GetGraphics()->DrawTexture(this->mAssets->images.SnailKnight.texture, this->mAssets->images.SnailKnight.rect);
}
