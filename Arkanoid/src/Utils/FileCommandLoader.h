/*
 * FileCommandLoader.h
 *
 *  Created on: 4 sty 2023
 *      Author: Zuzanna Jakubiak
 */

#ifndef UTILS_FILECOMMANDLOADER_H_
#define UTILS_FILECOMMANDLOADER_H_

#include <functional>
#include <vector>
#include <string>
#include <stdint.h>

class Color;

/**
* @brief Enumeracja typow komend w pliku
*/
enum CommandType
{
    COMMAND_ONE_LINE = 0, /**< Komenda jednowierszowa */
    COMMAND_MULTI_LINE /**< Komenda wielowierszowa */
};

/**
* @brief Struktura do przekazywania parametrow do analizy
*/
struct ParseFuncParams
{
    std::string line; /**< Wiersz komendy */
    size_t dilimitPos; /**< Pozycja separatora w wierszu */
    uint32_t lineNum; /**< Liczba wierszy w komendzie */
};

/**
* @brief Typ funkcji analizy
*/
using ParseFunc =  std::function<void(const ParseFuncParams& params)>;

/**
* @brief Struktura do przechowywania informacji o komendzie
*/
struct Command
{
    CommandType commandType = COMMAND_ONE_LINE; /**< Typ komendy */
    std::string command = ""; /**< Ciag znakow komendy */
    ParseFunc parseFunc = nullptr; /**< Funkcja analizy dla komendy */
};

/**
* @class FileCommandLoader
* @brief Klasa do ładowania komend z pliku, gdzie kazda komenda jest reprezentowana przez ciag znakow i funckje analizy ktora jest wywolywana kiedy komenda jest napotkana w pliku
* @var FileCommandLoader::mCommands
* Wektor komend
*/
class FileCommandLoader
{
public:
    /**
    * @brief Metoda dodajaca komende
    * @param command Komenda do dodania
    */
    void AddCommand(const Command& command);

    /**
    * @brief Metoda ladujaca plik
    * @param filePath Sciezka do pliku
    * @return Prawda jezeli plik zaladowany poprawnie, w innym przypadku falsz
    */
    bool LoadFile(const std::string& filePath);

    /**
    * @brief Metoda do czytania koloru
    * @param params Parametry funkcji analizy
    * @return Kolor
    */
    static Color ReadColor(const ParseFuncParams& params);

    /**
    * @brief Metoda do czytania int
    * @param params Parametry funkcji analizy
    * @return Integer (int)
    */
    static int ReadInt( const ParseFuncParams& params);

    /**
    * @brief Metoda do czytania znakow
    * @param params Parametry funkcji analizy
    * @return Znak (char)
    */
    static char ReadChar(const ParseFuncParams& params);

private:
    /**
    * @var FileCommandLoader::mCommands
    * Wektor komend
    */
    std::vector<Command> mCommands;
};





#endif /* UTILS_FILECOMMANDLOADER_H_ */
