#pragma once

#include "stdafx.h"
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
void Chess::Board::initializeBoard()
{
	for (int i = 0; i < BoradRows; i++)
	{
		for (int j = 0; j < BoardColumns; j++)
		{
			Point p = Point(i, j);
			SetBoardPiece(p, PieceColor::None, PieceType::Empty);
		}
	}

}

bool Board::SquareOccupied(Point p)
{
	Piece piece = BoardState[p.x][p.y];
	if (piece.type != PieceType::Empty)
		return true;
	else
		return false;
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
	BoardLocation bFrom((Col)from.x, (Row)from.y);
	BoardLocation bTo((Col)to.x, (Row)to.y);
	MakeMove(bFrom, bTo, p);
}

void Board::MakeMove(BoardLocation from, BoardLocation to, Piece p)
{
	//BoardState[(int)to.col][(int)to.row] = BoardState[(int)from.col][(int)to.row];
	//Piece piece(PieceColor::None, PieceType::Empty);
	//BoardState[(int)from.col][(int)from.row] = piece;
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

