#pragma once
#ifndef _ASSETS_H_
#define _ASSETS_H_

#include <map>
#include <SDL2/SDL_mixer.h>
#include "Graphics.h"

typedef std::map<std::string, SDL_Texture*> TextureList;

class Assets {
private:
	static Assets* sInstance;
	TextureList	mTextures;
	Assets();
	~Assets();
public:
	static Assets* Instance();
	static void Release();
	SDL_Texture* GetTexture(std::string name);
	Mix_Chunk* GetSound(std::string name);
	Mix_Music* GetMusic(std::string name);

	struct Image {
		SDL_Texture* texture;
		SDL_Rect* rect;
	};

	struct Images {
		Image SnailKnight;
		Image SnailKnightShell;
		Image b25x25;
		Image b100x25;
		Image c25x25;
		// Placeholder Spritesheet images
		Image SpriteSheet1D[1];
		Image SpriteSheet2D[1][1];
	} images;

	struct Sounds {
		Mix_Chunk* ExampleSound;
	} sounds;

	struct Music {
		Mix_Music* ExampleMusic;
	} music;
};

#endif
