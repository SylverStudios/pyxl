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

void DissolveAnimation::applyFrame(vector<vector<PixelState> >* canvas, long frame) {
  int coord = nonSpaceCoords.at(frame);
  int lineCoord = coord / numCols;
  int colCoord = coord % numCols;
  canvas->at(lineCoord)[colCoord] = fadeIn ? ON : OFF;
}

/**
 * Chooses random non-space characters to print / erase
 */
vector<vector<PixelState> >* DissolveAnimation::computeFrame(long currentTime) {
  long currentFrame = (currentTime - startTime) / frameDuration;
  vector<long> applicableFrames = getApplicableFrames(currentFrame);
  if (applicableFrames.size() == 0) {
    return nullptr;
  }

  vector<vector<PixelState> >* canvas = getBlankFrameState();
  for (int i = 0; i < applicableFrames.size(); i++) {
    applyFrame(canvas, applicableFrames[i]);
  }

  return canvas;
}
