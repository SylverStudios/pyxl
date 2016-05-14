#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ncurses.h>
using namespace std;

#define NEWLINE        "\n"

void fileToStringVector(vector<string> *);

int main ()
{
  vector<string> filecontents;
	fileToStringVector(&filecontents);
	WINDOW * stdscr = initscr();			/* Start curses mode 		  */
  for (int i = 0; i < filecontents.size() ; i++) {
    printw(filecontents.at(i).c_str());
    printw(NEWLINE);
  }
	refresh();			/* Print it on to the real screen */

	getch();			/* Wait for user input */
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
