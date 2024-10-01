/*
 * App.cpp
 *
 *  Created on: 2 sty 2023
 *      Author: Zuzanna Jakubiak
 */

#include"App.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "GameScene.h"
#include "BreakOut.h"

App& App::Singleton()
{
	static App theApp; //instancja klasy app
	return theApp; //referencja do tego
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
	mnoptrWindow = mScreen.Init(width, height, mag); //tworzenie okna

	std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>(); //breakout game object

	std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));//scena breakount

	PushScene(std::move(breakoutScene)); //nowa scena na stosie

	return mnoptrWindow != nullptr;
}

void App::Run()
{
	if(mnoptrWindow)
	{

		bool running = true;

		uint32_t lastTick = SDL_GetTicks();
		uint32_t currentTick = lastTick;

		uint32_t dt = 10; // dt = 10ms, update co 10ms
		uint32_t accumulator = 0;

		mInputController.Init([&running](uint32_t dt, InputState state){
			running = false;
		});


		while(running)
		{
			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick;

			if(frameTime > 300)
			{
				frameTime = 300;
			}


			lastTick = currentTick;

			accumulator += frameTime;

			//Input
			mInputController.Update(dt);

			GameScene* topScene = App::TopScene();

			if(topScene)
			{
			//Update
				while (accumulator >= dt)
				{
					//update current scene by dt
					topScene->Update(dt);
					accumulator -= dt;
				}

			//Render
			topScene->Draw(mScreen);

			}

			mScreen.SwapScreens();
		}
	}
}

void App::PushScene(std::unique_ptr<GameScene> scene)
{
	scene->Init();
	mInputController.SetGameController(scene->GetGameController());
	mSceneStack.emplace_back(std::move(scene));
	SDL_SetWindowTitle(mnoptrWindow, "Breakout");
}

/*
void App::PopScene()
{
	if(mSceneStack.size() > 1)
	{
		mSceneStack.pop_back();
	}

	if(TopScene())
	{
		mInputController.SetGameController(TopScene()->GetGameController());
		SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}
}
*/
GameScene* App::TopScene()
{
	return mSceneStack.back().get();
}

