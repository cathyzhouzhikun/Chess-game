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

		void setTurn(PieceColor color);
		PieceColor getTurn();

		void setLastMove(Point f, Point t);
		Move getLastMove();

		PieceColor GetPieceColor(Point p);
		PieceType GetPieceType(Point p);

		void PieceHasMoved(Point p, bool b);
		bool PieceHasMoved(Point p);

		void MakeMove(Point from, Point to, Piece p);
		void MakeMove(BoardLocation from, BoardLocation to, Piece p);
		void SetBoardPiece(Point pointLoc, PieceColor color, PieceType type);
		void SetBoardPiece(Col col, Row row, PieceColor color, PieceType type);

		PieceColor OppositeColor(PieceColor color);
		bool CheckForCheck(PieceColor color);
		Point getKingLoc(PieceColor color);
		Validity ValidateMove(Point from, Point to);
		bool isCheckMate();
		bool isDraw();

		Validity PawnDirectionCorrect(Point from, Point to);
		Validity PawnTakingPiece(Point to, Point from);
		Validity PawnTwoSpaceJump(Point from, Point to);

		bool ReachableAndClear90(Point from, Point to);
		bool ReachableAndClear45(Point from, Point to);

	
		bool RookHasMoved(Point from, Point to);
		bool CastlingPathClear(Point from, Point to);
		bool CastlePathCheckFree(Point from, Point to);


	private:
		PieceColor Turn;
		Move lastMove;
		Validity MovePossible(Point from, Point to);
		bool PathClear90(Point from, Point to);
		bool PathClear270(Point from, Point to);
		bool PathClear180(Point from, Point to);
		bool PathClear360(Point from, Point to);
		bool PathClear45(Point from, Point to);
		bool PathClear135(Point from, Point to);
		bool PathClear225(Point from, Point to);
		bool PathClear315(Point from, Point to);


	};

}