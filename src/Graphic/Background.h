#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <SDL.h>
#include <string>
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
    std::string mID;
    
    void reset();
};

#endif // BACKGROUND_H_