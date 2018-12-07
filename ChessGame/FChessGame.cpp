#pragma once

#include "stdafx.h"
#include "FChessGame.h"
#include <cmath>

FChessGame::FChessGame()
{
	initializeGame();
}


FChessGame::~FChessGame()
{
}

void Chess::FChessGame::initializeGame()
{
	board.initializeBoard();
	Turn = PieceColor::White;
}

Board Chess::FChessGame::getBoard()
{
	return board;
}

void Chess::FChessGame::setBoard(Board b)
{
	board = b;
}

void FChessGame::setTurn(PieceColor color)
{
	this->Turn = color;
}

PieceColor FChessGame::getTurn()
{
	return this->Turn;
}

void Chess::FChessGame::setLastMove(Point f, Point t)
{
	lastMove.from = f;
	lastMove.to = t;

	Piece p(board.GetPieceColor(f), board.GetPieceType(f));
	p.HasMoved = true;
	
	lastMove.piece = p;
}

Move Chess::FChessGame::getLastMove()
{
	return lastMove;
}

// TODO check if the move will result in the check position
bool FChessGame::CheckForCheck(PieceColor color)
{
	// get the king's position for the move side
	Point to = getKingLoc(color);
	for (int i = 0; i < board.BoradRows; i++)
	{
		for (int j = 0; j < board.BoardColumns; j++)
		{
			if (board.BoardState[i][j].color != color)
			{
				Point from(i, j);
				if (MovePossible(from, to).valid)
					return true;
			}
		}
	}
	return false;
}

Point Chess::FChessGame::getKingLoc(PieceColor color)
{
	for (int i = 0; i < board.BoradRows; i++)
	{
		for (int j = 0; j < board.BoardColumns; j++)
		{
			if (board.BoardState[i][j].color == color && board.BoardState[i][j].type == PieceType::King)
			{
				return Point(i, j);
			}
		}
	}
}

Validity FChessGame::ValidateMove(Point from, Point to)
{
	// Check to see if move is by the correct color
	if (board.GetPieceColor(from) != getTurn())
		return Validity(false, "Not your turn.");

	// Check to see if move is to a space occupied by own piece
	if (board.GetPieceColor(to) == getTurn())
		return Validity(false, "Can't take your own piece.");

	// Check to see if move is reachable and not blocked
	Validity v = MovePossible(from, to);
	if (!v.valid)
		return Validity(false, v.reason);

	// Check to see if move puts king in check
	if (CheckForCheck(getTurn()))
		return Validity(false, "Move puts or keeps your king in check");

	// if the move is valid, change the turn to the other side
	if (getTurn() == PieceColor::Black)
		setTurn(PieceColor::White);
	else
		setTurn(PieceColor::Black);
	// next three lines needed when validating en passant
	lastMove.from = from;
	lastMove.to = to;
	lastMove.piece.type = board.GetPieceType(from);

	return Validity(true, "");
}

// TODO check if the move will cause checkmate
bool FChessGame::isCheckMate()
{
	return false;
}

// TODO is the game becomes draw
bool FChessGame::isDraw()
{
	return false;
}

// TODO check if the move is the right direction for pawn
Validity Chess::FChessGame::PawnDirectionCorrect(Point from, Point to)
{
	return Validity(true, "");
}

// TODO check for legally taking a piece (includes en passant)
Validity Chess::FChessGame::PawnTakingPiece(Point to, Point from)
{
	return Validity(true, "");
}

// TODO need to check to see if 2 squre move is from home row
Validity Chess::FChessGame::PawnTwoSpaceJump(Point from, Point to)
{
	return Validity(true, "");
}

//  check if the path is reachable and clear horizontally and vertically
bool Chess::FChessGame::ReachableAndClear90(Point from, Point to)
{
	// if the direction is to move down vertically
	if (from.y == to.y && from.x < to.x)
	{
		if (PathClear90(from, to))
			return true;
	}
	// if the direction is to move up vertically
	if (from.y == to.y && from.x > to.x)
	{
		if (PathClear270(from, to))
			return true;
	}
	// if the direction is to move left horizontally
	if (from.x == to.x && from.y > to.y)
	{
		if (PathClear180(from, to))
			return true;
	}
	// if the direction is to move right horizontally
	if (from.x == to.x && from.y < to.y)
	{
		if (PathClear360(from, to))
			return true;
	}
	return false;
}

// check if the path is reachable and clear diagonally
bool Chess::FChessGame::ReachableAndClear45(Point from, Point to)
{
	if ((from.x - to.x) == (to.y - from.y))    // if the direction is to move diagonally NE 
	{
		if (PathClear45(from, to))
			return true;
	}
	if ((from.x - to.x) == (from.y - to.y))    // if the direction is to move diagonally NW
	{
		if (PathClear135(from, to))
			return true;
	}
	if ((to.x - from.x) == (from.y - to.y))    // if the direction is to move diagonally SW
	{
		if (PathClear225(from, to))
			return true;
	}
	if ((to.x - from.x) == (to.y - from.y))    // if the direction is to move diagonally SE
	{
		if (PathClear315(from, to))
			return true;
	}
	return false;
}

// TODO check if King has already moved
bool Chess::FChessGame::PieceHasMoved(Point from)
{
	return false;
}
// TODO check if Rook has already moved
bool Chess::FChessGame::RookHasMoved(Point from, Point to)
{
	return false;
}

// TODO check to see if path between rook and king is clear
bool Chess::FChessGame::CastlingPathClear(Point from, Point to)
{
	return true;
}

// TODO check to see if no squre along the path puts the king in check
bool Chess::FChessGame::CastlePathCheckFree(Point from, Point to)
{
	return true;
}

Validity FChessGame::MovePossible(Point from, Point to)
{
	Validity v(true, "");
	PieceType type = board.GetPieceType(from);
	switch (type)
	{
	case PieceType::Pawn:
		v = PawnDirectionCorrect(from, to);  // Is pawn moving in correct direction
		if (!v.valid)
			return v;
		if (from.x != to.x)   // need to check for legally taking a piece (includes en passant)
			return PawnTakingPiece(to, from);
		if ((from.y - to.y) == 2 || (to.y - from.y) == 2)  // need to check to see if 2 squre move is from home row
			return PawnTwoSpaceJump(from, to);
		if ((from.y - to.y) > 1 || (to.y - from.y) > 1)   // check for normal 1 row advancement
			return Validity(false, "pawn can only move 1 space from current location.");
		break;
	case PieceType::Rook:
		if (!ReachableAndClear90(from, to))
			return Validity(false, "Rook can only move horizontally and vertically over clear spaces.");
		break;
	case PieceType::Knight:
		if ((abs(from.x - to.x) == 2) && (abs(from.y - to.y) == 1))
			break;
		if ((abs(from.x - to.x) == 1) && (abs(from.y - to.y) == 2))
			break;
		return Validity(false, "Knight can only move in a 2,1 or 1, 2 \'L\' shape.");
	case PieceType::Bishop:
		if (!ReachableAndClear45(from, to))
			return Validity(false, "Bishop can only diagnonally over unobstructed spaces.");
		break;
	case PieceType::Queen:
		if (ReachableAndClear90(from, to))
			break;
		if (!ReachableAndClear45(from, to))
			return Validity(false, "Queen can only move diagonally, vertically or horizontally over unobstructed spaces.");
		break;
	case PieceType::King:
		// need to handle castling possiblility
		if ((((from.x - to.x == 2) || (to.x - from.x == 2)) && (from.y == to.y)))
		{
			// check to see if king has already moved
			if (PieceHasMoved(from))
				return Validity(false, "Cannot castle, King has already moved.");
			// check to see if Rook has already moved
			if (RookHasMoved(from, to))
				return Validity(false, "Cannot castle, Rook has already moved.");
			// check to see if path between rook and king is clear
			if (!CastlingPathClear(from, to))
				return Validity(false, "Cannot castle, path from king to rook not clear.");
			// check to see if no squre along the path puts the king in check
			if (!CastlePathCheckFree(from, to))
				return Validity(false, "Cannot castle, move would put king in check along path.");
			break;
		}
		// Is king trying to move more than one spaces?
		if ((from.x - to.x) > 1 || (to.x - from.x) > 1 || (from.y - to.y > 1) || (to.y - from.y > 1))
			return Validity(false, "King can only move one space");
		break;

	default:
		break;
	}
	return v;
}

bool Chess::FChessGame::PathClear90(Point from, Point to)
{
	for (int i = from.x + 1; i < to.x; i++)
	{
		Point p(i, from.y);
		if (board.SquareOccupied(p))
			return false;
	}
	return true;
}

bool Chess::FChessGame::PathClear270(Point from, Point to)
{
	for (int i = from.x - 1; i > to.x; i--)
	{
		Point p(i, from.y);
		if (board.SquareOccupied(p))
			return false;
	}
	return true;
}

bool Chess::FChessGame::PathClear180(Point from, Point to)
{
	for (int i = from.y - 1; i > to.y; i--)
	{
		Point p(from.x, i);
		if (board.SquareOccupied(p))
			return false;
	}
	return true;
}

bool Chess::FChessGame::PathClear360(Point from, Point to)
{
	for (int i = from.y + 1; i < to.y; i++)
	{
		Point p(from.x, i);
		if (board.SquareOccupied(p))
			return false;
	}
	return true;
}

bool Chess::FChessGame::PathClear45(Point from, Point to)
{
	int i = 0;
	int j = 0;
	for (i = from.x - 1, j = from.y + 1; i > to.x; i--, j++)
	{
		Point p(i, j);
		if (board.SquareOccupied(p))
			return false;
	}
	return true;
}

bool Chess::FChessGame::PathClear135(Point from, Point to)
{
	int i = 0;
	int j = 0;
	for (i = from.x - 1, j = from.y - 1; i > to.x, j > to.y; i--, j--)
	{
		Point p(i, j);
		if (board.SquareOccupied(p))
			return false;
	}
	return true;
}

bool Chess::FChessGame::PathClear225(Point from, Point to)
{
	int i = 0;
	int j = 0;
	for (i = from.x + 1, j = from.y - 1; i < to.x, j > to.y; i++, j--)
	{
		Point p(i, j);
		if (board.SquareOccupied(p))
			return false;
	}
	return true;
}

bool Chess::FChessGame::PathClear315(Point from, Point to)
{
	int i = 0;
	int j = 0;
	for (i = from.x + 1, j = from.y + 1; i < to.x, j < to.y; i++, j++)
	{
		Point p(i, j);
		if (board.SquareOccupied(p))
			return false;
	}
	return true;
}
