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
class AnimationEngine
{
  int numLines;
  int numCols;
  std::vector<std::string> characters;
  std::vector<int> nonSpaceCoords;
public:
  AnimationEngine(std::vector<std::string> characters);
  void animate_printRandomNonSpaces();
  void animate_printRandomSpaces();
  void animate_wave(bool stayUp);
};

#endif
