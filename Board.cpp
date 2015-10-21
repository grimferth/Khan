/*************************************************************************************************************************************
 * Board.cpp - code for Board class object
 *************************************************************************************************************************************/

// standard header files
//#include <string>
#include <sstream>
using namespace std;

// project header files
#include "Board.h"												// definitions for Board object
#include "conversions.h"										// definitions of common functions for converting indexes between formats
#include "extglobal.h"											// external definitions for global variables

/*************************************************************************************************************************************
 * constructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   xx/xx/2012   SDW   initial coding
 *************************************************************************************************************************************/
Board::Board(void)
{
}

/*************************************************************************************************************************************
 * destructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   xx/xx/2012   SDW   initial coding
 *************************************************************************************************************************************/
Board::~Board(void)
{
}

/*************************************************************************************************************************************
 * CalcMaterial	- calculate material based on current board position
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   10/10/2015   SDW   initial coding
 *************************************************************************************************************************************/
void Board::CalcMaterial(void)
{
	// local variables
	int i;														// loop counter

	// process
	Material_ = 0;												// clear material value
	for (i = 0; i < BOARDLEN; i++)								// loop through board
		Material_ += TABLE_VALUES_PIECES[Squares_[i]];				// adding value of piece in current square

	return;
}

/*************************************************************************************************************************************
 * CastleKingside - move for kingside castle
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   10/14/2015   SDW   initial coding
 *************************************************************************************************************************************/
void Board::CastleKingside(bool side)
{
	if (side == white)											// if side is white
	{
		Squares_[NoteToOff("g1")] = TYPE_WHITE_KING;				// king moved to g1
		Squares_[NoteToOff("f1")] = TYPE_WHITE_ROOK;				// rook moved to f1
		Squares_[NoteToOff("e1")] = TYPE_EMPTY;						// empty e1
		Squares_[NoteToOff("h1")] = TYPE_EMPTY;						// empty h1
	}
	else														// if side is black
	{
		Squares_[NoteToOff("g8")] = TYPE_BLACK_KING;				// king moved to g8
		Squares_[NoteToOff("f8")] = TYPE_BLACK_ROOK;				// rook moved to f8
		Squares_[NoteToOff("e8")] = TYPE_EMPTY;						// empty e8
		Squares_[NoteToOff("h8")] = TYPE_EMPTY;						// empty h8
	}
	return;
}

/*************************************************************************************************************************************
 * CastleQueenside - move for queenside castle
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   10/14/2015   SDW   initial coding
 *************************************************************************************************************************************/
void Board::CastleQueenside(bool side)
{
	if (side == white)											// if side is white
	{
		Squares_[NoteToOff("c1")] = TYPE_WHITE_KING;				// king moved to c1
		Squares_[NoteToOff("d1")] = TYPE_WHITE_ROOK;				// rook moved to d1
		Squares_[NoteToOff("e1")] = TYPE_EMPTY;						// empty e1
		Squares_[NoteToOff("a1")] = TYPE_EMPTY;						// empty a1
	}
	else														// if side is black
	{
		Squares_[NoteToOff("c8")] = TYPE_BLACK_KING;				// king moved to g8
		Squares_[NoteToOff("d8")] = TYPE_BLACK_ROOK;				// rook moved to f8
		Squares_[NoteToOff("e8")] = TYPE_EMPTY;						// empty e8
		Squares_[NoteToOff("a8")] = TYPE_EMPTY;						// empty h8
	}
	return;
}

/*************************************************************************************************************************************
 * Clear - clear board representation
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/19/2015   SDW   initial coding
 *************************************************************************************************************************************/
void Board::Clear(void)
{
	// local variables
	int i;													// loop counter

	// process
	for (i = 0; i < BOARDLEN; i++)							// loop through Mailbox_ member
		Squares_[i] = TYPE_EMPTY;								// set to empty
	Material_ = 0;											// reset material value

	return;
}

/*************************************************************************************************************************************
 * FormatBoard	- retrieve FEN string based on data member
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/29/2015   SDW   initial coding
 *************************************************************************************************************************************/
string Board::FormatBoard(void)
{
	//local variables
	string FENrec;												// string for FEN record
	stringstream buffer;                                        // conversion buffer
	int rank, file;												// loop counters
	int offset;													// index into mailbox
	int counter;												// empty square counter

	// process
	for (rank = 8; rank > 0; rank--)							// loop through ranks h to a
	{
		counter = 0;												// reset counter
		for (file = 1; file < 9; file++)							// loop through files 1 to 8
		{
			offset = TABLE_INDEX_OFFSET[file][rank];					// retrieve offset into board
			if (Squares_[offset] == TYPE_EMPTY)							// if square is empty
				counter++;													// then increment counter
			else
			{
				if (counter > 0)											// else if counter greater than 0
				{
				    buffer.str("");												// clear buffer             alt code = .str().clear();
					buffer << counter;                                          // write count of empty squares to FEN rec
				    FENrec += buffer.str();
					counter = 0;												// reset count
				}
				FENrec += TABLE_NAMES_PIECES[Squares_[offset]];
			}
		}
		if (counter > 0)											// empty squares at end?
		{
			buffer.str("");												// clear buffer
		    buffer << counter;                                          // write count of empty squares to FEN rec
            FENrec += buffer.str();
		}
		if (rank > 1)												// if not last rank
			FENrec += "/";												// then write seperator
	};

	return FENrec;
}

/*************************************************************************************************************************************
 * GetPiece - return value of specified square
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   10/16/2015   SDW   initial coding
 *************************************************************************************************************************************/
U16 Board::GetPiece(int offset)
{
	return Squares_[offset];
}


/*************************************************************************************************************************************
 * LoadBoard - load board based on FEN string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
void Board::LoadBoard(string FENrec)
{
	// local variables
	int i;														// loop counters
	int file, rank, offset;										// ptrs into chess board

	// process the FEN string
	Clear();													// clear the Squares_ member
	file = 1;													// starting point for rank and file
	rank = 8;
	for (i = 0; i < FENrec.size(); i++)							// cycle through FEN record, stopping when reaching end of string
	{
		offset = TABLE_INDEX_OFFSET[file][rank];					// retrieve offset
		switch (FENrec[i])											// handle current char in FEN record
		{
			case 'K':													// White king
				Squares_[offset] = TYPE_WHITE_KING;
				break;
			case 'Q':													// White queen
				Squares_[offset] = TYPE_WHITE_QUEEN;
				break;
			case 'R':													// White rook
				Squares_[offset] = TYPE_WHITE_ROOK;
				break;
			case 'B':													// White bishop
				Squares_[offset] = TYPE_WHITE_BISHOP;
				break;
			case 'N':													// White knight
				Squares_[offset] = TYPE_WHITE_KNIGHT;
				break;
			case 'P':													// White pawn
				Squares_[offset] = TYPE_WHITE_PAWN;
				break;
			case 'k':													// Black king
				Squares_[offset] = TYPE_BLACK_KING;
				break;
			case 'q':													// Black queen
				Squares_[offset] = TYPE_BLACK_QUEEN;
				break;
			case 'r':													// Black rook
				Squares_[offset] = TYPE_BLACK_ROOK;
				break;
			case 'b':													// Black bishop
				Squares_[offset] = TYPE_BLACK_BISHOP;
				break;
			case 'n':													// Black knight
				Squares_[offset] = TYPE_BLACK_KNIGHT;
				break;
			case 'p':													// Black pawn
				Squares_[offset] = TYPE_BLACK_PAWN;
				break;
			case '/':													// rank separator
				rank--;
				file = 0;
				break;
			case '1':													// empty spaces
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				file += (int) FENrec[i] - '1';
				break;
		}
		file++;
	}

	return;
}

/*************************************************************************************************************************************
 * MovePiece - move piece and update material
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   10/11/2015   SDW   initial coding
 *************************************************************************************************************************************/
void Board::MovePiece(int fromsquare, int tosquare)
{
	// local variables
	
	// process
//TODO 10
	Material_ -= TABLE_VALUES_PIECES[Squares_[tosquare]];		// subtract value of piece in specified square
	Squares_[tosquare] = Squares_[fromsquare];					// copy piece fromsquare tosquare
	Squares_[fromsquare] = TYPE_EMPTY;							// empty fromsquare

	return;
}

/*************************************************************************************************************************************
 * PieceColor - color of piece in specified square
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   10/11/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool Board::PieceColor(int offset)
{
	// local variables
	U16 temp;
	
	// process
	temp = Squares_[offset] & TEST_BLACK;
	if (temp == white)
		return white;
	else 
		return black;

}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------




//

//
///*************************************************************************************************************************************
// * FormatDisplay - retrieve string to display board on console
// *
// * VRM      Date      By    Description
// * ===   ==========   ===   ==========================================================================================================
// * 100   08/31/2012   SDW   initial coding
// * 111   09/03/2012   SDW   moved table to extglobal
// *************************************************************************************************************************************/
//string Board::FormatDisplay(void)
//{
//	//local variables
//	string displayrec;											// string for display record
//	int rank, file;												// loop counters
//	int offset;													// index into mailbox
//
//	// process
//	displayrec = "\n";											// start with new line
//	for (rank = 8; rank > 0; rank--)							// loop through ranks h to a
//	{
//		for (file = 1; file < 9; file++)							// loop through files 1 to 8
//		{
//			offset = TABLE_INDEX_OFFSET[file][rank];					// retrieve offset into board
//			displayrec += TABLE_NAMES_PIECES[Squares_[offset]];			// add char representing piece
//		}
//		if (rank > 1)												// if not last rank
//			displayrec += "\n";											// then write newline
//	};
//	displayrec += "\n";											// end with new line
//
//	return displayrec;
//}
//

//
