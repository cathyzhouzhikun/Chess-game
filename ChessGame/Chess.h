#pragma once
#include <string>


namespace Chess
{
	enum class PieceColor { None, White, Black };
	enum class PieceType { Empty, Pawn, Rook, Knight, Bishop, Queen, King };
	enum class Col { a, b, c, d, e, f, g, h };
	enum class Row { eight, seven, six, five, four, three, two, one };

	struct Validity
	{
		bool valid;
		std::string reason;

		Validity(bool v, std::string r)
		{
			valid = v;
			reason = r;
		}
	};

	struct Piece
	{
		PieceColor color;
		PieceType type;
		bool HasMoved;

		Piece()
		{
			color = PieceColor::None;
			type = PieceType::Empty;
			HasMoved = false;
		}

		Piece(PieceColor c, PieceType t)
		{
			color = c;
			type = t;
			HasMoved = false;
		}
	};

	struct Point
	{
		int x;
		int y;
		Point()
		{
			x = 0;
			y = 0;
		}
		Point(int x1, int y1)
		{
			x = x1;
			y = y1;
		}
	};

	struct BoardLocation
	{
		Col col;
		Row row;

		BoardLocation(Col c, Row r)
		{
			col = c;
			row = r;
		}
	};

	struct Move
	{
		Point from;
		Point to;
		Piece piece;

		Move()
		{
			from = Point();
			to = Point();
			piece = Piece();
		}

		Move(Point f, Point t, Piece p)
		{
			from = f;
			to = t;
			piece = p;
		}
	};



}