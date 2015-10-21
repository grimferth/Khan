/*************************************************************************************************************************************
 * Board.h - definitions for Board object
 *************************************************************************************************************************************/
#pragma once

// standard header files
#include <string>
using namespace std;

// project header files
#include "common.h"												// definitions shared by entire project

/***************************************************************************************************************
 * symbolic definitions
 ***************************************************************************************************************/
																// piece identifiers
#define TYPE_EMPTY 0												// mask 0000
#define TYPE_WHITE_PAWN 1											// mask 0001
#define TYPE_WHITE_KING 2											// mask 0010
#define TYPE_WHITE_KNIGHT 3											// mask 0011
#define TYPE_WHITE_BISHOP 5											// mask 0101
#define TYPE_WHITE_ROOK 6											// mask 0110
#define TYPE_WHITE_QUEEN 7											// mask 0111
#define TYPE_BLACK_PAWN 9											// mask 1001
#define TYPE_BLACK_KING 10											// mask 1010
#define TYPE_BLACK_KNIGHT 11										// mask 1011
#define TYPE_BLACK_BISHOP 13										// mask 1101
#define TYPE_BLACK_ROOK 14											// mask 1110
#define TYPE_BLACK_QUEEN 15											// mask 1111

#define TEST_BLACK 8												// mask 1000
#define TEST_PAWN 1                                                 // mask 0001

	// Usefull bitwise properties of this numbering scheme:
	// white = 0..., black = 1..., sliding = .1.., nonsliding = .0..
	// rank/file sliding pieces = .11., diagonally sliding pieces = .1.1
	// pawns and kings (without color bits), are < 3
	// major pieces (without color bits set), are > 5
	// minor and major pieces (without color bits set), are > 2

/***************************************************************************************************************
 * class definition
 ***************************************************************************************************************/
class Board
{
private:
	// private data members
	int Material_;												// material value
	U16 Squares_[BOARDLEN];										// mailbox board representation
	// private method members
	void Clear(void);											// clear board representation

protected:
	// protected data members
	// protected method members
	void CalcMaterial(void);									// calculate Material_ based on current board position
	void CastleKingside(bool);									// move for kingside castle
	void CastleQueenside(bool);									// move for queenside castle
	string FormatBoard(void);									// retrieve FEN string based on data member
	//string FormatDisplay(void);									// retrieve string to display board on console
	U16 GetPiece(int);											// return value of specified square
	void LoadBoard(string);										// load board based on FEN string
	void MovePiece(int, int);									// move piece and update material
	bool PieceColor(int);										// color of piece in specified square

public:
	// public data members
	// public method members
	Board(void);
	~Board(void);
};

