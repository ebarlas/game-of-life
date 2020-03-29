#ifndef GAMEOFLIFE_FPSLOGGER_H
#define GAMEOFLIFE_FPSLOGGER_H

#include <iostream>
#include "ClockTimer.h"

namespace gameoflife {
    class FpsLogger {
    public:
        explicit FpsLogger(std::ostream &os);
        void increment();
    private:
        ClockTimer timer;
        std::ostream &out;
        int frames;
        int thisSecond;
        int lastSecond;
    };
};

#endif
