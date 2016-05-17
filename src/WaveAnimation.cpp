#include "WaveAnimation.h"
using namespace std;

WaveAnimation::WaveAnimation(
  long numLines,
  long numCols,
  long startTime,
  long duration,
  long maxFrames,
  long waveWidth
) : Animation(numLines, numCols, startTime, duration, maxFrames){
  this->waveWidth = waveWidth;
}

WaveAnimation* WaveAnimation::create(
  long numLines,
  long numCols,
  long startTime,
  long duration,
  long waveWidth
) {
  return new WaveAnimation(
    numLines,
    numCols,
    startTime,
    duration,
    numCols + waveWidth,
    waveWidth
  );
}

vector<vector<PixelState> >* WaveAnimation::fullWaveFrame(long frame) {
  // wave (visible characters are the water) from left to right
  vector<vector<PixelState> > * canvas =
    new vector<vector<PixelState> > (numLines, vector<PixelState>(numCols, IMPARTIAL));
  vector<int> waveColHeights;
  waveColHeights.assign(numCols, 0);
  int waveBack = frame - waveWidth;
  for ( int c = 0 ; c < waveColHeights.size() ; c++ ) {
    // must be in wave
    if (frame < c || c < waveBack) {
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
        canvas->at(l)[c] = ON;
      } else {
        canvas->at(l)[c] = OFF;
      }
    }
  }
  return canvas;
}

void WaveAnimation::applyFrame(vector<vector<PixelState> >* canvas, long frame) {
  vector<vector<PixelState> >* currentFrame = fullWaveFrame(frame);
  if (frame == 0) {
    for (int l = 0; l < numLines; l++) {
      for (int c = 0; c < numCols; c++) {
        PixelState currentPixelState = currentFrame->at(l)[c];
        if (currentPixelState == ON) {
          canvas->at(l)[c] = currentPixelState;
        }
      }
    }
  } else {
    vector<vector<PixelState> >* previousFrame = fullWaveFrame(frame - 1);
    for (int l = 0; l < numLines; l++) {
      for (int c = 0; c < numCols; c++) {
        PixelState currentPixelState = currentFrame->at(l)[c];
        if (currentPixelState != previousFrame->at(l)[c]) {
          canvas->at(l)[c] = currentPixelState;
        }
      }
    }
  }
}