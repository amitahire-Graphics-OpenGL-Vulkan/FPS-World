#pragma once

class Player;
class Camera;
class Crosshair;
class Light;
class HealthBar;
class Renderer;
class WeaponModel;
class GPUProgram;
class Skybox;

#include "IGeometry.h"

class Application
{
	private:

		int screenWidth;
		int screenHeight;
		const char * const appName;

		// objects
		Player* player;
		Camera* gWorld;
		Crosshair* cross;
		Light* gLight;
		HealthBar* health;
		Renderer* m_renderer;
		WeaponModel* weapon;
		Skybox* skybox;

		Application();
		Application(const Application&);
		void operator=(const Application&);
		~Application();

		void Destroy();

		void initializeScene();

		void renderScene();

		//fps stuff
		unsigned frameCount;
		unsigned lastFrameEnd;
		unsigned lastTitleUpdateTime;
		unsigned lastTitleUpdateFrameCount;

		//* Function that calculates and displays
		//* frame time and fps on the window frame
		void displayFrameCounter();

		void handleEvents(float time, Renderer* renderer, Camera* camera);

	public:

		static Application& Instance();

		void run();
};