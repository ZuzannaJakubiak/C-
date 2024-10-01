/*
 * BreakoutGameLevel.cpp
 *
 *  Created on: 6 sty 2023
 *      Author: Zuzanna Jakubiak
 */

#include "BreakoutGameLevel.h"
#include "Ball.h"
#include "App.h"
#include "FileCommandLoader.h"
#include <stdlib.h>
#include <time.h>



BreakoutGameLevel::BreakoutGameLevel()
{

}

void BreakoutGameLevel::Load(const std::vector<Block>& blocks)
{
	mBlocks.clear(); //czyszczenie
	mBlocks = blocks; //set blokow
}

void BreakoutGameLevel::Update(uint32_t dt, Ball& ball)
{
	std::vector<Block> collidedBlocks; //wektor przechowujacy collidedBlocks

	BoundaryEdge edgeToBounceOffOf;
	Block* noptrBlockToBounceOffOf = nullptr;

	float largestMag = -1.0f;



	for(auto& block : mBlocks) //iteracja po blokach
	{
		BoundaryEdge edge; //krawedz do sprawdzania kolizji

		//jezeli blok nie zniszczony i ball miala kolizie z blokiem
		if(!block.IsDestroyed() &&
			block.HasCollided(ball.GetBoundingRect(), edge))
		{
			collidedBlocks.push_back(block); //dodaje blok do CollidedBlocks

			//dlugosc offsetu kolizji
			float mag = block.GetCollisionOffset(ball.GetBoundingRect()).Mag();

			if(mag > largestMag)
			{
				edgeToBounceOffOf = edge; //krawedz od ktorej ma sie odbic
				noptrBlockToBounceOffOf = &block;//blok od ktorego ma sie odbic

			}
		}
	}
	//jak jesy blok od ktorego sie odibic
	if(noptrBlockToBounceOffOf != nullptr)
	{
		noptrBlockToBounceOffOf->Bounce(ball, edgeToBounceOffOf); //odbij
		noptrBlockToBounceOffOf->ReduceHP(); //odejmij hp
	}

	for(const auto& block : collidedBlocks) //iteracja po CollidedBlocks
	{
		BoundaryEdge edge; //krawedz do sprawdzania kolizji
		if(block.HasCollided(ball.GetBoundingRect(), edge)) //jezelu byla kolizja z ball
		{
			Vec2D p; //punkt na krawedzi
			ball.MakeFlushWithEdge(edge, p, true);//wurownanie do krawedzu
		}
	}
}

void BreakoutGameLevel::Draw(Screen& screen)
{
	for(auto& block: mBlocks) //iteracja po bloczkach
	{
		if(!block.IsDestroyed()) //jezelu nie zniszczony
		{
			block.Draw(screen); //rysuj
		}

	}
}


bool BreakoutGameLevel::IsLevelComplete() const
{
	for(size_t i =0; i< mBlocks.size(); ++i) //iteracja po blokach
	{
		//jezeli nie zniszczony i nie jest niezniszczalny
		if(!mBlocks[i].IsDestroyed() && mBlocks[i].GetHP() != Block::UNBREAKABLE)
		{
			return false;
		}
	}
	return true;
}

LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock>& blocks, char symbol)
{
	for(size_t i = 0; i < blocks.size(); ++i) //iteracja po blokach
	{
		if(blocks[i].symbol == symbol) //jezeli blok pasuje do symbolu
		{
			return blocks[i]; //zwroc blok
		}
	}

	return LayoutBlock();//jak symbol nieznaleziony to pysty LayoutBlock
}


std::vector<BreakoutGameLevel> BreakoutGameLevel::LoadLevelsFromFile(const std::string& filePath)
{
	std::vector<BreakoutGameLevel> levels; //wektor przechowywujacy levele

	std::vector<LayoutBlock> layoutBlocks; //wektor przechwywujacy LayoutBlocks

	std::vector<Block> levelBlocks; //wektor przechowywujacy levelBlocks


	 int width = 0; //szerokosc
	 int height = 0; //wysokosc


	 FileCommandLoader fileLoader;

	 Command levelCommand;
	 levelCommand.command = "level";
	 levelCommand.parseFunc = [&](ParseFuncParams params) {
		if(levels.size() > 0) //jezeli sa levele w wektorzee
		{
			levels.back().Load(levelBlocks); //zaladuj bloki do ostatniego levelu w wektorze
		}
		layoutBlocks.clear();
		levelBlocks.clear();
		width = 0;
		height = 0;

		BreakoutGameLevel level; //nowy level
		//level.Init(AARectangle(Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()));

		levels.push_back(level);//dodaje nowy level do wektora
	 };

	 fileLoader.AddCommand(levelCommand);

	 Command blockCommand;
	 blockCommand.command = "block";
	 blockCommand.parseFunc = [&](ParseFuncParams params) {
		 LayoutBlock lb; //nowy LayoutBlock obiekt

		 layoutBlocks.push_back(lb); //dodaj layout do wektora
	 };

	 fileLoader.AddCommand(blockCommand);

	 Command symbolCommand;
	 symbolCommand.command = "symbol";
	 symbolCommand.parseFunc = [&](ParseFuncParams params) {
		 //symbol ostatniego layoutBlocku do wektora
		 layoutBlocks.back().symbol = FileCommandLoader::ReadChar(params);
	 };

	 fileLoader.AddCommand(symbolCommand);

	 Command fillColorCommand;
	 fillColorCommand.command = "fillcolor";
	 fillColorCommand.parseFunc = [&](ParseFuncParams params) {
		 //kolor ostatniego layoutBlocku do wektora
		layoutBlocks.back().color = FileCommandLoader::ReadColor(params);
	 };

	 fileLoader.AddCommand(fillColorCommand);

	 Command hpCommand;
	 hpCommand.command = "hp";
	 hpCommand.parseFunc = [&](ParseFuncParams params) {
		 //hp ostatniego layoutBlocku do wektora
		layoutBlocks.back().hp = FileCommandLoader::ReadInt(params);
	 };

	 fileLoader.AddCommand(hpCommand);

	 Command widthCommand;
	 widthCommand.command = "width";
	 widthCommand.parseFunc = [&](ParseFuncParams params) {
		 //szerokosc
		width = FileCommandLoader::ReadInt(params);
	 };

	 fileLoader.AddCommand(widthCommand);

	 Command heightCommand;
	 heightCommand.command = "height";
	 heightCommand.parseFunc = [&](ParseFuncParams params) {
		 //wysokosc
		height = FileCommandLoader::ReadInt(params);
	 };

	 fileLoader.AddCommand(heightCommand);


	 Command layoutCommand;
	 layoutCommand.commandType = COMMAND_MULTI_LINE;
	 layoutCommand.command = "layout";
	 layoutCommand.parseFunc = [&](ParseFuncParams params) {

		 //pozycja startowa x
		 float startingX = 0;
		 //inicjalizacja bloku jako prostokata z pozycja startowa i wymiarami
		 AARectangle blockRect(Vec2D(startingX, (params.lineNum+1)*BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT);

		 //iteracja po charach w wierszu
		 for(unsigned int c = 0; c < params.line.length();++c)
		 {
			 if(params.line[c] != '-') //jezeli nie -
			 {
				 //Znajdz LayoutBlock dla symbolu
				 LayoutBlock layoutBlock = FindLayoutBlockForSymbol(layoutBlocks, params.line[c]);

				 Block b; //nowy blok z informacjami z layout block
				 b.Init(blockRect, layoutBlock.hp, Color::Black(), layoutBlock.color);
				 levelBlocks.push_back(b);
			 }
			 //przesun blok do kolejnej pozycji
			 blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
		 }

	 };

	 //dodaje leyoutcommand do fileLoader
	 fileLoader.AddCommand(layoutCommand);

	 //zaladowanie pliku
	 fileLoader.LoadFile(filePath);

	 if(levels.size() > 0) //zaladowanie blokow
	 {
		 levels.back().Load(levelBlocks);
	 }

	 return levels; //wektor leveli
}

int BreakoutGameLevel::MaxPoints()
{
	int MaxPoints = 0;

	for(auto& block :mBlocks)
	{
		MaxPoints++;
	}

	return MaxPoints;
}

void BreakoutGameLevel::Delete()
{
	int ilosc = MaxPoints()/2;

	for(size_t i =0; i< ilosc ; ++i) //iteracja po blokach
		{
			int ten = rand()% MaxPoints();
			mBlocks[ten].Delete();
		}
}










