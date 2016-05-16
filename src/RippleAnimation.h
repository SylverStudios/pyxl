#ifndef RIPPLE_ANIMATION_H
#define RIPPLE_ANIMATION_H

#include "Animation.h"

class RippleAnimation : public Animation
{
public:
  RippleAnimation(int numLines, int numCols, long startTime, long duration):
    Animation(numLines, numCols, startTime, duration) {};
  std::vector<std::vector<PixelState> >* computeFrame(long currentTime);
};

#endif
