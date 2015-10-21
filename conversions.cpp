/*************************************************************************************************************************************
 * conversions.cpp - common functions for converting indexes between formats
 *************************************************************************************************************************************/

// standard header files
#include <string>
#include <sstream>
using namespace std;

// project header files
#include "extglobal.h"

/*************************************************************************************************************************************
 * NoteToOff - convert algebraic notation to board offset
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/20/2015   SDW   initial coding
 *************************************************************************************************************************************/
int NoteToOff(string notation)
{
	// local variables
	int offset = 0;
	stringstream buffer;

	// perform conversion
	buffer << notation[1];
	buffer >> offset;
	offset = (offset-1) * 8 + (notation[0] - 'a');

	return offset;
}

/*************************************************************************************************************************************
 * OffToNote - convert offset to algebraic notation
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/20/2015   SDW   initial coding
 *************************************************************************************************************************************/
string OffToNote(int offset)
{
	// local variables
	string notation;

	// perform conversion
	notation = TABLE_NAMES_FILES[TABLE_INDEX_FILE[offset]];
	notation += TABLE_NAMES_RANKS[TABLE_INDEX_RANK[offset]];

	return notation;
}
