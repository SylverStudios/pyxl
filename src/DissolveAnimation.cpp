#include "DissolveAnimation.h"
using namespace std;

DissolveAnimation::DissolveAnimation(
  long numLines,
  long numCols,
  long startTime,
  long duration,
  long maxFrames,
  vector<long> nonSpaceCoords,
  bool fadeIn
): Animation(numLines, numCols, startTime, duration, maxFrames) {
  this->nonSpaceCoords = nonSpaceCoords;
  this->fadeIn = fadeIn;
}

DissolveAnimation* DissolveAnimation::create(
  long numLines,
  long numCols,
  long startTime,
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
    startTime,
    duration,
    nonSpaceCoords.size(),

    nonSpaceCoords,
    fadeIn
  );
}

/**
 * Chooses random non-space characters to print / erase
 */
vector<vector<PixelState> >* DissolveAnimation::computeFrame(long currentTime) {
  int currentFrame = (currentTime - startTime) / frameDuration;
  if (currentFrame > maxFrames) {
    return nullptr;
  }

  vector<vector<PixelState> >* canvasState = getBlankFrameState();
  // the one new showing pixel
  int coord = nonSpaceCoords.at(currentFrame);
  int lineCoord = coord / numCols;
  int colCoord = coord % numCols;
  canvasState->at(lineCoord)[colCoord] = fadeIn ? ON : OFF;
  return canvasState;
}
