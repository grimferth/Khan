/*************************************************************************************************************************************
 * Position.h - definitions for Position object
 *************************************************************************************************************************************/
#pragma once

/***************************************************************************************************************
 * mapping for the flag data element
 *
 * format - IxxSqkQK
 *
 * where -
 *			qkQk		castling flags (1=available)
 *			S			side to move (1=white)
 *			xx			unused
 *			I			invalid position (1=yes)
 *
 ***************************************************************************************************************/

// standard header files

// project header files
#include "Board.h"
#include "common.h"												// definitions shared by entire project

/***************************************************************************************************************
 * symbolic definitions
 ***************************************************************************************************************/

#define WHITE_KINGSIDE 0x01										// mask 0000 0001
#define WHITE_QUEENSIDE 0x02									// mask 0000 0010
#define BLACK_KINGSIDE 0x04										// mask 0000 0100
#define BLACK_QUEENSIDE 0x08									// mask 0000 1000
#define ANY_CASTLE 0x0F											// mask 0000 1111
#define WHITE_TO_MOVE 0x10										// mask 0001 0000
#define INVALID_POSITION 0x80									// mask 1000 0000
#define CLEAR_POSITION 0x00										// mask 0000 0000

/***************************************************************************************************************
 * class definition
 ***************************************************************************************************************/
class Position :
	public Board
{
private:
	// private data members
	int EPtarget_;												// offset to en passant target square
	U16 Flags_;													// misc flags
	// private method members
	void Clear(void);											// clear position representation

protected:
	// protected data members
	// protected method members
	void ChangeFlag(U16);										// switch setting on flag
	string FormatCastling(void);								// retrieve FEN string based on data member
	string FormatEP(void);										// retrieve FEN string based on data member
	string FormatSide(void);									// retrieve FEN string based on data member
	void LoadCastling(string);									// set castling flags based on FEN string
	void LoadEP(string);										// set EP target square based on FEN string
	void LoadSide(string);										// set side to move flag based on FEN string
	bool SideToMove(void);										// return side to move

public:
	// public data members
	// public method members
	Position(void);
	~Position(void);
    //bool IsWhiteMove(void);									// test if white is side to move
};

