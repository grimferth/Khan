/*************************************************************************************************************************************
 * global - definitions for global variables
 *************************************************************************************************************************************/
#pragma once

// standard header files

// project header files
#include "common.h"												// definitions shared by entire project
#include "Node.h"												// 

// declarations

// tables
U64 TABLE_ATTACKS_KING[BOARDLEN];								// lookup table of attack bitmaps for any king
U64 TABLE_ATTACKS_KNIGHT[BOARDLEN];								// lookup table of attack bitmaps for any knight
U64 TABLE_INDEX_BITSET[BOARDLEN];								// lookup table for bitset by offset
int TABLE_INDEX_FILE[BOARDLEN];									// lookup table for file by offset
int TABLE_INDEX_OFFSET[9][9];									// lookup table for offsets by file then rank
int TABLE_INDEX_RANK[BOARDLEN];									// lookup table for rank by offset
char TABLE_NAMES_FILES[] = " abcdefgh";							// lookup table for display labels for files
char TABLE_NAMES_PIECES[] = ".PKN-BRQ-pkn-brq";					// lookup table for FEN name of piece ids
char TABLE_NAMES_RANKS[] = " 12345678";							// lookup table for display labels for ranks
int TABLE_VALUES_PIECES[] =										// lookup table for piece values in centipawns (using TYPE_piece for lookup)
	{
		0,															//  0 - EMPTY
		100,														//  1 - WHITE_PAWN
		9999,														//  2 - WHITE_KING
		260,														//  3 - WHITE_KNIGHT
		0,															//  4 - not used
		300,														//  5 - WHITE_BISHOP
		500,														//  6 - WHITE_ROOK
		900,														//  7 - WHITE_QUEEN
		0,															//  8 - not used
		-100,														//  9 - BLACK_PAWN
		-9999,														// 10 - BLACK_KING
		-260,														// 11 - BLACK_KNIGHT
		0,															// 12 - not used
		-300,														// 13 - BLACK_BISHOP
		-500,														// 14 - BLACK_ROOK
		-900														// 15 - BLACK_QUEEN
	};

// search tree
Node treeTop;													// top of the search tree