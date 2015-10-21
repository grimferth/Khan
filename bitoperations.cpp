/*************************************************************************************************************************************
 * bitoperations.cpp - code for common functions for bitwise operations
 *************************************************************************************************************************************/

// standard header files

// project header files
#include "bitoperations.h"

/*************************************************************************************************************************************
 * BitscanForward - find the index of the least significant 1 bit (LS1B)
 *
 * De Bruijn Multiplication, see http://chessprogramming.wikispaces.com/BitScan
 * don't use this if bitmap = 0
 * taken from: winglet, copyright © 2011, Stef Luijten
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 112   09/20/2015   SDW   initial coding
 *************************************************************************************************************************************/
int BitscanForward(U64 bitmap)
{
	// local variables
	static const int INDEX64[64] =
	{
		63,  0, 58,  1, 59, 47, 53,  2,
		60, 39, 48, 27, 54, 33, 42,  3,
		61, 51, 37, 40, 49, 18, 28, 20,
		55, 30, 34, 11, 43, 14, 22,  4,
		62, 57, 46, 52, 38, 26, 32, 41,
		50, 36, 17, 19, 29, 10, 13, 21,
		56, 45, 25, 31, 35, 16,  9, 12,
		44, 24, 15,  8, 23,  7,  6,  5
	};
 	static const U64 DEBRUIJN64 = U64(0x07EDD5E59A4E28C2);

	// here you would get a warming: "unary minus operator applied to unsigned type",
	// that's intended and OK so I'll disable it
#pragma warning (disable: 4146)

	// process
	return INDEX64[((bitmap & -bitmap) * DEBRUIJN64) >> 58];
}

