#include "SnailKnight.h"

SnailKnight::SnailKnight() {
	// Set game running/playing flags
	Running = true;

	// Set timer values
	currTick = 0;
	lastTick = 0;
	timeStep = 0;
}

int SnailKnight::OnExecute() {
	// Initialize scenes and SDL Graphics/Audio
	if (scene.Init() == false) {
		return -1;
	}

	SDL_Event Event;

	// Main loop
	while (Running) {
		// Update timeStep by # of ticks from last cycle
		lastTick = currTick;
		currTick = SDL_GetTicks();
		timeStep = currTick - lastTick;

		// Check events
		while (SDL_PollEvent(&Event)) {
			scene.Event(&Event);
		}
		// Perform actions and updates
		scene.Update();

		// Render scene
		scene.Render();

		// Check if scene manager has given the go-ahead to quit game
		if (scene.quitGame) Running = false;
	}

	return 0;
}

int main(int argc, char* argv[]) {
	SnailKnight sn;

	return sn.OnExecute();
}
