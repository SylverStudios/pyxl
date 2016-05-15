#ifndef ANIMATION_ENGINE_H
#define ANIMATION_ENGINE_H

#define PI 3.14159265

#include <vector>
#include <string>
#include <math.h>
#include <ncurses.h>

void animate_printRandomNonSpaces(
  std::vector<int> nonSpaceCoords,
  std::vector<std::string> filecontents,
  int numCols
);

void animate_printRandomSpaces(
  std::vector<int> nonSpaceCoords,
  std::vector<std::string> filecontents,
  int numCols
);

void animate_wave(std::vector<std::string> filecontents, int numLines, int numCols, bool stayUp);

#endif