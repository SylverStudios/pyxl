#ifndef DISSOLVE_ANIMATION_H
#define DISSOLVE_ANIMATION_H

#include "Animation.h"

class DissolveAnimation : public Animation
{
  std::vector<long> nonSpaceCoords;
  bool fadeIn; // false -> fade out
protected:
  void applyFrame(std::vector<std::vector<PixelState> >* canvas, long frame);
public:
  DissolveAnimation(
    long numLines,
    long numCols,
    long startTime,
    long duration,
    long maxFrames,
    std::vector<long> nonSpaceCoords,
    bool fadeIn
  );

  static DissolveAnimation* create(
    long numLines,
    long numCols,
    long startTime,
    long duration,
    std::vector<std::string> characters,
    bool fadeIn
  );
};

#endif
