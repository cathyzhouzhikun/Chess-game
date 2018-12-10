#pragma once

#include "stdafx.h"
#include <iostream>
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
}

Board Chess::FChessGame::getBoard()
{
	return board;
}

void Chess::FChessGame::setBoard(Board b)
{
	board = b;
}

Validity Chess::FChessGame::move(Point from, Point to, Piece p) {
	Board b_copy = board;
	Validity v = b_copy.ValidateMove(from, to);
	if (!v.valid) {
		std::cout << "Move is invalid! " << v.reason << "\n";
		return v;
	}

	b_copy.MakeMove(from, to, p);

	if (b_copy.CheckForCheck(p.color)) {
		v = Validity(false, "Move puts or keeps your king in check.");
		std::cout << "Move is invalid! " << v.reason << "\n";
		return v;
	}
	std::cout << "Move is valid!\n";
	board.MakeMove(from, to, p);
	return v;
}



