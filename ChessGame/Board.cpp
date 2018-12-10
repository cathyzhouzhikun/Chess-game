#pragma once

#include "stdafx.h"
#include <iostream>
#include "Board.h"

// TODO set up a Board
Board::Board()
{
	initializeBoard();
}


Board::~Board()
{
}

// to initialize the board, set all the squre to be empty
void Board::initializeBoard()
{
	for (int i = 0; i < BoradRows; i++)
	{
		for (int j = 0; j < BoardColumns; j++)
		{
			Point p = Point(i, j);
			SetBoardPiece(p, PieceColor::None, PieceType::Empty);
		}
	}
	setTurn(PieceColor::White);
}

bool Board::SquareOccupied(Point p)
{
	Piece piece = BoardState[p.x][p.y];
	if (piece.type != PieceType::Empty)
		return true;
	else
		return false;
}

void Board::setTurn(PieceColor color)
{
	this->Turn = color;
}

PieceColor Board::getTurn()
{
	return this->Turn;
}

void Board::setLastMove(Point f, Point t)
{
	lastMove.from = f;
	lastMove.to = t;

	Piece p(GetPieceColor(f), GetPieceType(f));
	p.HasMoved = true;

	lastMove.piece = p;
}

Move Board::getLastMove()
{
	return lastMove;
}

PieceColor Board::GetPieceColor(Point p)
{
	Piece piece = BoardState[p.x][p.y];
	return piece.color;
}

PieceType Board::GetPieceType(Point p)
{
	Piece piece = BoardState[p.x][p.y];
	return piece.type;
}

void Board::PieceHasMoved(Point p, bool b)
{
	BoardState[p.x][p.y].HasMoved = b;
}

bool Board::PieceHasMoved(Point p)
{
	return BoardState[p.x][p.y].HasMoved;
}

void Board::MakeMove(Point from, Point to, Piece p)
{
	BoardLocation bFrom((Col)from.y, (Row)from.x);
	BoardLocation bTo((Col)to.y, (Row)to.x);
	MakeMove(bFrom, bTo, p);
}

void Board::MakeMove(BoardLocation from, BoardLocation to, Piece p)
{
	SetBoardPiece(to.col, to.row, p.color, p.type);
	SetBoardPiece(from.col, from.row, PieceColor::None, PieceType::Empty);
}

void Board::SetBoardPiece(Point pointLoc, PieceColor color, PieceType type)
{
	BoardLocation bLoc((Col)pointLoc.y, (Row)pointLoc.x);
	SetBoardPiece(bLoc.col, bLoc.row, color, type);
}

void Board::SetBoardPiece(Col col, Row row, PieceColor color, PieceType type)
{
	Piece piece(color, type);
	BoardState[(int)row][(int)col] = piece;
}

PieceColor Chess::Board::OppositeColor(PieceColor color)
{
	if (color == PieceColor::Black)
		return PieceColor::White;
	if (color == PieceColor::White)
		return PieceColor::Black;
}

// check if the move will result in the check position
bool Board::CheckForCheck(PieceColor color)
{
	// get the king's position for the move side
	Point to = getKingLoc(color);
	for (int i = 0; i < BoradRows; i++)
	{
		for (int j = 0; j < BoardColumns; j++)
		{
			//std::cout << BoardState[i][j] << "  ";
			if (BoardState[i][j].color == OppositeColor(color))
			{
				Point from(i, j);
				if (MovePossible(from, to).valid)
					return true;
			}
		}
	}
	return false;
}

Point Board::getKingLoc(PieceColor color)
{
	for (int i = 0; i < BoradRows; i++)
	{
		for (int j = 0; j < BoardColumns; j++)
		{
			if (BoardState[i][j].color == color && BoardState[i][j].type == PieceType::King)
			{
				return Point(i, j);
			}
		}
	}
}

Validity Board::ValidateMove(Point from, Point to)
{
	// Check to see if move is by the correct color
	if (GetPieceColor(from) != getTurn())
		return Validity(false, "Not your turn.");

	// Check to see if move is to a space occupied by own piece
	if (GetPieceColor(to) == getTurn())
		return Validity(false, "Can't take your own piece.");

	// Check to see if move is reachable and not blocked
	Validity v = MovePossible(from, to);
	if (!v.valid)
		return Validity(false, v.reason);

	// Check to see if move puts king in check
	//if (CheckForCheck(getTurn()))
	//	return Validity(false, "Move puts or keeps your king in check");

	// if the move is valid, change the turn to the other side
	if (getTurn() == PieceColor::Black)
		setTurn(PieceColor::White);
	else
		setTurn(PieceColor::Black);
	// next three lines needed when validating en passant
	lastMove.from = from;
	lastMove.to = to;
	lastMove.piece.type = GetPieceType(from);

	return Validity(true, "");
}

// TODO check if the move will cause checkmate
bool Board::isCheckMate()
{
	return false;
}

// TODO is the game becomes draw
bool Board::isDraw()
{
	return false;
}

// TODO check if the move is the right direction for pawn
Validity Board::PawnDirectionCorrect(Point from, Point to)
{
	return Validity(true, "");
}



// TODO check for legally taking a piece (includes en passant)
Validity Board::PawnTakingPiece(Point to, Point from)
{
	return Validity(true, "");
}

// TODO need to check to see if 2 squre move is from home row
Validity Board::PawnTwoSpaceJump(Point from, Point to)
{
	return Validity(true, "");
}

//  check if the path is reachable and clear horizontally and vertically
bool Board::ReachableAndClear90(Point from, Point to)
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
bool Board::ReachableAndClear45(Point from, Point to)
{
	if ((from.x > to.x) && (from.x - to.x) == (to.y - from.y))    // if the direction is to move diagonally NE 
	{
		if (PathClear45(from, to))
			return true;
	}
	if ((from.x > to.x) && (from.x - to.x) == (from.y - to.y))    // if the direction is to move diagonally NW
	{
		if (PathClear135(from, to))
			return true;
	}
	if ((from.x < to.x) && (to.x - from.x) == (from.y - to.y))    // if the direction is to move diagonally SW
	{
		if (PathClear225(from, to))
			return true;
	}
	if ((from.x < to.x) && (to.x - from.x) == (to.y - from.y))    // if the direction is to move diagonally SE
	{
		if (PathClear315(from, to))
			return true;
	}
	return false;
}


// TODO check if Rook has already moved
bool Board::RookHasMoved(Point from, Point to)
{
	return false;
}

// TODO check to see if path between rook and king is clear
bool Board::CastlingPathClear(Point from, Point to)
{
	return true;
}

// TODO check to see if no squre along the path puts the king in check
bool Board::CastlePathCheckFree(Point from, Point to)
{
	return true;
}

Validity Board::MovePossible(Point from, Point to)
{
	Validity v(true, "");
	PieceType type = GetPieceType(from);
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

bool Board::PathClear90(Point from, Point to)
{
	for (int i = from.x + 1; i < to.x; i++)
	{
		Point p(i, from.y);
		if (SquareOccupied(p))
			return false;
	}
	return true;
}

bool Board::PathClear270(Point from, Point to)
{
	for (int i = from.x - 1; i > to.x; i--)
	{
		Point p(i, from.y);
		if (SquareOccupied(p))
			return false;
	}
	return true;
}

bool Board::PathClear180(Point from, Point to)
{
	for (int i = from.y - 1; i > to.y; i--)
	{
		Point p(from.x, i);
		if (SquareOccupied(p))
			return false;
	}
	return true;
}

bool Board::PathClear360(Point from, Point to)
{
	for (int i = from.y + 1; i < to.y; i++)
	{
		Point p(from.x, i);
		if (SquareOccupied(p))
			return false;
	}
	return true;
}

bool Board::PathClear45(Point from, Point to)
{
	int i = 0;
	int j = 0;
	for (i = from.x - 1, j = from.y + 1; i > to.x; i--, j++)
	{
		Point p(i, j);
		if (SquareOccupied(p))
			return false;
	}
	return true;
}

bool Board::PathClear135(Point from, Point to)
{
	int i = 0;
	int j = 0;
	for (i = from.x - 1, j = from.y - 1; i > to.x, j > to.y; i--, j--)
	{
		Point p(i, j);
		if (SquareOccupied(p))
			return false;
	}
	return true;
}

bool Board::PathClear225(Point from, Point to)
{
	int i = 0;
	int j = 0;
	for (i = from.x + 1, j = from.y - 1; i < to.x, j > to.y; i++, j--)
	{
		Point p(i, j);
		if (SquareOccupied(p))
			return false;
	}
	return true;
}

bool Board::PathClear315(Point from, Point to)
{
	int i = 0;
	int j = 0;
	for (i = from.x + 1, j = from.y + 1; i < to.x, j < to.y; i++, j++)
	{
		Point p(i, j);
		if (SquareOccupied(p))
			return false;
	}
	return true;
}
