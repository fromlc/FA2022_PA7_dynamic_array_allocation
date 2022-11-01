//------------------------------------------------------------------------------
// input_util.cpp
// 
// console input tools
//------------------------------------------------------------------------------
#include "input_util.h"

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
string g_input;
string g_intPrompt = "\nEnter a positive integer or Q to quit: ";
string g_errorPrompt = "That's not a positive integer.";

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
bool _getConsoleInt(int& intInput);

//------------------------------------------------------------------------------
// handler for ctrl-c console input
// 
// sets keepRunning to 0 on ctrl-c entered (SIGINT)
//------------------------------------------------------------------------------
namespace {
	volatile sig_atomic_t keepRunning = 1;

	void handleCtrlC(int x) {
		keepRunning = 0;
	}
}

//------------------------------------------------------------------------------
// get one positive integer from console input
// 
// prompt is optional parameter, g_intPrompt used by default
//------------------------------------------------------------------------------
int getConsoleInt(const string& prompt) {

	// set user prompt to passed string
	if (!prompt.empty()) {
		g_intPrompt = prompt;
	}

	// set up ctrl-c handler
	signal(SIGINT, handleCtrlC);

	int intInput;
	while (!_getConsoleInt(intInput)) {
		cerr << g_errorPrompt << '\n';
	}

	// return validated int
	return intInput;
}

//------------------------------------------------------------------------------
// loop to get positive integer input
// 
// throws UserQuitException on quit command
//------------------------------------------------------------------------------
bool _getConsoleInt(int& intInput) {

	// ask user to enter an int
	cout << g_intPrompt;
	getline(cin, g_input);
	stringstream ss(g_input);

	// check for user wants to quit
	if (!ss.str().compare("q") || !ss.str().compare("Q"))
		throw UserQuitException();

	// register exceptions we handle in catch blocks
	ss.exceptions(stringstream::failbit | stringstream::badbit);

	try {
		ss >> intInput;
		return validateInt(intInput);
	}
	catch (stringstream::failure e) {
		// timing loop waits for possible signal
		for (int i = 0; i < IU_WAIT; i++);

		if (!keepRunning) {
			// signal was set by handleCtrlC() on SIGINT
			cerr << "^C\n";
			exit(IU_CONTROLC);
		}
		return false;
	}
}

//------------------------------------------------------------------------------
// integer greater than or equal to zero input validation
//------------------------------------------------------------------------------
bool validateInt(int intInput) {

	return (intInput >= 0) ? true : false;
}

//------------------------------------------------------------------------------
// set strings for prompting user and displaying error
//------------------------------------------------------------------------------
void setPrompts(const string& prompt, const string& errorStr) {
	g_intPrompt = prompt;
	g_errorPrompt = errorStr;
}

