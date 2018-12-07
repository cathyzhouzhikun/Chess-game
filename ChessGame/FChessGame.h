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
		void setTurn(PieceColor color);
		PieceColor getTurn();
		void setLastMove(Point f, Point t);
		Move getLastMove();
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

		bool PieceHasMoved(Point from);
		bool RookHasMoved(Point from, Point to);
		bool CastlingPathClear(Point from, Point to);
		bool CastlePathCheckFree(Point from, Point to);

	private:
		Board board;
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