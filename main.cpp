/*************************************************************************************************************************************
 * Name:        main.cpp
 * Purpose:     entry point into the Khan project
 * Licence:     GNU GPL v3.0 (29 June 2007)
 * Copyright:   2015(c) Stephen Wunschel
 *************************************************************************************************************************************/

// standard header files

// project header files
#include "initializeTables.h"									// definitions for initialize global tables
#include "global.h"												// definitions for global variables
#include "main.h"												// definitions for main program
#include "uci.h"												// definitions for C routines to handle all interactions with GUI front-end

/*************************************************************************************************************************************
 * main - project entry point
 *
 * initialize global variables and then call UCI loop
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/19/2015   SDW   initial coding
 *************************************************************************************************************************************/
int main(int argc, char *argv[])
{
	initializeTables();											// initialize global tables
	commandLoop();												// enter command loop
    return 0;
}

