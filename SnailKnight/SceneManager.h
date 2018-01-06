#pragma once
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <vector>
#include "Assets.h"
#include "Timer.h"

// Class forward decs
class Scene;
class TitleScreen;
class SceneManager;

//// Scene name enum
enum SceneName {
	Scene_TitleScreen	// Title Screen
};

//// Scene class
class Scene {
protected:
	SceneName		mSceneName; // Current scene name (pulled from enum)
	bool			mActive;	// Scene is active or inactive
	SceneManager*	mManager;	// Parent scene manager pointer
	Assets*			mAssets;	// Scene assets pointer
	
public:
	// Scene ctor/dtor
	Scene();
	~Scene();

	// Scene funcs
	void Init(SceneManager* manager);

	// Scene methods
	void SetActive(bool active) { this->mActive = active; }
	bool IsActive() const { return this->mActive; }
	void SetManager(SceneManager* manager) { this->mManager = manager; }
	void SetSceneName(SceneName name) { this->mSceneName = name; }

	// Scene virtual funcs
	virtual void LoadAssets() = 0;
	virtual void SceneStart() = 0;
	virtual void HandleEvent(SDL_Event* Event) = 0;
	virtual void Update(Uint32 timeStep) = 0;
	virtual void Render() = 0;
};

//// Title screen scene class
class TitleScreen : public Scene {
public:
	// Scene ctor
	TitleScreen();

	// Scene funcs
	void LoadAssets();
	void SceneStart();
	void HandleEvent(SDL_Event* Event);
	void Update(Uint32 timeStep);
	void Render();
};

//// Scene manager class
class SceneManager{
protected:
	// Timer Vars
	Uint32			currTick;
	Uint32			lastTick;
	Uint32			timeStep;

	Graphics*			mGraphics;	// Scene renderer pointer
	Scene*				mCurrent;	// Current active scene
	Scene*				mNext;		// Next active scene
	std::vector<Scene*>	sceneList;	// Vector of all scenes

public:
	bool quitGame;

	// Scene manager ctor/dtor
	SceneManager();
	~SceneManager();

	// Scene manager methods
	void AddScene(Scene* scene) { this->sceneList.push_back(scene); }
	Scene* GetScene() { return this->mCurrent; }
	Graphics* GetGraphics() { return this->mGraphics; }
	bool IsScene(SceneName scene) { return this->mCurrent == this->sceneList[scene]; }
	void Update() { this->mCurrent->Update(this->timeStep); }

	// Scene manager funcs
	bool Init();
	void Event(SDL_Event* Event);
	void Render();
	void StartScene(SceneName scene);
	void UpdateTicks();
};

#endif
