#include "Animation.h"
using namespace std;

Animation::Animation(int numLines, int numCols, long startTime, long duration) {
  logf("Animation constructor");
  this->numLines = numLines;
  this->numCols = numCols;
  this->startTime = startTime;
  logf("\tstartTime: " + to_string(startTime));
  this->duration = duration / 1000 * CLOCKS_PER_SEC ; // milliseconds to clock ticks
  logf("\tduration: " + to_string(duration) + " -> " + to_string(this->duration));
}
