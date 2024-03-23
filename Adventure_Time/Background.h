#pragma once

#include <SDL.h>
class Background
{
public:
    Background();

    virtual void drawBackground();
    virtual void updateBackground();

    ~Background();
private:
    SDL_Rect mSrc1;
    SDL_Rect mSrc2;
    SDL_Rect mDest1;
    SDL_Rect mDest2;

    int mWindowsWidth;
    int mWindowsHeight;
    int mScrollSpeed;
    int mCountTime;

    void reset();
};
