/*************************************************************************************************************************************
 * common.h - definitions shared by entire project
 *************************************************************************************************************************************/
#pragma once

// standard header files
#include <cstdint>

// project header files

// type definitions
typedef uint16_t U16;											// type definition for 16 bit binary string
typedef uint32_t U32;											// type definition for 32 bit binary string
typedef uint64_t U64;											// type definition for 64 bit binary string

// definitions
#define BOARDLEN 64												// assumes a 0..63 board representation
#define MAX_CMD_BUFF 256										// console command input buffer

// enumerations
enum ENUM_CMDS													// console command translation
{
	uci=0,															// UCI compliant commands
	debug,
	isready,
	setoption,
	reg,
	ucinewgame,
	position,
	go,
	stop,
	ponderhit,
	quit,
	unknown=100,													// standalone commands
	display,
	loadfen,
	movelist,
	savefen
};

enum ENUM_PIECE													// chess pieces
{
	king=0,
	queen,
	rook,
	bishop,
	knight,
	pawn
};

enum ENUM_SIDE													// board side
{
	white=0,
	black,
	both
};