#include "FileCommandLoader.h"
#include <fstream>
#include <iostream>
#include "Color.h"


void FileCommandLoader::AddCommand(const Command& command) //Dodanie obiektu Command do wektoru obiektow
{
	mCommands.push_back(command);
}

bool FileCommandLoader::LoadFile(const std::string& filePath) //otwiera plik, czyta kazda linie, wywoluje ospowiedznie funkcje analizy dla kazdej komendy w pliku
{
	std::ifstream inFile;	//tworzenie obiektu input File
	inFile.open(filePath);	//otwarcie pliku

	std:: string line = "";	//pusty string o nazwie wiersz

	if(!inFile.is_open())	//sprawdza czy z sukcesem otworzono plik
	{
		std:: cout << "Can not open file" << filePath << std::endl; //error
		return false;
	}

	while(!inFile.eof()) //czyta kazdy wiersz pliku az do konca
	{
		std::getline(inFile, line); //czyta wiersz z pliku i przechowuje go w zmiennej line

		size_t commandPos = std::string::npos; //tworzy zmienna commandPos, przechowujaca pozycje komendy w wierszu

		if((commandPos = line.find(":")) != std::string::npos) //sprawdzenie czy wiersz zawiera polecenie zawierajace :
		{
			size_t dilimitPos = line.find_first_of(" ", commandPos); //tworzy zmeinna, ktora przechowuje pozycje pierwszej spacji po komendzie w wierszu

			if(dilimitPos == std::string::npos)	//jezeli spacji nie ma
			{
				dilimitPos = line.length(); // to dlimitPos ustawiamy na koniec wiersza
			}
			else // jak spacja jest
			{
				dilimitPos -= 1; //przesuwamy dlimitPos o 1 w lewo
			}

			std::string commandStr = line.substr(commandPos+1, dilimitPos); //tworzy string commandStr przechowujacy komende
			dilimitPos += 1; //przesuwany dlimitPos o 1 w prawo

			for(size_t commandIndex = 0; commandIndex < mCommands.size(); ++commandIndex) // iteracja przez wektor komend
			{
				if(commandStr == mCommands[commandIndex].command) //sprawdza czy CommandStr pasuje do komendy z wektora
				{
					if(mCommands[commandIndex]. commandType == COMMAND_ONE_LINE) //sprawdza czy komenta jest jednowierszowa
					{
						ParseFuncParams params;	//tworzy obiekt typu ParseFuncParams, ktory bedzie uzywany do przekzazywania parametrow do analizy
						params.dilimitPos = dilimitPos; //ustawia parametr dlimitPos z params na dilimiatPos
						params.lineNum = 0; // ustawia lineNum parametr z params na 0
						params.line = line; //ustawia line pramatr z params na aktualny wiersz
						mCommands[commandIndex].parseFunc(params); //funkcja analizy
					}
					else // jak wielowierszowa
					{
						std::string numLines = line.substr(dilimitPos+1); // liczba linii jako string
						int totalLines = std::stoi(numLines); //konwersja na integer
						int lineNum = 0; //biezacy numer linii

						while(lineNum < totalLines) //czyta kazda linie dopoki nie nastapi total
						{
							std::getline(inFile, line); //czyta wiersz i przechowuje w line

							if(line.empty()) //jezeli linia pusta
							{
								continue; //skip do kolejnej iteracji
							}
							else
							{
								ParseFuncParams params;//tworzy obiekt typu ParseFuncParams, ktory bedzie uzywany do przekzazywania parametrow do analizy
								params.dilimitPos = 0; //ustawia parametr dlimitPos z params na 0
								params.lineNum = lineNum; // ustawia lineNum parametr z params na lineNum
								params.line = line; //ustawia line pramatr z params na aktualny wiersz
								mCommands[commandIndex].parseFunc(params); //funkcja analizy
								++lineNum; //line Num ++
							}
						}
					}
				}
			}
		}
	}
	return true;
}

Color FileCommandLoader::ReadColor(const ParseFuncParams& params)
{
	size_t nextSpacePos = params.line.find_first_of(" ", params.dilimitPos+1); //znajduje pozyje pierwszej spacji po params.dilimitPos w wierszu
	int r = std::stoi(params.line.substr(params.dilimitPos, (nextSpacePos - params.dilimitPos))); //konwersja substringu w wierszu zaczynajacego sie po params.dilimiPos i konczoacego na spacji na integer

	size_t lastSpacePos = nextSpacePos; //nextSpacePos to teraz Last
	nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);//szuka pozycji kolejnej spacji po last space pos
	int g = std::stoi(params.line.substr(lastSpacePos+1, nextSpacePos - lastSpacePos));//konwersja substringu w wierszu zaczynajacego sie po spacji i konczoacego na spacji na integer
	lastSpacePos = nextSpacePos; //nextSpacePos to teraz Last

	nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);//szuka pozycji kolejnej spacji po last space pos
	int b = std::stoi(params.line.substr(lastSpacePos + 1, nextSpacePos - lastSpacePos));//konwersja substringu w wierszu zaczynajacego sie po spacji i konczoacego na spacji na integer
	int a = std::stoi(params.line.substr(nextSpacePos + 1));//konwersja substringu w wierszu zaczynajacego sie po spacji na integer

	return Color(r, g , b, a);
}

int FileCommandLoader::ReadInt( const ParseFuncParams& params)
{
	std::string intStr = params.line.substr(params.dilimitPos + 1); //tworzy substring wiersza ktory zaczyna sie po params.dilimitPos a konczy na koncu linii
	return std::stoi(intStr); // konwertuje substring na int
}

char FileCommandLoader::ReadChar(const ParseFuncParams& params)
{
	return params.line.substr(params.dilimitPos +1)[0]; //zwraca 1szy znak substringu w linii, ktory zaczyna sie po params.silimitPos
}



