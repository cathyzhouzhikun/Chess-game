#pragma once

#include "Chess.h"
using namespace Chess;
namespace Chess
{
	class Board
	{
	public:
		Board();
		~Board();
		const static int BoardColumns = 8;
		const static int BoradRows = 8;
		Piece BoardState[BoardColumns][BoradRows];

		void initializeBoard();
		bool SquareOccupied(Point p);
		
		PieceColor GetPieceColor(Point p);
		PieceType GetPieceType(Point p);
		void PieceHasMoved(Point p, bool b);
		bool PieceHasMoved(Point p);
		void MakeMove(Point from, Point to, Piece p);
		void MakeMove(BoardLocation from, BoardLocation to, Piece p);
		void SetBoardPiece(Point pointLoc, PieceColor color, PieceType type);
		void SetBoardPiece(Col col, Row row, PieceColor color, PieceType type);


	private:
		


	};

}