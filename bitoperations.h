/*************************************************************************************************************************************
 * bitoperations.h - definitions of common functions for bitwise operations 
 *************************************************************************************************************************************/
#pragma once

// standard header files
#include "common.h"												// definitions shared by entire project

// project header files

/***************************************************************************************************************
 * symbolic definitions
 ***************************************************************************************************************/
#define LSB (U64)0x0000000000000001								// least significant bit
#define MSB (U64)0xF000000000000000								// most significant bit

/***************************************************************************************************************
 * function declarations
 ***************************************************************************************************************/
int BitscanForward(U64);										// find the index of the least significant 1 bit (LS1B)

//int PopCount(void);											// count the number of bits set
//U64 GetMap(void);											// retrieve binary string
//string GetNotation(void);									// retrieve algebraic notation from bitboard
//bool IsEmpty(void);											// test if string is empty
//bool LoadNotation(string);									// load bitboard using string in algebraic notation

//bool SetRankFile(int,int);									// set bit using rank and file