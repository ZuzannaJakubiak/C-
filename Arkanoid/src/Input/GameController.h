#ifndef INPUT_GAMECONTROLLER_H_
#define INPUT_GAMECONTROLLER_H_

#include <vector>
#include <functional>
#include <stdint.h>

/**
@typedef InputKey
@brief Alias ​​dla typu używanego do reprezentowania kluczy wejsciowych
*/
using InputKey = uint8_t;

/**
@typedef InputState
@brief Alias ​​typu uzywanego do reprezentowania stanu klucza wejsciowego
*/
using InputState = uint8_t;

/**
@typedef InputAction
@brief Alias ​​typu funkcji uzywanej do obslugi danych wejsciowych.
*/
using InputAction = std::function<void(uint32_t dt, InputState)>;

/**
@struct ButtonAction
@brief Struktura reprezentujaca klucz i akcje powiazane z przyciskiem.
*/
struct ButtonAction
{
InputKey key; /** < Klucz. */
InputAction action; /** < Akcja. */
};

/**
@class GameController
@brief Klasa GameController obsluguje dane wejsciowe uzytkownika
*/
class GameController
{
public:

	/**
	@brief Konstruktor
	*/
	GameController();

	/**
	@brief Metoda, ktora pobiera akcje skojarzona z danym kluczem
	@param key Klucz.
	@return Akcja skojarzona z danym kluczem
	*/
	InputAction GetActionForKey(InputKey key);

	/**
	@brief Metoda, ktora kojarzy dana akcje z danym kluczem.
	@param buttonAction Klucz i akcja do kojarzenia.
	*/
	void AddInputActionForKey(const ButtonAction& buttonAction);

	/**
	* @brief Metoda, ktora usuwa wszystkie powiazania klawisz-akcja z GameController.
	*/
	//void ClearAll();

	/**
	 * @brief Metoda, ktora inicjuje GameController z wykonaniem jakiejs akcji kiedy uzytkownik zamknie gre.
	 * @param quitAction Akcja ktora nastepuje po zamknieciu.
	 */
	void Init(InputAction quitAction);

	/**
	 * @brief Metoda, ktore aktualizuje GameController, obslugując dane wejsciowe i wywolując odpowiednie akcje
	 * @param dt Czas w milisekundach od ostatniej aktualizacji.
	 */
	void Update(uint32_t dt);

	/**
	 * @brief Metoda ktora ustawia bieżący GameController na dany kontroler
	 * @param controller GameController do usatwienia jako aktualny.
	 */
	void SetGameController(GameController* controller);

	/**
	 * @brief Metoda ktora sprawdza szy przycisk jest wcisniety
	 * @param state Stan wejscia
	 * @return Prawda jezeli jest wcisniety, w innym przypadku falsz
	 */
	static bool IsPressed(InputState state);

	/**
	 * @brief Zwraca klucz skojarzony z klawiszem akcji
	 * @return Klucz
	 */
	static InputKey ActionKey();

	/**
	 * @brief Zwraca klucz powiazany z lewym klawiszem
	 * @return Klucz powiazany z lewym klawiszem
	 */
	static InputKey LeftKey();

	/**
	* @brief Zwraca klucz powiazany z prawym klawiszem
	* @return Klucz powiazany z prawym klawiszem
	*/
	static InputKey RightKey();

	static InputKey RandomKey();

	void ClearAll();

private:
	std::vector<ButtonAction> mButtonActions; /**< Wektor skojarzen klawisz-akcja. */
	InputAction mQuit; /**< Akcja, ktora ma zostac podjeta, gdy uzytkownik wyjdzie z gry. */
	GameController* mnoptrCurrentController; /**< Wskaznik do biezącego GameController. */
};




#endif /* INPUT_GAMECONTROLLER_H_ */
