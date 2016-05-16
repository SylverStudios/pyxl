#include "DissolveAnimation.h"
using namespace std;

DissolveAnimation::DissolveAnimation(
  int numLines,
  int numCols,
  long startTime,
  long duration,
  vector<string> characters,
  bool fadeIn
): Animation(numLines, numCols, startTime, duration) {
  vector<int> nonSpaceCoords;
  for( int l = 0 ; l < numLines ; l++ ) {
    for( int c = 0 ; c < numCols ; c++ ) {
      if (characters.at(l).at(c) != ' ') {
        nonSpaceCoords.push_back(l * numCols + c);
      }
    }
  }
  random_shuffle(nonSpaceCoords.begin(), nonSpaceCoords.end());
  this->nonSpaceCoords = nonSpaceCoords;
  this->fadeIn = fadeIn;
}

/**
 * Chooses random non-space characters to print / erase
 */
vector<vector<PixelState> >* DissolveAnimation::computeFrame(long currentTime) {
  logf("computeFrame");
  logf("\tcurrentTime: " + to_string(currentTime));
  float percentThrough = ((float) currentTime - (float) startTime) / duration;
  logf("\tpercentThrough: " + to_string(percentThrough));
  if (percentThrough >= 1) {
    return nullptr;
  }
  int maxFrames = nonSpaceCoords.size();
  logf("\tmaxFrames: " + to_string(maxFrames));
  long frameDuration = duration / maxFrames;
  logf("\tframeDuration: " + to_string(frameDuration));
  int currentFrame = (currentTime - startTime) / frameDuration;
  logf("\tcurrentFrame: " + to_string(currentFrame));
  static vector<vector<PixelState> > canvasState (
    numLines,
    vector<PixelState> (numCols, IMPARTIAL)
  );

  // the one new showing pixel
  int coord = nonSpaceCoords.at(currentFrame);
  int lineCoord = coord / numCols;
  int colCoord = coord % numCols;
  canvasState[lineCoord][colCoord] = fadeIn ? ON : OFF;
  return &canvasState;
}
