/*************************************************************************************************************************************
 * extglobal - external definitions for global variables
 *************************************************************************************************************************************/
#pragma once

// standard header files

// project header files
#include "common.h"												// definitions shared by entire project
#include "Node.h"												// 

// declarations

// tables
extern U64 TABLE_ATTACKS_KING[];								// lookup table of attack bitmaps for any king
extern U64 TABLE_ATTACKS_KNIGHT[];								// lookup table of attack bitmaps for any knight
extern U64 TABLE_INDEX_BITSET[];								// lookup table for bitset by offset
extern int TABLE_INDEX_FILE[];									// lookup table for file by offset
extern int TABLE_INDEX_OFFSET[9][9];							// lookup table for offsets by file then rank
extern int TABLE_INDEX_RANK[];									// lookup table for rank by offset
extern char TABLE_NAMES_FILES[];								// lookup table for display labels for files
extern char TABLE_NAMES_PIECES[];								// lookup table for FEN name of piece ids
extern char TABLE_NAMES_RANKS[];								// lookup table for display labels for ranks
extern int TABLE_VALUES_PIECES[];								// lookup table for piece values in centipawns (using TYPE_piece for lookup)

// search tree
extern Node treeTop;													// top of the search tree
