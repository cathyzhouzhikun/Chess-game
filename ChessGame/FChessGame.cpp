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





