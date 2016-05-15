#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

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
  // get contents of text file
  vector<string> filecontents;
	fileToStringVector(&filecontents);

  // initialize curses screen
	initscr();
  curs_set(0);
  noecho();

  // initialize AnimationEngine
  AnimationEngine engine (filecontents);

  // perform startup animations
  engine.animate_printRandomNonSpaces();
  engine.animate_printRandomSpaces();
  engine.animate_wave(false);
  engine.animate_wave(true);

  // await user instruction for further animations
  for (;;) {
    char c = getch();
    if (c == 'q') {
      break;
    }
    if (c == 'w') {
      engine.animate_wave(true);
    }
  }

  // end curses window
	endwin();

  return 0;
}
