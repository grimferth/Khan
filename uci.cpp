/*************************************************************************************************************************************
 * Name:        uci.cpp
 * Purpose:     C routines to handle all interactions with GUI front-end
 * Licence:     GNU GPL v3.0 (29 June 2007)
 * Copyright:   2015(c) Stephen Wunschel
 *************************************************************************************************************************************/

// standard header files
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// project header files
#include "common.h"												// definitions shared by entire project
#include "extglobal.h"											// external definitions for global variables
#include "uci.h"												// definitions

/*************************************************************************************************************************************
 * commandLoop - console command loop
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
void commandLoop()
{
	//local variables
	int next_char;												// next character
	char cmd_buffer[MAX_CMD_BUFF];
	int count = 0;												// index into command buffer

	// read a command and call doCommand:
	while ((next_char=getc(stdin)) != EOF)						// read characters until end of file
	{
		if (next_char == '\n')										// if next char is a newline then -
		{
			cmd_buffer[count] = '\0';									// write end of string
			if (LOGFLAG)												// if logging
				writeLog("Arena: " + string(cmd_buffer));					// then write command buffer to log
			if (!doCommand(cmd_buffer))									// execute the command, if returns false
				return;														// return to caller
			count = 0;												// reset index
		}
		else													// else - handle next character
		{
			if (count >= MAX_CMD_BUFF-1)						// check to see if command buffer will be overrun
				count = 0;											// and reset index into command buffer
			cmd_buffer[count++] = next_char;					// copy char into buffer and increment pointer
		}
	}
}

/*************************************************************************************************************************************
 * doCommand - console command processor
 *
 * Khan will be implementing the universal chess interface (UCI) protocol for communicating with a compliant GUI front-end, with
 * some supplemental commands added for when Khan is used in console mode only
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool doCommand(const char *input_buffer)
{
	// local variables
	int token;													// token for switch structure

	// return when command buffer is empty
	if (!strcmp(input_buffer, ""))
		return true;

	// parse command if possible
	token = parseCommand(input_buffer);

	// act on command
	switch (token)
	{
		// standalone commands
		// UCI compliant commands
		case debug:
			handle_debug(input_buffer);
			return true;
		case go:
			handle_go(input_buffer);
			return true;
		case isready:
			handle_isready(input_buffer);
			return true;
		case ponderhit:
			handle_ponderhit(input_buffer);
			return true;
		case position:
			handle_position(input_buffer);
			return true;
		case quit:
			return false;
		case reg:
			handle_register(input_buffer);
			return true;
		case setoption:
			handle_setoption(input_buffer);
			return true;
		case stop:
			handle_stop(input_buffer);
			return true;
		case uci:
			handle_uci(input_buffer);
			return true;
		case ucinewgame:
			handle_ucinewgame(input_buffer);
			return true;
		// unknown commands
		case unknown:
		default:
			return true;
	}
}

/*************************************************************************************************************************************
 * handle_debug	- handle debug command
 *
 * switch the debug mode of the engine on and off. In debug mode the engine should send additional infos to the GUI, e.g. with the
 * "info string" command, to help debugging, e.g. the commands that the engine has received etc. This mode should be switched off by
 * default and this command can be sent any time, also when the engine is thinking.
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_debug(const char *buf)
{
    // local variables
    
    // process
	writeLog("Khan:  not yet coded");							// then write intext to log
	
	return true;
}

/*************************************************************************************************************************************
 * handle_go - handle go command
 *
 * start calculating on the current position set up with the "position" command. There are a number of commands that can follow
 * this command, all will be sent in the same string. If one command is not sent its value should be interpreted as it would not
 * influence the search.
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_go(const char *buf)
{
    // local variables
    
    // process
	writeLog("Khan:  not yet coded");							// then write intext to log
	
	return true;
}

/*************************************************************************************************************************************
 * handle_isready - handle isready command
 *
 * this is used to synchronize the engine with the GUI. When the GUI has sent a command or multiple commands that can take some time
 * to complete, this command can be used to wait for the engine to be ready again or to ping the engine to find out if it is still 
 * alive.  This command is also required once before the engine is asked to do any search to wait for the engine to finish
 * initializing.  This command must always be answered with "readyok" and can be sent also when the engine is calculating in which
 * case the engine should also immediately answer with "readyok" without stopping the search.
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/19/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_isready(const char *buf)
{
    // local variables
    
    // process
	tellGUI("readyok");											// required response
	
	return true;
}

/*************************************************************************************************************************************
 * handle_ponderhit - handle ponderhit command
 *
 * the user has played the expected move. This will be sent if the engine was told to ponder on the same move the user has played.
 * The engine should continue searching but switch from pondering to normal search.
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/19/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_ponderhit(const char *buf)
{
    // local variables
    
    // process
	tellGUI("readyok");											// required response
	
	return true;
}

/*************************************************************************************************************************************
 * handle_position - handle position command
 *
 * set up the position described in fenstring on the internal board and play the moves on the internal chess board; if the game was 
 * played  from the start position the string "startpos" will be sent 
 *
 * Note: no "new" command is needed. However, if this position is from a different game than the last position sent to the engine,
 * the GUI should have sent a "ucinewgame" inbetween.
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   0x/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_position(const char *buf)
{
    // local variables
	stringstream ss (stringstream::in | stringstream::out);		// parsing stringstream
	string token;												// current token

	// parse input command
	ss << string(buf);											// load parsing stringstream
	ss >> token;												// should be "POSITION"
	ss >> token;												// get subcommand
	if (token == "startpos")									// if startpos subcommand
		treeTop.Reset();											// reset top of search tree
	else 
		if (token == "fen")										// if fen subcommand
			treeTop.LoadFEN(token);									// set top of search tree to fen string
		else
			return false;
	
	//loop through move chain
	token.clear();
	ss >> token;												// get moves parm
	if (token == "moves")
	{
		token.clear();											// clear token
		ss >> token;											// get move?
		while (token != "")										// loop through moves list
		{
			treeTop.ApplyMove(token);								// make the specified move
			token.clear();											// clear token
			ss >> token;											// get next move?
		}
	}		
	writeLog("log:   " + treeTop.GetFEN());						// write boardpos to log
	
	return true;
}

/*************************************************************************************************************************************
 * handle_register - handle register command
 *
 * this is the command to try to register an engine or to tell the engine that registration will be done later. This command should
 * always be sent if the engine	has sent "registration error" at program startup.
 * The following tokens are allowed:
 *	* later
 *	   the user doesn't want to register the engine now.
 *	* name <x>
 *	   the engine should be registered with the name <x>
 *	* code <y>
 *	   the engine should be registered with the code <y>
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_register(const char *buf)
{
    // local variables
    
    // process
	writeLog("Khan:  not yet coded");							// then write intext to log
	
	return true;
}

/*************************************************************************************************************************************
 * handle_setoption - handle setoption command
 *
 * this is sent to the engine when the user wants to change the internal parameters of the engine. For the "button" type no value is
 * needed. One string will be sent for each parameter and this will only be sent when the engine is waiting. The name and value of
 * the option in <id> should not be case sensitive and can inlude spaces. The substrings "value" and "name" should be avoided in
 * <id> and <x> to allow unambiguous parsing, for example do not use <name> = "draw value".
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_setoption(const char *buf)
{
    // local variables
    
    // process
	writeLog("Khan:  not yet coded");							// then write intext to log
	
	return true;
}

/*************************************************************************************************************************************
 * handle_stop - handle stop command
 *
 * stop calculating as soon as possible, don't forget the "bestmove" and possibly the "ponder" token when finishing the search
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_stop(const char *buf)
{
    // local variables
    
    // process
	writeLog("Khan:  not yet coded");							// then write intext to log
	
	return true;
}

/*************************************************************************************************************************************
 * handle_uci - handle uci command
 *
 * tell engine to use the uci (universal chess interface), 	this will be sent once as a first command after program boot to tell the
 * engine to switch to uci mode.  After receiving the uci command the engine must identify itself with the "id" command and send the
 * "option" commands to tell the GUI which engine settings the engine supports if any.  After that the engine should send "uciok" to
 * acknowledge the uci mode.  If no uciok is sent within a certain time period, the engine task will be killed by the GUI.
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/19/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_uci(const char *buf)
{
    // local variables
    
    // process
	tellGUI("id name Khan 1.0");								// display project name and version
	tellGUI("id author Stephen Wunschel");						// display project author
	// no options at this time
	tellGUI("uciok");											// engine is ready
	
	return true;
}

/*************************************************************************************************************************************
 * handle_ucinewgame - handle ucinewgame command
 *
 * this is sent to the engine when the next search (started with "position" and "go") will be from a different game. This can be a 
 * new game the engine should play or a new game it should analyse but also the next position from a testsuite with positions only.
 * If the GUI hasn't sent a "ucinewgame" before the first "position" command, the engine shouldn't expect any further ucinewgame
 * commands as the GUI is probably not supporting the ucinewgame command. So the engine should not rely on this command even though
 * all new GUIs should support it. As the engine's reaction to "ucinewgame" can take some time the GUI should always send "isready"
 * after "ucinewgame" to wait for the engine to finish its operation.
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   10/15/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool handle_ucinewgame(const char *buf)
{
    treeTop.Reset();	
	return true;
}

/*************************************************************************************************************************************
 * parseCommand - return switch token for command received
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   xx/xx/2012   SDW   initial coding
 *************************************************************************************************************************************/
int parseCommand(const char *buf)
{
	if ((!strncmp(buf, "debug", 5))) return debug;
	if ((!strncmp(buf, "go", 2))) return go;
	if ((!strcmp(buf, "isready"))) return isready;
	if ((!strcmp(buf, "ponderhit"))) return ponderhit;
	if ((!strncmp(buf, "position", 8))) return position;
	if ((!strncmp(buf, "register", 8))) return reg;
	if ((!strncmp(buf, "setoption", 9))) return setoption;
	if ((!strcmp(buf, "stop"))) return stop;
	if ((!strcmp(buf, "quit")) || (!strcmp(buf, "exit"))) return quit;
	if ((!strcmp(buf, "uci"))) return uci;
	if ((!strcmp(buf, "ucinewgame"))) return ucinewgame;
	return unknown;
}

/*************************************************************************************************************************************
 * tellGUI - write string to GUI via console
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/20/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool tellGUI(string intext)
{
	// local variables
    
    // process
	if (LOGFLAG)												// if logging
		writeLog("Khan:  " + intext);								// then write intext to log
	std::cout << intext << std::endl;							// send text to command console
	std::cout.flush();											// flush the cout buffer
	return true;
}

/*************************************************************************************************************************************
 * writeLog - write console command exchanges to log file
 *
 * VRM      Date      By    Description
 * ===   ==========   ===   ==========================================================================================================
 * 100   09/30/2015   SDW   initial coding
 *************************************************************************************************************************************/
bool writeLog(string intext)
{
	// local variables
	ofstream outfile;

	// process
	outfile.open("KhanLog.txt", std::ofstream::app);			// open file						
	outfile << intext << std::endl;								// send text to log
	outfile.flush();											// flush the buffer
	outfile.close();											// close file

	return true;
}