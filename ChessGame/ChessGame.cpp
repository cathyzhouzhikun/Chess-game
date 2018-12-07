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
void PrintBoard(FChessGame game);
void TestCase1(FChessGame game);
BoardLocation readInMove(std::string move);
bool MoveInputValid(std::string move);

int main()
{
	FChessGame game;   // instantiate a new chess game. This will set up a board and set up the turn to White
	TestCase1(game);
    return 0;
}

void PrintBoard(FChessGame game)
{
	Board b = game.getBoard();
	int row = b.BoradRows;
	int col = b.BoardColumns;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			PieceColor c = b.BoardState[i][j].color;
			int col = (int)c;
			switch (col)
			{
			case 0:
				std::cout << "";
				break;
			case 1:
				std::cout << "W";
				break;
			case 2:
				std::cout << "B";
				break;
			default:
				break;
			}
			PieceType p = b.BoardState[i][j].type;
			int num = (int)p;
			switch (num)
			{
			case 0:
				std::cout << "E" << "\t";
				break;
			case 1:
				std::cout << "P" << "\t";
				break;
			case 2:
				std::cout << "R" << "\t";
				break;
			case 3:
				std::cout << "N" << "\t";
				break;
			case 4:
				std::cout << "B" << "\t";
				break;
			case 5:
				std::cout << "Q" << "\t";
				break;
			case 6:
				std::cout << "K" << "\t";
				break;
			default:
				break;
			}
			
		}
		std::cout << std::endl;
	}
}

void TestCase1(FChessGame game)
{
	Board b = game.getBoard();
	b.SetBoardPiece(Col::b, Row::four, PieceColor::Black, PieceType::Queen);
	b.SetBoardPiece(Col::d, Row::two, PieceColor::White, PieceType::Pawn);
	b.SetBoardPiece(Col::e, Row::one, PieceColor::White, PieceType::King);
	game.setBoard(b);
	PrintBoard(game);

	std::string turn = "";
	switch (game.getTurn())
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
	Piece p = b.BoardState[(int)f.row][(int)f.col];
	
	BoardLocation t = readInMove(to);
	b.MakeMove(f, t, p);

	Point pFrom((int)f.row, (int)f.col);
	Point pTo((int)t.row, (int)t.col);
	
	if (game.ValidateMove(pFrom, pTo).valid)
		game.setBoard(b);
	else
		std::cout << "Move is invalid! " << game.ValidateMove(pFrom, pTo).reason << "\n";
	
	PrintBoard(game);

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
