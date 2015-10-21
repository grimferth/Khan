/*************************************************************************************************************************************
 * conversions.h - definitions of common functions for converting indexes between formats
 *************************************************************************************************************************************/
#pragma once

// standard header files
#include <string>
using namespace std;

// project header files
#include "common.h"												// definitions shared by entire project

/***************************************************************************************************************
 * symbolic definitions
 ***************************************************************************************************************/

/***************************************************************************************************************
 * function declarations
 ***************************************************************************************************************/
int NoteToOff(string);										// convert algebraic notation to board offset
string OffToNote(int);										// convert offset to algebraic notation
