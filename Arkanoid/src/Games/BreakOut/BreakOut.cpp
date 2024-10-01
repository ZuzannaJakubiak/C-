/*
 * BreakOut.cpp
 *
 *  Created on: 4 sty 2023
 *      Author: Zuzanna Jakubiak
 */


#include "BreakOut.h"
#include "GameController.h"
#include "App.h"
#include <iostream>
#include "Circle.h"
#include<SDL2/SDL.h>
#include <string>

void BreakOut::Init(GameController& controller)
{
	controller.ClearAll();


	ResetGame(); //reset

	ButtonAction serveAction; //nowy buttonaction
	serveAction.key = GameController::ActionKey(); //l;ucz
	serveAction.action = [this](uint32_t dt, InputState state) //akcja
		{
			if(mGameState == IN_SERVE) //jezeli status jest w gotowosci
			{
				if(GameController::IsPressed(state)) //jezeli wcienity
				{
					mGameState = IN_PLAY; //stan w grze


					if(mPaddle.IsMovingLeft()) //jak w lewo
					{
						//ustaw predkosc pilki
						mBall.SetVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
					}
					else
					{
						//ustaw predkosc pilki
						mBall.SetVelocity(Vec2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
					}
				}
			}
			else if(mGameState == IN_GAME_OVER) //jak przegrana
			{
				if(GameController::IsPressed(state))
				{
					ResetGame();
				}
			}
		};

	controller.AddInputActionForKey(serveAction); //dodanie akcji do kontrolera


	ButtonAction leftKeyAction; //w lewo
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state)
		{
			if(mGameState == IN_PLAY || mGameState == IN_SERVE)
			{
				if(GameController::IsPressed(state))
				{
					mPaddle.SetMovementDirection(PaddleDirection::LEFT);
				}
				else
				{
					mPaddle.SetMovementDirection(PaddleDirection::NONE);
				}
			}

		};

	controller.AddInputActionForKey(leftKeyAction);

	ButtonAction rightKeyAction; // w prawo
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state)
		{
			if(mGameState == IN_PLAY || mGameState == IN_SERVE)
			{
				if(GameController::IsPressed(state))
				{
					mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
				}
				else
				{
					mPaddle.SetMovementDirection(PaddleDirection::NONE);
				}
			}
		};

	controller.AddInputActionForKey(rightKeyAction);

	ButtonAction randomKeyAction; // w prawo
	randomKeyAction.key = GameController::RandomKey();
	randomKeyAction.action = [this](uint32_t dt, InputState state)
		{
			if(mGameState == IN_PLAY || mGameState == IN_SERVE)
			{
				GetCurrentLevel().Delete();
			}
		};

	controller.AddInputActionForKey(randomKeyAction);
}

void BreakOut::Update(uint32_t dt) //aktualizacja
{
	if(mGameState == IN_SERVE) //w gotowasci
	{
		mPaddle.Update(dt, mBall);
		SetToServeState();
	}

	else if(mGameState == IN_PLAY)
	{

		mBall.Update(dt);
		mPaddle.Update(dt, mBall);

		BoundaryEdge edge;

		if(mPaddle.Bounce(mBall))
		{
			return;
		}

		if(mLevelBoundary.HasCollided(mBall, edge))
		{
			mBall.Bounce(edge);
			return;
		}

		GetCurrentLevel().Update(dt, mBall);

		if(IsBallPassedCutoffY())
		{
			ReduceLifeByOne();
			if(!IsGameOver())
			{
				SetToServeState();
			}
			else
			{
				mGameState = IN_GAME_OVER;
			}
		}
		else if(GetCurrentLevel().IsLevelComplete())
		{
			mCurrentLevel = (mCurrentLevel + 1) % mLevels.size();
			ResetGame(mCurrentLevel);
		}
	}
}


void BreakOut::Draw(Screen& screen)
{
	mBall.Draw(screen);
	mPaddle.Draw(screen);
	GetCurrentLevel().Draw(screen);

	screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());

	Circle lifeCircle = {Vec2D(7, App::Singleton().Height() - 10), 5};

	Line2D cutoff = {Vec2D(0, mYCutoff), Vec2D(App::Singleton().Width(), mYCutoff)};
	screen.Draw(cutoff, Color::White());
	for(int i = 0;i < mLives;++i)
	{
		screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
		lifeCircle.MoveBy(Vec2D(17, 0));
	}
}

const std::string& BreakOut::GetName() const
{
	static std::string name = "Break Out!";
	return name;
}

void BreakOut::ResetGame(size_t toLevel)
{
	const std::string basePath = SDL_GetBasePath();
	mLevels = BreakoutGameLevel::LoadLevelsFromFile(basePath + "Assets/BreakoutLevels.txt");

	mCurrentLevel = 1;
	mYCutoff = App::Singleton().Height() - 2*Paddle::PADDLE_HEIGHT;
	mLives = NUM_LIVES;

	AARectangle paddleRect = {Vec2D(App::Singleton().Width()/2 - Paddle::PADDLE_WIDTH/2, App::Singleton().Height() - 3*Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
	AARectangle levelBoundary = {Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()};

	mLevelBoundary = {levelBoundary};

	mPaddle.Init(paddleRect, levelBoundary);
	mBall.MoveTo(Vec2D(App::Singleton().Width()/2, App::Singleton().Height() * 0.75f));
	SetToServeState();
}

void BreakOut::SetToServeState()
{
	mGameState = IN_SERVE;
	mBall.Stop();

	mBall.MoveTo(Vec2D(mPaddle.GetAARectangle().GetCenterPoint().GetX(), mPaddle.GetAARectangle().GetTopLeftPoint().GetY() -  mBall.GetRadius()-1));
}

bool BreakOut::IsBallPassedCutoffY() const
{
	return mBall.GetPosition().GetY() > mYCutoff;
}

void BreakOut::ReduceLifeByOne()
{
	if(mLives >=0)
	{
		--mLives;
	}
}



