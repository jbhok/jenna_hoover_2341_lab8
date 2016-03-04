#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#endif

//#if defined(__linux__)
//#include <unistd.h>
//#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#endif

#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h>


class CAnimation {
    private:
        int    CurrentFrame;

        int     FrameInc;

    private:
        int     FrameRate; //Milliseconds

        long    OldTime;

    public:
        int    MaxFrames;

        bool    Oscillate;

    public:
        CAnimation();

        void OnAnimate();

    public:
        void SetFrameRate(int Rate);

        void SetCurrentFrame(int Frame);

        int GetCurrentFrame();
};

//#endif
