/*************************************************************************************************************************************
 * Node.cpp - code for Node class object
 *************************************************************************************************************************************/

// standard header files
#include <sstream>
using namespace std;

// project header files
#include "bitoperations.h"										// definitions of common functions for bitwise operations
#include "conversions.h"										// definitions of common functions for converting indexes between formats
#include "extglobal.h"											// external definitions for global variables
#include "Node.h"

/*************************************************************************************************************************************
 * constructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 112   10/14/2012   SDW   initial coding
 *************************************************************************************************************************************/
Node::Node(void)
{
	//Fullmove_ = -1;												// set Fullmove_ to indicate empty node
	return;
}

/*************************************************************************************************************************************
 * destructor
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 1xx   xx/xx/2012   SDW   initial coding
 *************************************************************************************************************************************/
Node::~Node(void)
{
}

/*************************************************************************************************************************************
 * ApplyMove - apply supplied move to current position
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool Node::ApplyMove(string move)
{
	// local variables
	int fromsquare, tosquare;									// offsets for from- and to-squares

	// initial setup
	
	
	if (move == "O-O")											// if kingside castle
	{
		CastleKingside(SideToMove());								// process castle
		if (SideToMove() == white)									// if white
			ChangeFlag(WHITE_KINGSIDE);									// switch castling flag
		else														// if black
			ChangeFlag(BLACK_KINGSIDE);									// switch castling flag
	}
	else
		if (move == "O-O-O")									// if queenside castle
		{
			CastleQueenside(SideToMove());							// process castle
			if (SideToMove() == white)								// if white
				ChangeFlag(WHITE_QUEENSIDE);							// switch castling flag
			else													// if black
				ChangeFlag(BLACK_KINGSIDE);								// switch castling flag
		}
		else													// for piece moves
		{
			fromsquare = NoteToOff(move.substr(0,2));				// convert notation of from-square to offset
			tosquare = NoteToOff(move.substr(2,2));					// convert notation of to-square to offset
			if ((GetPiece(fromsquare)&&TEST_PAWN)||(GetPiece(tosquare)>0))	// if pawn move or capture
				Halfmove_ = 0;													// then reset halfmove clock
			else 
				Halfmove_++;													// else increment halfmove
			MovePiece(fromsquare, tosquare);						// make the specified move
		}




	// final steps
	if (SideToMove() == black)									// if moving piece is black
		Fullmove_++;												// then increment full move counter
	ChangeFlag(WHITE_TO_MOVE);									// switch side-to-move flag

	return true;
}

/*************************************************************************************************************************************
 * Clear - clear node representation
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   10/10/2015   SDW   initial coding
 *************************************************************************************************************************************/
void Node::Clear(void)
{
	// local variables

	// process
	Fullmove_ = Halfmove_ = -1;									// clear move values

	return;
}

/*************************************************************************************************************************************
 * FormatFullmove - retrieve FEN string based on data member
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/29/2015   SDW   initial coding
 *************************************************************************************************************************************/
string Node::FormatFullmove(void)
{
	//local variables
	string FENrec;
	stringstream buffer;                                        // conversion buffer

	// translate data member into string format
	buffer << Fullmove_;
    FENrec += buffer.str();

	return FENrec;
}

/*************************************************************************************************************************************
 * FormatHalfmove - retrieve FEN string based on data member
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/29/2015   SDW   initial coding
 *************************************************************************************************************************************/
string Node::FormatHalfmove(void)
{
	//local variables
	string FENrec;
	stringstream buffer;                                        // conversion buffer

	// translate data member into string format
	buffer << Halfmove_;
    FENrec += buffer.str();

	return FENrec;
}

/*************************************************************************************************************************************
 * GetFEN - retrieve FEN string based on object
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/29/2015   SDW   initial coding
 *************************************************************************************************************************************/
string Node::GetFEN(void)
{
	// local variables
	string FENrec;

	// string together position members into single FEN format
	FENrec += FormatBoard();
	FENrec += " ";
	FENrec += FormatSide();
	FENrec += " ";
	FENrec += FormatCastling();
	FENrec += " ";
	FENrec += FormatEP();
	FENrec += " ";
	FENrec += FormatHalfmove();
	FENrec += " ";
	FENrec += FormatFullmove();

	return FENrec;
}

/*************************************************************************************************************************************
 * LoadFEN - load position based on FEN string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool Node::LoadFEN(string FENrec)
{
	// local variables
	stringstream ss (stringstream::in | stringstream::out);		// parsing stringstream
	string buffer;												// current token

	// parse FENrec and load into top of tree
	ss << FENrec;												// load parsing stringstream
	ss >> buffer;												// load both board representations
	LoadBoard(buffer);
//TODO 8 LoadBitsets();
	ss >> buffer;												// set active color
	LoadSide(buffer);
	ss >> buffer;												// set castling availability
	LoadCastling(buffer);
	ss >> buffer;												// set target
	LoadEP(buffer);
	ss >> buffer;												// set halfmove
	LoadHalfmove(buffer);
	ss >> buffer;												// set fullmove
	LoadFullmove(buffer);
	CalcMaterial();												// load material balance

	return true;
}

/*************************************************************************************************************************************
 * LoadFullmove	- load fullmove counter based on FEN string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/29/2012   SDW   initial coding
 *************************************************************************************************************************************/
void Node::LoadFullmove(string FENrec)
{
	// local variables
	stringstream buffer;

	// process
	buffer << FENrec;
	buffer >> Fullmove_;
	return;
}

/*************************************************************************************************************************************
 * LoadHalfmove - load halfmove counter based on FEN string
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/29/2012   SDW   initial coding
 *************************************************************************************************************************************/
void Node::LoadHalfmove(string FENrec)
{
	// local variables
	stringstream buffer;

	// process
	buffer << FENrec;
	buffer >> Halfmove_;
	return;
}

/*************************************************************************************************************************************
 * Reset - reset Node to initial board position
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool Node::Reset(void)
{
	// local variables

	// process
	LoadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");	// set board position to initial values
//TODO 5 other node variables

	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

///*************************************************************************************************************************************
// * DisplayPosition - retrieve string to display position on console
// *
// * VRM      Date      By    Description
// * ===   ==========   ===   ==========================================================================================================
// * 100   08/31/2012   SDW   initial coding
// *************************************************************************************************************************************/
//string Node::DisplayPosition(void)
//{
//	// local variables
//	string displayrec;											// string for display record
//
//	//process
//	displayrec = FormatDisplay();									// start with board representation
//	displayrec += "\nside to move: ";
//	displayrec += FormatSide();
//	displayrec += "\ncastling flags: ";
//	displayrec += FormatCastling();
//	displayrec += "\nEP target: ";
//	displayrec += FormatEP();
//	displayrec += "\nHalfmove: ";
//	displayrec += FormatHalfmove();
//	displayrec += "\nFullmove: ";
//	displayrec += FormatFullmove();
//	displayrec += "\nMaterial: ";
//	displayrec += FormatMaterial();
//	displayrec += "\n\n";
//
//	return displayrec;
//}
//
//
///*************************************************************************************************************************************
// * FormatMaterial - retrieve current material value of position
// *
// * VRM      Date      By    Description
// * ===   ==========   ===   ==========================================================================================================
// * 100   08/31/2012   SDW   initial coding
// * 112   09/26/2012   SDW   converted _itoa_s to stringstream
// *************************************************************************************************************************************/
//string Node::FormatMaterial(void)
//{
//	//local variables
//	string displayrec;
//	stringstream buffer;                                        // conversion buffer
//
//	// translate data member into string format
//	buffer << Material_;
//    displayrec += buffer.str();
//
//	return displayrec;
//}
//
///*************************************************************************************************************************************
// * GenerateMoves - generate move list from current position
// *
// * VRM      Date      By    Description
// * ===   ==========   ===   ==========================================================================================================
// * 112   10/17/2012   SDW   initial coding
// * 113   xx/xx/2012   SDW   add support for king move generation (w/o castling)
// *************************************************************************************************************************************/
//Movelist* Node::GenerateMoves(void)
//{
//	// local variables
//	Movelist* top;												// top of Movelist
//	Movelist* thismove;											// pointer to move being appended to list
//	U64 ownpieces;												// temporary bitmap of own pieces
//	U64 candidates;												// candidate targets bitmap
//	int origin, target;											// location of origin and target squares
//
//	// process
//	top = NULL;													// initialize movelist
//
//	if (IsWhiteMove())											// load own and notown bitsets depending on side to move
//	{
//		ownpieces = WhitePieces_;
//		NotOwnPieces_ = ~WhitePieces_;
//	}
//	else
//	{
//		ownpieces = BlackPieces_;
//		NotOwnPieces_ = ~BlackPieces_;
//	}
//
//	while (ownpieces)											// cycle through own pieces
//	{
//		origin = BitscanForward(ownpieces);							// for each piece of current side
//		ownpieces &= ~TABLE_INDEX_BITSET[origin];					// clear origin bit
//		switch (Squares_[origin])									// generate target bitmap appropriate to piece type
//		{
//			case TYPE_WHITE_KING:
//			case TYPE_BLACK_KING:
//				candidates = GenMoveKing(origin);						// generate king moves
//				break;
//			case TYPE_WHITE_KNIGHT:
//			case TYPE_BLACK_KNIGHT:
//				candidates = GenMoveKnight(origin);						// generate knight moves
//				break;
//			case TYPE_EMPTY:
//			case TYPE_WHITE_PAWN:
//			case TYPE_WHITE_BISHOP:
//			case TYPE_WHITE_ROOK:
//			case TYPE_WHITE_QUEEN:
//			case TYPE_BLACK_PAWN:
//			case TYPE_BLACK_BISHOP:
//			case TYPE_BLACK_ROOK:
//			case TYPE_BLACK_QUEEN:
//				candidates = 0;											// set candidates to empty
//				break;
//		}
//		while (candidates)											// use target to append moves to movelist
//		{
//			target = BitscanForward(candidates);						// for each square of candidates list
//			candidates &= ~TABLE_INDEX_BITSET[target];					// clear target bit
//			if ((Squares_[origin] == TYPE_WHITE_PAWN)&&(TABLE_INDEX_RANK[target]==8))	// for promoting white pawns
//			{
//				thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_WHITE_QUEEN);
//				thismove->LoadNext(top);
//				top = thismove;
//				thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_WHITE_ROOK);
//				thismove->LoadNext(top);
//				top = thismove;
//				thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_WHITE_BISHOP);
//				thismove->LoadNext(top);
//				top = thismove;
//				thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_WHITE_KNIGHT);
//				thismove->LoadNext(top);
//				top = thismove;
//			}
//			else
//				if ((Squares_[origin] == TYPE_BLACK_PAWN)&&(TABLE_INDEX_RANK[target]==1))	// for promoting black pawns
//				{
//					thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_BLACK_QUEEN);
//					thismove->LoadNext(top);
//					top = thismove;
//					thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_BLACK_ROOK);
//					thismove->LoadNext(top);
//					top = thismove;
//					thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_BLACK_BISHOP);
//					thismove->LoadNext(top);
//					top = thismove;
//					thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_BLACK_KNIGHT);
//					thismove->LoadNext(top);
//					top = thismove;
//				}
//				else																		// for all other moves
//				{
//					thismove = new Movelist(origin,Squares_[origin],target,Squares_[target],TYPE_EMPTY);
//					thismove->LoadNext(top);
//					top = thismove;
//				}
//		}
//	}
//
//
//	// sort movelist by material, piece position
//
//    return top;													// return pointer to top of movelist
//}
//
///*************************************************************************************************************************************
// * GenMoveKing - generate target squares for king
// *
// * accepts offset into board as input, returns bitmap of target squares
// * accesses Node variables as needed so nothing else needs to be passed
// *
// * VRM      Date      By    Description
// * ===   ==========   ===   ==========================================================================================================
// * 113   10/24/2012   SDW   initial coding
// *************************************************************************************************************************************/
//U64 Node::GenMoveKing(int offset)
//{
//	// add support for castling
//	return TABLE_ATTACKS_KING[offset] & NotOwnPieces_;
//}
//
///*************************************************************************************************************************************
// * GenMoveKnight - generate target squares for knight
// *
// * accepts offset into board as input, returns bitmap of target squares
// * accesses Node variables as needed so nothing else needs to be passed
// *
// * VRM      Date      By    Description
// * ===   ==========   ===   ==========================================================================================================
// * 112   09/18/2012   SDW   initial coding
// *************************************************************************************************************************************/
//U64 Node::GenMoveKnight(int offset)
//{
//	return TABLE_ATTACKS_KNIGHT[offset] & NotOwnPieces_;
//}
//
//
///*************************************************************************************************************************************
// * IsEmptyNode - test if node is empty
// *
// * VRM      Date      By    Description
// * ===   ==========   ===   ==========================================================================================================
// * 112   10/14/2012   SDW   initial coding
// *************************************************************************************************************************************/
//bool Node::IsEmptyNode(void)
//{
//	if (Fullmove_ == -1)
//		return true;
//	else
//		return false;
//}
//
///*************************************************************************************************************************************
// * LoadBitsets - load bitsets based on board
// *
// * VRM      Date      By    Description
// * ===   ==========   ===   ==========================================================================================================
// * 100   08/30/2012   SDW   initial coding
// * 111   09/01/2012   SDW   add process to load other summary bitsets
// * 111   09/03/2012   SDW   replace general shifts with table lookups
// * 112   09/12/2012   SDW   commented out bitsets other than white and black
// *************************************************************************************************************************************/
//void Node::LoadBitsets(void)
//{
//	// local variables
//	int i, j;													// loop counters
//
//
//	// clear out the current contents of Bitsets
//	for (i = white; i <= black; i++)							// for each side
//		for (j = king; j <= pawn; j++)							// for each piece
//			Piecesets_[i][j] ^= Piecesets_[i][j];					// clear bits in binary string
//
//	// process the contents of the board
//	for (i = 0; i < BOARDLEN; i++)
//	{
//		switch (Squares_[i])									// act on piece in square
//		{
//			case TYPE_WHITE_KING:
//				Piecesets_[white][king] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_WHITE_QUEEN:
//				Piecesets_[white][queen] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_WHITE_ROOK:
//				Piecesets_[white][rook] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_WHITE_BISHOP:
//				Piecesets_[white][bishop] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_WHITE_KNIGHT:
//				Piecesets_[white][knight] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_WHITE_PAWN:
//				Piecesets_[white][pawn] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_BLACK_KING:
//				Piecesets_[black][king] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_BLACK_QUEEN:
//				Piecesets_[black][queen] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_BLACK_ROOK:
//				Piecesets_[black][rook] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_BLACK_BISHOP:
//				Piecesets_[black][bishop] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_BLACK_KNIGHT:
//				Piecesets_[black][knight] |= TABLE_INDEX_BITSET[i];
//				break;
//			case TYPE_BLACK_PAWN:
//				Piecesets_[black][pawn] |= TABLE_INDEX_BITSET[i];
//				break;
//		}
//	}
//
//	// load WhitePieces and BlackPieces bitsets
//	WhitePieces_ ^= WhitePieces_;									// clear current bits in bitset
//	BlackPieces_ ^= BlackPieces_;
//	for (i=king;i<=pawn;i++)										// loop through Piecesets
//	{
//		WhitePieces_ |= Piecesets_[white][i];							// accumulate bits for white pieces
//		BlackPieces_ |= Piecesets_[black][i];							// accumulate bits for black pieces
//	}
//
//	// load remaining bitsets
//	NoPieces_ = ~(WhitePieces_ | BlackPieces_);
//
//	return;
//}
//
//

//
//
//

