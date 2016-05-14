#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
using namespace std;

#define NEWLINE        "\n"

void fileToString(string *);

int main ()
{
  string filecontents;
	string test;
	fileToString(&filecontents);
	initscr();			/* Start curses mode 		  */
	printw(filecontents.c_str());	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
	return 0;
}

void fileToString(string * filecontents) {
	string line;
	ifstream myfile ("text/logo.txt");
	if (myfile.is_open()) {
    while(getline(myfile, line)) {
			*filecontents += line + '\n';
		}
		myfile.close();
	} else {
		cout << "Unable to open file";
	}
}
