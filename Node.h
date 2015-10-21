/*************************************************************************************************************************************
 * Node.h - definitions for Node object
 *************************************************************************************************************************************/
#pragma once

// standard header files
#include <string>
using namespace std;

// project header files
//#include "Movelist.h"
#include "Position.h"

/***************************************************************************************************************
 * symbolic definitions
 ***************************************************************************************************************/

/***************************************************************************************************************
 * class definition
 ***************************************************************************************************************/
class Node :
	public Position
{
private:
	// private data members
	int Fullmove_;												// full move number
	int Halfmove_;												// half move clock
	
//TODO 1 move bitmap board rep to BOARD?
	//U64 Piecesets_[2][6];										// bitmap board representation
	//U64 WhitePieces_;											// bitmap of all white pieces
	//U64 BlackPieces_;											// bitmap of all black pieces
	//U64 NoPieces_;												// bitmap of all squares not occupied by any pieces
	//U64 NotOwnPieces_;											// bitmap of all squares not occupied by own pieces
	// private method members
	void Clear(void);											// clear node representation
	string FormatFullmove(void);								// retrieve FEN string based on data member
	string FormatHalfmove(void);								// retrieve FEN string based on data member
	//string FormatMaterial(void);								// retrieve current material value of position
	//U64 GenMoveKing(int);										// generate target squares for king
	//U64 GenMoveKnight(int);										// generate target squares for knight
	//void LoadBitsets(void);									// load bitsets based on board
	void LoadHalfmove(string);									// load halfmove counter based on FEN string
	void LoadFullmove(string);									// load fullmove counter based on FEN string
	void LoadMaterial(void);									// load material value from current board

protected:
	// protected data members
	// protected method members

public:
	// public data members
	// public method members
	Node(void);
	~Node(void);
	bool ApplyMove(string);										// apply supplied move to current position
	//string DisplayPosition(void);								// retrieve string to display position on console
	//Movelist* GenerateMoves(void);								// generate move list from current position
	string GetFEN(void);										// retrieve FEN string based on object
	//bool IsEmptyNode(void);									// test if node is empty
	bool LoadFEN(string);										// load position based on FEN string
	bool Reset(void);											// reset Node to initial board position
};

