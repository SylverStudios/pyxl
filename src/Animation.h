#ifndef ANIMATION_H
#define ANIMATION_H

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "Logging.h"

enum PixelState { IMPARTIAL, ON, OFF };

class Animation
{
  long lastAppliedFrame;
protected:
  long numLines;
  long numCols;
  long startTime;
  long duration;
  long maxFrames;
  long frameDuration;

  std::vector<long> getApplicableFrames(long currentFrame);

  std::vector<std::vector<PixelState> >* getBlankFrameState();

public:
  Animation(
    long numLines,
    long numCols,
    long startTime,
    long duration,
    long maxFrames
  );
  virtual std::vector<std::vector<PixelState> >* computeFrame(long currentTime) =0;
};

#endif
