#include "DissolveAnimation.h"
using namespace std;

DissolveAnimation::DissolveAnimation(
  long numLines,
  long numCols,
  long duration,
  long maxFrames,
  vector<long> nonSpaceCoords,
  bool fadeIn
): Animation(numLines, numCols, duration, maxFrames) {
  this->nonSpaceCoords = nonSpaceCoords;
  this->fadeIn = fadeIn;
}

DissolveAnimation* DissolveAnimation::create(
  long numLines,
  long numCols,
  long duration,
  vector<string> characters,
  bool fadeIn
) {
  vector<long> nonSpaceCoords;
  for( int l = 0 ; l < numLines ; l++ ) {
    for( int c = 0 ; c < numCols ; c++ ) {
      if (characters.at(l).at(c) != ' ') {
        nonSpaceCoords.push_back(l * numCols + c);
      }
    }
  }
  random_shuffle(nonSpaceCoords.begin(), nonSpaceCoords.end());
  return new DissolveAnimation(
    numLines,
    numCols,
    duration,
    nonSpaceCoords.size(),
    nonSpaceCoords,
    fadeIn
  );
}

void DissolveAnimation::applyFrame(vector<vector<PixelState> >* canvas, long frame) {
  int coord = nonSpaceCoords.at(frame);
  int lineCoord = coord / numCols;
  int colCoord = coord % numCols;
  canvas->at(lineCoord)[colCoord] = fadeIn ? ON : OFF;
}
