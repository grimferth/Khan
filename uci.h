/*************************************************************************************************************************************
 * uci.h - definitions for C routines to handle all interactions with GUI front-end
 *************************************************************************************************************************************/

#pragma once

// standard header files
#include <string>
using namespace std;

// project header files

// definitions
#define LOGFLAG 1												// switch to control logging of command console

// declarations

// variables

// function prototypes
void commandLoop(void);											// command entry loop
bool doCommand(const char *);									// console command processor
bool handle_debug(const char *);								// handle debug command
//bool handle_display(void);										// execute display command
bool handle_go(const char *);									// handle go command
//bool handle_loadfen(const char *);								// execute loadfen command
//bool handle_movelist(const char *);								// execute movelist command
//bool handle_savefen(const char *);								// execute savefen command
bool handle_isready(const char *);								// handle isready command
bool handle_ponderhit(const char *);							// handle ponderhit command
bool handle_position(const char *);								// handle position command
bool handle_register(const char *);								// handle register command
bool handle_setoption(const char *);							// handle setoption command
bool handle_stop(const char *);									// handle stop command
bool handle_uci(const char *);									// handle uci command
bool handle_ucinewgame(const char *);							// handle ucinewgame command
//void initializeTables(void);									// initialize global tables
int parseCommand(const char *);									// return switch token for command received
bool tellGUI(string);											// write string to GUI via console
bool writeLog(string);											// write console command exchanges to log file
