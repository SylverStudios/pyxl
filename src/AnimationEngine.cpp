#include "AnimationEngine.h"
using namespace std;

void wait ( int milliseconds )
{
  clock_t endwait;
  endwait = clock () + milliseconds * CLOCKS_PER_SEC / 1000 ;
  while (clock() < endwait) {}
}

AnimationEngine::AnimationEngine(vector<string> characters) {
  this->characters = characters;
  numLines = characters.size();
  numCols = characters.at(0).size(); // FIXME assumes all lines are same length (and 1 exists)
  this->mainLoop();
}

void AnimationEngine::mainLoop() {
  vector<Animation*> activeAnimations;

  /**
   * Initial animations
   */
  Animation* initialFadeIn = DissolveAnimation::create(numLines, numCols, 1200, characters, true);
  Animation* initialFadeOut = DissolveAnimation::create(numLines, numCols, 1200, characters, false);
  Animation* initialWave = WaveAnimation::create(numLines, numCols, 1400, numCols, false);
  Animation* secondaryWave = WaveAnimation::create(numLines, numCols, 1400, numCols, true);
  initialFadeIn->chainAnimation(initialFadeOut);
  initialFadeOut->chainAnimation(initialWave);
  initialWave->chainAnimation(secondaryWave);
  activeAnimations.push_back(initialFadeIn);

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
        activeAnimations.push_back(RippleAnimation::create(numLines, numCols, 3000));
        break;
      case 'o': // fade [o]ut
        activeAnimations.push_back(
          DissolveAnimation::create(numLines, numCols, 1200, characters, false)
        );
        break;
      case 'i': // fade [i]n
        activeAnimations.push_back(
          DissolveAnimation::create(numLines, numCols, 1200, characters, true)
        );
        break;
      case 'w': // [w]ave
        activeAnimations.push_back(
          WaveAnimation::create(numLines, numCols, 1400, numCols, false)
        );
        break;
      case 'u': // wave, stay [u]p
        activeAnimations.push_back(
          WaveAnimation::create(numLines, numCols, 1400, numCols, true)
        );
        break;
    }
    // step through each active animation and build a canvas
    vector<vector<PixelState> > canvas (numLines, vector<PixelState>(numCols, IMPARTIAL));
    for ( int a = 0; a < activeAnimations.size() ; a++ ) {
      Animation* activeAnimation = activeAnimations[a];
      vector<vector<PixelState> >* animationCanvas = activeAnimation->computeFrame(currentTime);
      if ( animationCanvas == nullptr ) {
        logf("mainloop, erasing index: " + to_string(a));
        Animation* chainedAnimation = activeAnimation->getChainedAnimation();
        if (chainedAnimation != nullptr) {
          logf("\tchainedAnimation found");
          activeAnimations.push_back(chainedAnimation);
        }
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
