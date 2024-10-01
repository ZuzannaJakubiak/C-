#ifndef GRAPHICS_COLOR_H_
#define GRAPHICS_COLOR_H_

#include <stdint.h>

struct SDL_PixelFormat;

/**
@class Color
@brief Klasa reprezentujaca kolor w formacie RGBA.
*/
class Color
{
uint32_t mColor; /**< Kolor przechowywany jako 32-bit integer. */
public:

/**
@brief Format koloru pixeli.
*/
static const SDL_PixelFormat* mFormat;

/**
@brief Inicjalizacja formatu
@param format wskaznik do SDL_PixelFormat
*/
static void InitColorFormat(const SDL_PixelFormat* format);

/**
@brief Zwraca kolor czarny
@return Obiekt Color reprezentujacy kolor czarny
*/
static Color Black() {return Color(0, 0, 0, 255);}

/**
@brief Zwraca kolor bialy
@return Obiekt Color reprezentujacy kolor bialy
*/

static Color White() {return Color(255, 255, 255, 255);}

/**
@brief Zwraca kolor niebieski
@return Obiekt Color reprezentujacy kolor niebieski
*/
static Color Blue() {return Color(0, 0, 255, 255);}

/**
@brief Zwraca kolor czerwony
@return Obiekt Color reprezentujacy kolor czerwony
*/
static Color Red() {return Color(255, 0, 0, 255);}

/**
@brief Zwraca kolor zielony
@return Obiekt Color reprezentujacy kolor zielony
*/
static Color Green() {return Color(0, 255, 0, 255);}

/**
@brief Konstruktor.
*/
Color(): Color(0){}

/**
@brief Konstruktor klasy Color, ktory jako argument przyjmuje 32-bitowa wartosc koloru
@param color 32-bitowa wartosc koloru.
*/
Color(uint32_t color): mColor(color){}

/**
@brief Konstruktor klasy Color, ktory jako argument przyjmuje parametry czerwony, zielony, niebieski i alfa.
@param r Wartosc red (0-255).
@param g Wartosc green (0-255).
@param b Wartosc blue (0-255).
@param a Wartosc alfa (0-255).
*/
Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
@brief Funkcja sprawdzajaca kolor w postaci 32-bitowej liczby calkowitej.
@return Kolor w postaci 32-bitowej liczby calkowitej.
*/
inline uint32_t GetPixelColor() const {return mColor;}

Color(uint8_t r, uint8_t g, uint8_t b);
};



#endif /* GRAPHICS_COLOR_H_ */
