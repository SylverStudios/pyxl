#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

#include "Logging.h"
#include "AnimationEngine.h"

#define NEWLINE        "\n"

void fileToStringVector(vector<string> * filecontents) {
  vector<string> lines;
  string line;
	ifstream myfile ("text/logo.txt");
	if (myfile.is_open()) {
    while(getline(myfile, line)) {
      lines.push_back(line);
		}
		myfile.close();
	} else {
		cout << "Unable to open file";
	}
  *filecontents = lines;
}

int main ()
{
  logf("\n\n--------PROGRAM START--------");
  // get contents of text file
  vector<string> filecontents;
	fileToStringVector(&filecontents);

  // initialize curses screen
	initscr();
  curs_set(0);
  noecho();
  nodelay(stdscr, TRUE);

  // initialize AnimationEngine
  AnimationEngine engine (filecontents);

  // end curses window
	endwin();

  return 0;
}
