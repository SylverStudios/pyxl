#include "Animation.h"
using namespace std;

vector<vector<PixelState> >* Animation::getBlankFrameState() {
  static vector<vector<PixelState> > blankState;
  blankState.assign(
    numLines,
    vector<PixelState> (numCols, IMPARTIAL)
  );
  return &blankState;
}

vector<long>* Animation::getApplicableFrames(long currentFrame) {
  logf("applicable frames");
  logf("\tcurrentFrame: " + to_string(currentFrame));
  vector<long>* applicableFrames = new vector<long>;
  for (int f = lastAppliedFrame + 1; f <= currentFrame && f < maxFrames ; f++) {
    applicableFrames->push_back(f);
  }
  if (applicableFrames->size() == 0 && currentFrame >= maxFrames) {
    return nullptr;
  }
  lastAppliedFrame = currentFrame;
  return applicableFrames;
}

vector<vector<PixelState> >* Animation::computeFrame(long currentTime) {
 long currentFrame = (currentTime - startTime) / frameDuration;
 vector<long>* applicableFrames = getApplicableFrames(currentFrame);
 if (applicableFrames == nullptr) {
   return nullptr;
 }
 vector<vector<PixelState> >* canvas = getBlankFrameState();
 for (int i = 0; i < applicableFrames->size(); i++) {
   applyFrame(canvas, applicableFrames->at(i));
 }
 return canvas;
}

Animation::Animation(
  long numLines,
  long numCols,
  long startTime,
  long duration,
  long maxFrames
) {
  logf("Animation constructor");
  this->numLines = numLines;
  this->numCols = numCols;
  this->startTime = startTime;
  logf("\tstartTime: " + to_string(startTime));
  this->duration = duration / 1000 * CLOCKS_PER_SEC ; // milliseconds to clock ticks
  logf("\tduration: " + to_string(duration) + " -> " + to_string(this->duration));
  this->maxFrames = maxFrames;
  logf("\tmaxFrames: " + to_string(maxFrames));
  this->frameDuration = this->duration / maxFrames;
  logf("\tframeDuration: " + to_string(frameDuration));
  this->lastAppliedFrame = -1;
}
