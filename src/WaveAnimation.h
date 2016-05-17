#ifndef WAVE_ANIMATION_H
#define WAVE_ANIMATION_H

#include "Animation.h"

#define PI 3.14159265

class WaveAnimation : public Animation
{
  long waveWidth;
  std::vector<std::vector<PixelState> >* fullWaveFrame(long frame);
protected:
  void applyFrame(std::vector<std::vector<PixelState> >* canvas, long frame);
public:
  static WaveAnimation* create(
    long numLines,
    long numCols,
    long startTime,
    long duration,
    long waveWidth
  );
  WaveAnimation(
    long numLines,
    long numCols,
    long startTime,
    long duration,
    long maxFrames,
    long waveWidth
  );
};

#endif
