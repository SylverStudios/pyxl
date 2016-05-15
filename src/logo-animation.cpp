#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

#define NEWLINE        "\n"
#define PI 3.14159265

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

void wait ( int milliseconds )
{
  clock_t endwait;
  endwait = clock () + milliseconds * CLOCKS_PER_SEC / 1000 ;
  while (clock() < endwait) {}
}

void animate_printRandomNonSpaces(
  vector<int> nonSpaceCoords,
  vector<string> filecontents,
  int numCols
 ) {
  // loop through non-space coords and print them at appropriate coordinates
  for ( int i = 0 ; i < nonSpaceCoords.size() ; i++ ) {
    int coord = nonSpaceCoords.at(i);
    int lineCoord = coord / numCols;
    int colCoord = coord % numCols;
    string line = filecontents.at(lineCoord);
    char character = line.at(colCoord);
    mvaddch(lineCoord, colCoord, character);
    refresh();
    wait(3);
  }
}

void animate_printRandomSpaces(
  vector<int> nonSpaceCoords,
  vector<string> filecontents,
  int numCols
) {
  // // loop through non-space coords and print a space there
  for ( int i = 0 ; i < nonSpaceCoords.size() ; i++ ) {
    int coord = nonSpaceCoords.at(i);
    int lineCoord = coord / numCols;
    int colCoord = coord % numCols;
    mvaddch(lineCoord, colCoord, ' ');
    refresh();
    wait(3);
  }
}

void animate_wave(vector<string> filecontents, int numLines, int numCols, bool stayUp) {
  // wave (visible characters are the water) from left to right
  vector<int> waveColHeights;
  waveColHeights.assign(numCols, 0);
  int waveWidth = numCols; // TODO make this adjustable
  int currentTick = 0; // front of the wave
  bool waveFinished = false;
  float speed = 14;
  while (!waveFinished) {
    currentTick++;
    int waveBack = currentTick - waveWidth;
    for ( int c = 0 ; c < waveColHeights.size() ; c++ ) {
      if (stayUp && c < waveBack + waveWidth / 2) {
        waveColHeights[c] = numLines;
      }
      // must be in wave
      else if (currentTick < c || c < waveBack) {
        waveColHeights[c] = 0;
      } else {
        int distanceFromBack = c - waveBack;
        int colHeight = sin( (float) distanceFromBack * PI / (float) waveWidth ) * numLines;
        waveColHeights[c] = colHeight;
      }
    }
    for ( int c = 0 ;  c < waveColHeights.size() ; c++ ) {
      for ( int l = 0 ; l < numLines ; l++ ) {
        if ( waveColHeights[c] >= numLines - l ) {
          mvaddch(l, c, filecontents.at(l).at(c));
        } else {
          mvaddch(l, c, ' ');
        }
      }
    }
    refresh();
    speed -= 0.05;
    wait((int) speed);
    bool anyColHasHeight = false;
    bool allColsHaveHeight = true;
    for ( int c = 0 ; c < waveColHeights.size() ; c++ ) {
      if (waveColHeights[c] > 0) {
        anyColHasHeight = true;
      }
      if (waveColHeights[c] != numLines) {
        allColsHaveHeight = false;
      }
    }
    waveFinished = currentTick > waveWidth &&
     ((!stayUp && !anyColHasHeight) || (stayUp && allColsHaveHeight));
  }
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
