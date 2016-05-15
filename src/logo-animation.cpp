#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

#define NEWLINE        "\n"

void fileToStringVector(vector<string> *);
void wait(int);

int main ()
{
  // get contents of text file
  vector<string> filecontents;
	fileToStringVector(&filecontents);

  // initialize values needed for random character printing
  int numLines = filecontents.size();
  int numCols = filecontents.at(0).size(); // FIXME assumes all lines are same length (and 1 exists)
  int totalCoords = numLines * numCols;
  vector<int> unprintedCoords;
  for( int i = 0 ; i < totalCoords ; i++ ) {
    unprintedCoords.push_back(i);
  }
  random_shuffle(unprintedCoords.begin(), unprintedCoords.end());

  // initialize curses screen
	initscr();
  curs_set(0);

  // loop through characters in text file, print them to screen at appropriate coordinates
  srand (time(NULL));
  for ( int i = 0 ; i < totalCoords ; i++ ) {
    int coord = unprintedCoords.at(i);
    int lineCoord = coord / numCols;
    int colCoord = coord % numCols;
    string line = filecontents.at(lineCoord);
    char character = line.at(colCoord);
    mvaddch(lineCoord, colCoord, character);
    refresh();
    wait(10);
  }
  getch();
	endwin();			/* End curses mode		  */
	return 0;
}

void wait ( int milliseconds )
{
  clock_t endwait;
  endwait = clock () + milliseconds * CLOCKS_PER_SEC / 1000 ;
  while (clock() < endwait) {}
}

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
