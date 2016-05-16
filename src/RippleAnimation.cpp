#include "RippleAnimation.h"
using namespace std;

RippleAnimation* RippleAnimation::create(
  long numLines,
  long numCols,
  long startTime,
  long duration
) {
  return new RippleAnimation(
    numLines,
    numCols,
    startTime,
    duration,
    numCols + 1
  );
}

/**
 * First frame: 1st column is off
 * Second frame: 1st column on, 2nd off
 * Third frame: 2nd column on, 3rd off
 * ...
 * Second to last frame: last column is off, 2nd to last column is on
 * Last frame: last column is on
 */
vector<vector<PixelState> >* RippleAnimation::computeFrame(long currentTime) {
  int currentFrame = (currentTime - startTime) / frameDuration;
  logf("ripple compute frame, currentTime: " + to_string(currentTime));
  logf("\tcurrentFrame: " + to_string(currentFrame));
  if (currentFrame > maxFrames) {
    return nullptr;
  }
  vector<vector<PixelState> >* canvasState = getBlankFrameState();
  // off column
  if ( currentFrame < maxFrames ) {
    for ( int l = 0 ; l < numLines ; l++ ) {
      canvasState->at(l)[currentFrame] = OFF;
    }
  }
  // on column
  if ( currentFrame >= 1 ) {
    for ( int l = 0 ; l < numLines ; l++ ) {
      canvasState->at(l)[currentFrame - 1] = ON;
    }
  }
  return canvasState;
}
