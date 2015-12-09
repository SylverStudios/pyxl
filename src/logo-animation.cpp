#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
using namespace std;

#define NEWLINE        "\n"

void printFromFile();

int main ()
{
	printFromFile();
	return 0;
}

void printFromFile() {
	string filecontents, line;
	ifstream myfile ("text/logo.txt");
	if (myfile.is_open()) {
    while(getline(myfile, line)) {
			filecontents += line + '\n';
		}
		myfile.close();
	  cout << NEWLINE << filecontents << endl;
	} else {
		cout << "Unable to open file";
	}
}

