#pragma once
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <vector>
#include "Assets.h"
#include "GameObject.h"
#include "Timer.h"
#include "Box2D\Box2D.h"

// Class forward decs
class Scene;
class TitleScreen;
class SceneManager;

//// Scene name enum
enum SceneName {
	Scene_TitleScreen,	// Title Screen
	Scene_Level1
};

//// Scene class
class Scene {
protected:
	SceneName		mSceneName; // Current scene name (pulled from enum)
	bool			mActive;	// Scene is active or inactive
	SceneManager*	mManager;	// Parent scene manager pointer
	Assets*			mAssets;	// Scene assets pointer
	std::vector<GameObject*> mGameObjects;

	// World physics
	b2Vec2 gravity;
	b2World* world;
	// Physics timestep
	float32 boxTimeStep = 1.0f / 600.0f;
	// Physics iterations
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

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
	void AddRect(float32 _x, float32 _y, float32 _w, float32 _h, float32 _angle) {
		this->mGameObjects.push_back(new StaticRectangle(
			this->world,
			*(new b2Vec2(_x, _y)),
			*(new b2Vec2(_w, _h)),
			_angle,
			&this->mAssets->images.b100x25));
	}

	// Scene virtual funcs
	virtual void LoadAssets() = 0;
	virtual void LoadGameObjects() = 0;
	virtual void SceneStart() = 0;
	virtual void HandleEvent(SDL_Event* Event) = 0;
	virtual void Update(Uint32 timeStep) = 0;
	virtual void Render() = 0;
};

//// Title screen scene class
class TitleScreen : public Scene {
protected:
	bool StartLevel1;
public:
	// Scene ctor
	TitleScreen();

	// Scene funcs
	void LoadAssets();
	void LoadGameObjects();
	void SceneStart();
	void HandleEvent(SDL_Event* Event);
	void Update(Uint32 timeStep);
	void Render();
};

//// Level 1 scene class
class Level1 : public Scene {
protected:
	bool ExitToMainMenu;
	Snail* Player;
	
public:
	// Scene ctor
	Level1();

	// Scene funcs
	void LoadAssets();
	void LoadGameObjects();
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
