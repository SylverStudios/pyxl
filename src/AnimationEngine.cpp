#include "AnimationEngine.h"
using namespace std;

void wait ( int milliseconds )
{
  clock_t endwait;
  endwait = clock () + milliseconds * CLOCKS_PER_SEC / 1000 ;
  while (clock() < endwait) {}
}

AnimationEngine::AnimationEngine(vector<string> characters) {
  // initialize values needed for random character printing
  this->characters = characters;
  numLines = characters.size();
  numCols = characters.at(0).size(); // FIXME assumes all lines are same length (and 1 exists)

  // this->animate_printRandomSpaces();
  this->animate_wave(false);
  this->animate_wave(true);

  this->mainLoop();
}

void AnimationEngine::mainLoop() {
  vector<Animation*> activeAnimations;
  bool shouldExit = false;
  while (!shouldExit) {
    long currentTime = clock();
    // check for user input
    char c = getch();
    switch(c) {
      case ERR:
        break;
      case 'q': // [q]uit
        shouldExit = true;
        break;
      case 'r': // [r]ipple
        activeAnimations.push_back(RippleAnimation::create(numLines, numCols, currentTime, 3000));
        break;
      case 'o': // fade [o]ut
        activeAnimations.push_back(
          DissolveAnimation::create(numLines, numCols, currentTime, 2000, characters, false)
        );
        break;
      case 'i': // fade [i]n
        activeAnimations.push_back(
          DissolveAnimation::create(numLines, numCols, currentTime, 2000, characters, true)
        );
        break;
    }
    // step through each active animation and build a canvas
    vector<vector<PixelState> > canvas (numLines, vector<PixelState>(numCols, IMPARTIAL));
    for ( int a = 0; a < activeAnimations.size() ; a++ ) {
      vector<vector<PixelState> >* animationCanvas = activeAnimations[a]->computeFrame(currentTime);
      if ( animationCanvas == nullptr ) {
        logf("mainloop, erasing index: " + to_string(a));
        activeAnimations.erase (activeAnimations.begin() + a);
        a--;
        continue;
      }
      for ( int l = 0; l < numLines ; l++) {
        for ( int c = 0; c < numCols ; c++) {
          PixelState pixelState = animationCanvas->at(l)[c];
          if (pixelState != IMPARTIAL) {
            canvas[l][c] = pixelState;
          }
        }
      }
    }
    // print current canvas
    for ( int l = 0; l < numLines ; l++) {
      for ( int c = 0; c < numCols ; c++) {
        PixelState pixelState = canvas[l][c];
        if (pixelState == ON) {
          mvaddch(l, c, characters[l][c]);
        } else if (pixelState == OFF) {
          mvaddch(l, c, ' ');
        }
      }
    }
    wait(5);
  }
};

void AnimationEngine::animate_wave(bool stayUp) {
  // wave (visible characters are the water) from left to right
  vector<int> waveColHeights;
  waveColHeights.assign(numCols, 0);
  int waveWidth = numCols; // TODO make this adjustable
  int currentTick = 0; // front of the wave
  bool waveFinished = false;
  float speed = 14;
  while (!waveFinished) {
    currentTick++;
    int waveBack = currentTick - waveWidth;
    for ( int c = 0 ; c < waveColHeights.size() ; c++ ) {
      if (stayUp && c < waveBack + waveWidth / 2) {
        waveColHeights[c] = numLines;
      }
      // must be in wave
      else if (currentTick < c || c < waveBack) {
        waveColHeights[c] = 0;
      } else {
        int distanceFromBack = c - waveBack;
        int colHeight = sin( (float) distanceFromBack * PI / (float) waveWidth ) * numLines;
        waveColHeights[c] = colHeight;
      }
    }
    for ( int c = 0 ;  c < waveColHeights.size() ; c++ ) {
      for ( int l = 0 ; l < numLines ; l++ ) {
        if ( waveColHeights[c] >= numLines - l ) {
          mvaddch(l, c, characters.at(l).at(c));
        } else {
          mvaddch(l, c, ' ');
        }
      }
    }
    refresh();
    speed -= 0.05;
    wait((int) speed);
    bool anyColHasHeight = false;
    bool allColsHaveHeight = true;
    for ( int c = 0 ; c < waveColHeights.size() ; c++ ) {
      if (waveColHeights[c] > 0) {
        anyColHasHeight = true;
      }
      if (waveColHeights[c] != numLines) {
        allColsHaveHeight = false;
      }
    }
    waveFinished = currentTick > waveWidth &&
     ((!stayUp && !anyColHasHeight) || (stayUp && allColsHaveHeight));
  }
}
