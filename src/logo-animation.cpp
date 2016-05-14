#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

#define NEWLINE        "\n"

void fileToStringVector(vector<string> *);

int main ()
{
  // get contents of text file
  vector<string> filecontents;
	fileToStringVector(&filecontents);

  // initialize values needed for random character printing
  int numLines = filecontents.size();
  int numCols = filecontents.at(0).size(); // FIXME assumes all lines are same length (and 1 exists)

  // initialize curses screen
	initscr();

  // loop through characters in text file, print them to screen at appropriate coordinates
  srand (time(NULL));
  for (;;) {
    int lineCoord = rand() % numLines;
    int colCoord = rand() % numCols;
    string line = filecontents.at(lineCoord);
    char character = line.at(colCoord);
    mvaddch(lineCoord, colCoord, character);
    refresh();
  }
	endwin();			/* End curses mode		  */
	return 0;
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
