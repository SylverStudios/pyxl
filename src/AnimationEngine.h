#ifndef ANIMATION_ENGINE_H
#define ANIMATION_ENGINE_H

#define PI 3.14159265

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "Animation.h"
#include "RippleAnimation.h"
#include "DissolveAnimation.h"
#include "WaveAnimation.h"
#include "Logging.h"

class AnimationEngine
{
  long numLines;
  long numCols;
  std::vector<std::string> characters;
  std::vector<long> nonSpaceCoords;
  void mainLoop();
public:
  AnimationEngine(std::vector<std::string> characters);
  void animate_printRandomNonSpaces();
  void animate_printRandomSpaces();
  void animate_wave(bool stayUp);
};

#endif
