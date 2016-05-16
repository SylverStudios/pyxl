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

enum PixelState { IMPARTIAL, ON, OFF };

class Animation
{
  int numLines;
  int numCols;
  long startTime;
  long duration;
public:
  Animation(int numLines, int numCols, long startTime, long duration);
  std::vector<std::vector<PixelState> >* computeFrame(long currentTime);
};

#endif
