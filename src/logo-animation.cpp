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

  // initialize values needed for random character printing
  int numLines = filecontents.size();
  int numCols = filecontents.at(0).size(); // FIXME assumes all lines are same length (and 1 exists)
  vector<int> nonSpaceCoords;
  for( int l = 0 ; l < numLines ; l++ ) {
    for( int c = 0 ; c < numCols ; c++ ) {
      if (filecontents.at(l).at(c) != ' ') {
        nonSpaceCoords.push_back(l * numCols + c);
      }
    }
  }
  random_shuffle(nonSpaceCoords.begin(), nonSpaceCoords.end());

  // initialize curses screen
	initscr();
  curs_set(0);
  noecho();

  // perform startup animations
  animate_printRandomNonSpaces(nonSpaceCoords, filecontents, numCols);
  animate_printRandomSpaces(nonSpaceCoords, filecontents, numCols);
  animate_wave(filecontents, numLines, numCols, false);
  animate_wave(filecontents, numLines, numCols, true);

  // await user instruction for further animations
  for (;;) {
    char c = getch();
    if (c == 'q') {
      break;
    }
    if (c == 'w') {
      animate_wave(filecontents, numLines, numCols, true);
    }
  }

  // end curses window
	endwin();

  return 0;
}
