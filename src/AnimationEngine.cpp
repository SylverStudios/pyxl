#include "AnimationEngine.h"
using namespace std;

void wait ( int milliseconds )
{
  clock_t endwait;
  endwait = clock () + milliseconds * CLOCKS_PER_SEC / 1000 ;
  while (clock() < endwait) {}
}

AnimationEngine::AnimationEngine(vector<string> characters) {
  // initialize values needed for random character printing
  this->characters = characters;
  numLines = characters.size();
  numCols = characters.at(0).size(); // FIXME assumes all lines are same length (and 1 exists)
  for( int l = 0 ; l < numLines ; l++ ) {
    for( int c = 0 ; c < numCols ; c++ ) {
      if (characters.at(l).at(c) != ' ') {
        nonSpaceCoords.push_back(l * numCols + c);
      }
    }
  }
  random_shuffle(nonSpaceCoords.begin(), nonSpaceCoords.end());
}

void AnimationEngine::animate_printRandomNonSpaces() {
  // loop through non-space coords and print them at appropriate coordinates
  for ( int i = 0 ; i < nonSpaceCoords.size() ; i++ ) {
    int coord = nonSpaceCoords.at(i);
    int lineCoord = coord / numCols;
    int colCoord = coord % numCols;
    string line = characters.at(lineCoord);
    char character = line.at(colCoord);
    mvaddch(lineCoord, colCoord, character);
    refresh();
    wait(3);
  }
}

void AnimationEngine::animate_printRandomSpaces() {
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

void AnimationEngine::animate_wave(bool stayUp) {
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
          mvaddch(l, c, characters.at(l).at(c));
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
