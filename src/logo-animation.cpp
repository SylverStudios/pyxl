#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define NEWLINE        "\n"

int main ()
{
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
	return 0;
}

