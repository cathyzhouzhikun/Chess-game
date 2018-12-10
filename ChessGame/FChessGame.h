#pragma once

#include "Chess.h"
#include "Board.h"

using namespace Chess;
namespace Chess
{
	class FChessGame
	{
	public:
		FChessGame();
		~FChessGame();
		void initializeGame();
		Board getBoard();
		void setBoard(Board b);
		Validity move(Point from, Point to, Piece p);
		
		

	private:
		Board board;
		
		
		
	};

}