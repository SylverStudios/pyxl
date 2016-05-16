#ifndef RIPPLE_ANIMATION_H
#define RIPPLE_ANIMATION_H

#include "Animation.h"

class RippleAnimation : public Animation
{
protected:
  void applyFrame(std::vector<std::vector<PixelState> >* canvas, long frame);
public:
  static RippleAnimation* create(long numLines, long numCols, long startTime, long duration);
  RippleAnimation(long numLines, long numCols, long startTime, long duration, long maxFrames)
    : Animation(numLines, numCols, startTime, duration, maxFrames) {};
};

#endif
