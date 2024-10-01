#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include "BreakOut.h"
#include "GameController.h"
#include <memory>


/**
@class GameScene
@brief Klasa reprezentujaca scene gry.
*/
class GameScene{

public:

/**
@brief Konstruktor
@param optrGame Unikalny wskaźnik do obiektu gry BreakOu
*/
GameScene(std::unique_ptr<BreakOut> optrGame);

/**
@brief Wirtualny destruktor klasy GameScene
*/
virtual ~GameScene() {}

/**
@brief Metoda inicjujaca GameScene
*/
virtual void Init();

/**
@brief Metoda aktualizujaca GameScene.
@param dt Czas w milisekundach od ostatniej aktualizacji
*/
virtual void Update(uint32_t dt);

/**
@brief Metoda, ktora rysuje GameScene na podanym ekranie.
@param screen Screen na ktorym narysowac GameScene.
*/
virtual void Draw(Screen& screen);

/**
@brief Metoda pobierajaca GameController dla GameScene.
@return GameController dla GameScene.
*/
GameController* GetGameController() {return &mGameController;}

private:
std::unique_ptr<BreakOut> mGame; /**< Unikalny wskaźnik do obiektu gry BreakOut. */

protected:
GameController mGameController; /**< GameController dla GameScene. */
};


#endif /* SCENES_GAMESCENE_H_ */
