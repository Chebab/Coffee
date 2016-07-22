//
//  cTimer.h
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2016-07-22.
//  Copyright © 2016 Viktor Johansson. All rights reserved.
//

#ifndef cTimer_h
#define cTimer_h

#include <SDL2/SDL.h>
class chTimer {
private:
    Uint32 startTime;
    Uint32 pauseTime;
    bool started, paused;
    
public:
    chTimer(){}
    ~chTimer(){
        this->stop();
    }
    
    void start(){
        
        startTime = SDL_GetTicks();
        
        pauseTime = 0;
        started = true;
        paused = false;
    }
    void stop(){
        startTime = 0;
        pauseTime = 0;
        started = false;
        paused = false;
    }
    void pause(){
        if (paused) {
            return;
        }
        pauseTime = SDL_GetTicks();
        started = true;
        paused = true;
    }
    Uint32 GetTime(){
        if (started && paused) {
            return pauseTime - startTime;
        }
        return SDL_GetTicks() - startTime;
    }
};

#endif /* cTimer_h */
