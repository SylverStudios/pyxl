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
  std::vector<long> getApplicableFrames(long currentFrame);
  std::vector<std::vector<PixelState> >* getBlankFrameState();

protected:
  long numLines;
  long numCols;
  long startTime;
  long duration;
  long maxFrames;
  long frameDuration;

  virtual void applyFrame(std::vector<std::vector<PixelState> >* canvas, long frame) =0;

public:
  Animation(
    long numLines,
    long numCols,
    long startTime,
    long duration,
    long maxFrames
  );

  std::vector<std::vector<PixelState> >* computeFrame(long currentTime);
};

#endif
