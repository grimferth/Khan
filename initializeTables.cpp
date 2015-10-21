/*************************************************************************************************************************************
 * initializeTables.cpp - initialize global tables
 *************************************************************************************************************************************/

// standard header files

// project header files
#include "bitoperations.h"										// definitions of common functions for bitwise operations
#include "common.h"												// definitions shared by entire project
#include "extglobal.h"											// external definitions for global variables

/*************************************************************************************************************************************
 * initializeTables - initialize global tables
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/19/2015   SDW   initial coding
 *************************************************************************************************************************************/
void initializeTables(void)
{
	// local variables
	int file, rank, offset;										// loop counters
	int tempfile, temprank;										// temporary variables

	// TABLE_INDEX_BITSET is used to translate a board offset to the corresponding bitset
	TABLE_INDEX_BITSET[0] = LSB;								// use least significant bit for 0 offset
	for (offset = 1; offset < 64; offset++)						// looping through the rest of the board
	{
		TABLE_INDEX_BITSET[offset] = TABLE_INDEX_BITSET[offset-1] << 1;		// load left-shifted map
	}

	// TABLE_INDEX_OFFSET is used to translate [file][rank] to board offset
	// TABLE_INDEX_FILE is used to lookup the file associated with a given board offset
	// TABLE_INDEX_RANK is used to lookup the rank associated with a given board offset
	// note that both file and rank are assumed to be 1-8 (not starting at 0)
	for (rank = 1 ; rank < 9; rank++)							// looping through ranks
		for (file = 1 ; file < 9; file++)						// looping through files
		{
			TABLE_INDEX_OFFSET[file][rank] = (rank-1) * 8 + file - 1;	// calculate and load offset
			TABLE_INDEX_FILE[TABLE_INDEX_OFFSET[file][rank]] = file;	// load file
			TABLE_INDEX_RANK[TABLE_INDEX_OFFSET[file][rank]] = rank;	// load rank
		}

	// initialize attack tables to zeroes
	for (offset = 0 ; offset < 64; offset++)					// looping through board
	{
		TABLE_ATTACKS_KING[offset] = 0x0;							// lookup table for king attacks
		TABLE_ATTACKS_KNIGHT[offset] = 0x0;							// lookup table for knight attacks
	}

	// load king attack table
	for (offset = 0; offset < 64; offset++)						// looping through board
	{
		file = TABLE_INDEX_FILE[offset];							// look up file and rank
		rank = TABLE_INDEX_RANK[offset];
		tempfile = file - 1;										// add bitmap for [file-1][rank-1] if valid
		temprank = rank - 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KING[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file;										// add bitmap for [file][rank-1] if valid
		temprank = rank - 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KING[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file + 1;										// add bitmap for [file+1][rank-1] if valid
		temprank = rank - 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KING[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file - 1;										// add bitmap for [file-1][rank] if valid
		temprank = rank;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KING[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file + 1;										// add bitmap for [file+1][rank] if valid
		temprank = rank;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KING[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file - 1;										// add bitmap for [file-1][rank+1] if valid
		temprank = rank + 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KING[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file;										// add bitmap for [file][rank+1] if valid
		temprank = rank + 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KING[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file + 1;										// add bitmap for [file+1][rank+1] if valid
		temprank = rank + 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KING[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
       }

	// load knight attack table
	for (offset = 0; offset < 64; offset++)						// looping through board
	{
		file = TABLE_INDEX_FILE[offset];							// look up file and rank
		rank = TABLE_INDEX_RANK[offset];
		tempfile = file - 2;										// add bitmap for [file-2][rank+1] if valid
		temprank = rank + 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KNIGHT[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file - 1;										// add bitmap for [file-1][rank+2] if valid
		temprank = rank + 2;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KNIGHT[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file + 1;										// add bitmap for [file+1][rank+2] if valid
		temprank = rank + 2;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KNIGHT[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file + 2;										// add bitmap for [file+2][rank+1] if valid
		temprank = rank + 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KNIGHT[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file + 2;										// add bitmap for [file+2][rank-1] if valid
		temprank = rank - 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KNIGHT[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file + 1;										// add bitmap for [file+1][rank-2] if valid
		temprank = rank - 2;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KNIGHT[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file - 1;										// add bitmap for [file-1][rank-2] if valid
		temprank = rank - 2;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KNIGHT[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
		tempfile = file - 2;										// add bitmap for [file-2][rank-1] if valid
		temprank = rank - 1;
		if ((tempfile >= 1) & (tempfile <= 8) & (temprank >= 1) & (temprank <= 8))
			TABLE_ATTACKS_KNIGHT[offset] |= TABLE_INDEX_BITSET[TABLE_INDEX_OFFSET[tempfile][temprank]];
       }

	// reset top of search tree
	treeTop.Reset();

	return;
}
