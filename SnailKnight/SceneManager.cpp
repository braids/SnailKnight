#include "Assets.h"
#include "Graphics.h"
#include "SceneManager.h"

SceneManager::SceneManager() {
	// Set SDL Graphics NULL on creation
	this->mGraphics = NULL;

	// We're not quitting yet
	this->quitGame = false;

	// Set timer values
	currTick = 0;
	lastTick = 0;
	timeStep = 0;
}

SceneManager::~SceneManager() {
	// Release/free SDL Graphics
	Graphics::Release();
	this->mGraphics = NULL;

	// Quit SDL_Mixer
	Mix_Quit();
}

bool SceneManager::Init() {
	printf("Init\n");

	// Initialize SDL Graphics
	this->mGraphics = Graphics::Instance();

	// Initialize sound
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(16);

	// Add scenes here
	this->AddScene(new TitleScreen());
	this->AddScene(new Level1());

	// Initialize scenes
	for (int i = 0; i < (int) this->sceneList.size(); i++)
		this->sceneList[i]->Init(this);

	// Set initial scene
	this->StartScene(Scene_TitleScreen);

	// Init succeeded
	return true;
}

void SceneManager::Event(SDL_Event* Event) {
	if (Event->type == SDL_QUIT) 
		this->quitGame = true;
	else
		this->GetScene()->HandleEvent(Event);
}

void SceneManager::Render() {
	// Clear draw buffer
	this->mGraphics->ClearBackBuffer();

	// Run scene rendering func
	this->mCurrent->Render();

	// Render buffer to scene
	this->mGraphics->Render();
}

void SceneManager::StartScene(SceneName scene) {
	// Get next scene
	this->mNext = this->sceneList[scene];
	
	// Run scene start func
	this->mNext->SceneStart();
	
	// Set next scene as current
	this->mCurrent = this->mNext;
	
	// Clear next scene
	this->mNext = nullptr;

	// Run scene update
	this->Update();
}

void SceneManager::UpdateTicks() {
	// Update timeStep by # of ticks from last cycle
	this->lastTick = this->currTick;
	this->currTick = SDL_GetTicks();
	this->timeStep = this->currTick - this->lastTick;
}
