// ChessGame.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <iostream>
#include "Board.h"
#include "FChessGame.h"
#include "Chess.h"

using namespace Chess;

// Function prototypes 
void PrintBoard(Board b);
void SetBoard_0(Board &b);
void SetBoard_1(Board &b);
void TestCase(Board b);
BoardLocation readInMove(std::string move);
bool MoveInputValid(std::string move);

int main()
{
	FChessGame game;   // instantiate a new chess game. This will set up a board and set up the turn to White
	Board b = game.getBoard();
	int testChoice;
	std::cout << "\nEnter your board choice. 0 for test Queens move, 1 for check for check situation: ";
	std::cin >> testChoice;
	if (testChoice == 0)
		SetBoard_0(b);
	if (testChoice == 1)
		SetBoard_1(b);

	TestCase(b);
    return 0;
}

void PrintBoard(Board b)
{
	int row = b.BoradRows;
	int col = b.BoardColumns;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Piece p = b.BoardState[i][j];
			std::cout << p;
		}
		std::cout << std::endl;
	}
}

void SetBoard_0(Board &b)
{
	b.SetBoardPiece(Col::b, Row::eight, PieceColor::Black, PieceType::King);
	b.SetBoardPiece(Col::b, Row::seven, PieceColor::White, PieceType::Pawn);
	b.SetBoardPiece(Col::d, Row::seven, PieceColor::White, PieceType::Pawn);
	b.SetBoardPiece(Col::f, Row::seven, PieceColor::White, PieceType::Pawn);
	b.SetBoardPiece(Col::d, Row::five, PieceColor::White, PieceType::Queen);
	b.SetBoardPiece(Col::g, Row::two, PieceColor::White, PieceType::Knight);
	b.SetBoardPiece(Col::d, Row::two, PieceColor::White, PieceType::King);
	b.SetBoardPiece(Col::g, Row::five, PieceColor::White, PieceType::Pawn);
}

void SetBoard_1(Board &b)
{
	b.SetBoardPiece(Col::b, Row::four, PieceColor::Black, PieceType::Queen);
	b.SetBoardPiece(Col::d, Row::two, PieceColor::White, PieceType::Pawn);
	b.SetBoardPiece(Col::e, Row::one, PieceColor::White, PieceType::King);
	b.SetBoardPiece(Col::b, Row::eight, PieceColor::Black, PieceType::King);
	b.SetBoardPiece(Col::e, Row::six, PieceColor::White, PieceType::Queen);
	b.SetBoardPiece(Col::c, Row::four, PieceColor::White, PieceType::Pawn);
	b.SetBoardPiece(Col::g, Row::three, PieceColor::Black, PieceType::Knight);
}

void TestCase(Board b)
{
	std::cout << "\n\n The current Board is:  \n\n";
	PrintBoard(b);

	std::string turn = "";
	switch (b.getTurn())
	{
	case PieceColor::Black:
		turn = "Black";
		break;
	case PieceColor::White:
		turn = "White";
		break;
	default:
		break;
	}

	std::cout << "Now is the " << turn << "'s turn.\n";
	std::string from = "";
	std::cout << "Enter a from squre : ";
	std::cin >> from;
	std::string to = "";
	std::cout << "Enter a to squre : ";
	std::cin >> to;
	BoardLocation f = readInMove(from);
	Piece p = b.BoardState[(int)f.row][(int)f.col];    // the piece that was taken to move
	std::cout << "Trying to move " << p << std::endl;
	BoardLocation t = readInMove(to);

	Point pFrom((int)f.row, (int)f.col);
	Point pTo((int)t.row, (int)t.col);
	bool reach = b.ReachableAndClear45(pFrom, pTo);
	std::cout << "Is diagonally clear? " << reach << "\n";
	Point king = b.getKingLoc(b.getTurn());
	std::cout << "the king position is " << king.x << king.y << "\n";
	std::cout << "the king square is " << b.SquareOccupied(king) << "\n";
	Validity isValid = b.ValidateMove(pFrom, pTo);

	if (isValid.valid)
	{
		std::cout << "Move is valid!" << std::endl;
		b.MakeMove(f, t, p);
	}
	else
		std::cout << "Move is invalid! " << isValid.reason << "\n";
	
	PrintBoard(b);

}



BoardLocation readInMove(std::string move)
{
	Col c;
	Row r;
	char col = move[0];
	switch (col)
	{
	case 'a':
		c = Col::a;
		break;
	case 'b':
		c = Col::b;
		break;
	case 'c':
		c = Col::c;
		break;
	case 'd':
		c = Col::d;
		break;
	case 'e':
		c = Col::e;
		break;
	case 'f':
		c = Col::f;
		break;
	case 'g':
		c = Col::g;
		break;
	case 'h':
		c = Col::h;
		break;
	default:
		break;

	}

	char row = move[1];
	switch (row)
	{
	case '1':
		r = Row::one;
		break;
	case '2':
		r = Row::two;
		break;
	case '3':
		r = Row::three;
		break;
	case '4':
		r = Row::four;
		break;
	case '5':
		r = Row::five;
		break;
	case '6':
		r = Row::six;
		break;
	case '7':
		r = Row::seven;
		break;
	case '8':
		r = Row::eight;
		break;
	default:
		break;
	}
	return BoardLocation(c, r);
	
}

bool MoveInputValid(std::string move)
{
	return true;
}
