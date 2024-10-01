#ifndef APP_APP_H_
#define APP_APP_H_

#include "Screen.h"
#include <stdint.h>
#include <vector>
#include <memory>
#include "GameScene.h"
#include "GameController.h"

struct SDL_Window;

/**

@class App
@brief Definicja klasy dla glownej aplikacji.
Klasa App jest odpowiedzialna za inicjowanie, uruchamianie i zarzadzanie scenami gry. Sledzi rowniez szerokosc i wysokosc ekranu oraz InputController.
@var mScreen
Ekran.
@var mnoptrWindow
Okno aplikacji.
@var mSceneStack
Stos scen.
@var mInputController
InputController dla aplikacji
*/
class App
{
public:
	/**
	* @brief Pobiera pojedyczne wystapienie klasy App.
	* @return Instancja.
	*/
	static App& Singleton();

	/**
	* @brief Inicjuje aplikacje z okresloną szerokoscia, wysokoscią i powiekszeniem.
	* @param width Szerokosc.
	* @param height Wysokosc.
	* @param mag Powiekszenie.
	* @return Prawda, jesli inicjalizacja zakonczyla się pomyslnie, w przeciwnym razie falsz.
	*/
	bool Init(uint32_t width, uint32_t height, uint32_t mag);

	/**
	* @brief Uruchamia aplikacje.
	*/
	void Run();

	/**
	* @brief Pobiera szerokosc ekranu.
	* @return Szerokosc ekranu.
	*/
	inline uint32_t Width() const {return mScreen.Width();}

	/**
	* @brief Pobiera wysokosc ekranu
	* @return Wysokosc ekranu.
	*/
	inline uint32_t Height() const {return mScreen.Height();}

	/**
	* @brief Umieszczenie sceny na stosie.
	* @param scene Scena.
	*/
	void PushScene(std::unique_ptr<GameScene> scene);

	/**
	* @brief Pobiera najwyzsza scenę ze stosu.
	* @return Ostatnia scena.
	*/
	GameScene* TopScene();

private:
	Screen mScreen; ///< Ekran.
	SDL_Window * mnoptrWindow; ///< Okno.
	std::vector<std::unique_ptr<GameScene>> mSceneStack; ///< Stos scen.
	GameController mInputController; ///< InputController dla aplikacji.
};


#endif /* APP_APP_H_ */
