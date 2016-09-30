#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "brick.h"

enum struct SplashScreenType { Intro, GAME_OVER, COMPLETED};

class SplashScreen : public Brick
{
public:
    SplashScreen(int, int, QString);
    ~SplashScreen();
    inline bool getIsSplashScreen(){ return isSplashScreen; }
    inline void setIsSplashScreen(bool splash){ this->isSplashScreen = splash; }
    inline void setType(SplashScreenType type){ this->type = type; }
    inline SplashScreenType getType(){ return this->type; }

private:
    bool isSplashScreen = true;
    SplashScreenType type = SplashScreenType::Intro;
};

#endif // SPLASHSCREEN_H
