#include "GameScene.h"


GameScene::GameScene(std::unique_ptr<BreakOut> optrGame):mGame(std::move(optrGame))
{
//konstruktor
}

void GameScene::Init()
{
	mGame->Init(mGameController); //referencja do Game Controller
}

void GameScene::Update(uint32_t dt)
{
	mGame->Update(dt); //Aktualizacja po czasie
}

void GameScene::Draw(Screen& screen)
{
	mGame->Draw(screen); //Rusuj, referencja do screen
}

