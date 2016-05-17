#include "WaveAnimation.h"
using namespace std;

WaveAnimation::WaveAnimation(
  long numLines,
  long numCols,
  long duration,
  long maxFrames,
  long waveWidth,
  long stayUp
) : Animation(numLines, numCols, duration, maxFrames){
  this->waveWidth = waveWidth;
  this->stayUp = stayUp;
}

WaveAnimation* WaveAnimation::create(
  long numLines,
  long numCols,
  long duration,
  long waveWidth,
  long stayUp
) {
  return new WaveAnimation(
    numLines,
    numCols,
    duration,
    numCols + waveWidth,
    waveWidth,
    stayUp
  );
}

vector<vector<PixelState> >* WaveAnimation::fullWaveFrame(long frame) {
  // wave (visible characters are the water) from left to right
  vector<vector<PixelState> > * canvas =
    new vector<vector<PixelState> > (numLines, vector<PixelState>(numCols, IMPARTIAL));
  vector<long> waveColHeights;
  waveColHeights.assign(numCols, 0);
  long waveBack = frame - waveWidth;
  for ( int c = 0 ; c < waveColHeights.size() ; c++ ) {
    if (stayUp && c < waveBack + waveWidth / 2) {
      waveColHeights[c] = numLines;
    }
    // must be in wave
    else if (frame < c || c < waveBack) {
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
