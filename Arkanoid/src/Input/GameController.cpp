#include "GameController.h"
#include <SDL2/SDL.h>

GameController::GameController():mQuit(nullptr), mnoptrCurrentController(nullptr)
{
//konstruktor
}

InputAction GameController::GetActionForKey(InputKey key)
{
	for(const auto& buttonAction: mButtonActions) //dla kazdego ButtonAction
	{
		if(key == buttonAction.key) //jezeli key = ba.key
		{
			return buttonAction.action; //zwroc akcje
		}
	}

	return [](uint32_t, InputState){}; // zwraca funkcje ktora przyjmuje 2 argumenty
}

void GameController::AddInputActionForKey(const ButtonAction& buttonAction)
{
	mButtonActions.push_back(buttonAction); // Dodaje InputAction dla klucza do ButtonActions
}
void GameController::ClearAll()
{
	mButtonActions.clear();
}

bool GameController::IsPressed(InputState state)
{
	return state == SDL_PRESSED; //sprawdza stan
}

InputKey GameController::ActionKey()
{
	return static_cast<InputKey>(SDLK_a); //key dla actionKey
}


InputKey GameController::LeftKey()
{
	return static_cast<InputKey>(SDLK_LEFT); //lewy
}

InputKey GameController::RightKey()
{
	return static_cast<InputKey>(SDLK_RIGHT); //prawy
}

InputKey GameController::RandomKey()
{
	return static_cast<InputKey>(SDLK_r); //prawy
}

void GameController::Init(InputAction quitAction)
{
	mQuit = quitAction; //akcja zakonczenia do mQuit
}

void GameController::Update(uint32_t dt)
{
	SDL_Event sdlEvent;

	while(SDL_PollEvent(&sdlEvent))
	{
		switch(sdlEvent.type)
		{
		case SDL_QUIT:
		{
			//jezelu uzytkownik chce zamknac, to quitaction
			mQuit(dt, SDL_PRESSED);
		}
		break;
		case SDL_KEYUP:
		case SDL_KEYDOWN:

			if(mnoptrCurrentController)
			{
				//jezelu jest aktualny kontroler to get action i wywyolaj ja
				InputAction action = mnoptrCurrentController->GetActionForKey(sdlEvent.key.keysym.sym);

				action(dt, static_cast<InputState>(sdlEvent.key.state));
			}
			break;
		}
	}
}

void GameController::SetGameController(GameController* controller)
{
	mnoptrCurrentController = controller;//Ta funkcja ustawia biezący kontroler gier na przekazany kontroler
}
