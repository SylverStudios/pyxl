#ifndef DISSOLVE_ANIMATION_H
#define DISSOLVE_ANIMATION_H

#include "Animation.h"

class DissolveAnimation : public Animation
{
  std::vector<int> nonSpaceCoords;
  bool fadeIn; // false -> fade out
public:
  DissolveAnimation(
    int numLines,
    int numCols,
    long startTime,
    long duration,
    std::vector<std::string> characters,
    bool fadeIn
  );
  std::vector<std::vector<PixelState> >* computeFrame(long currentTime);
};

#endif
