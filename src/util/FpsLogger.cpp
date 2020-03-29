#include "FpsLogger.h"

namespace gameoflife {
    FpsLogger::FpsLogger(std::ostream &os) :
            out(os), frames(0), thisSecond(0), lastSecond(static_cast<int>(timer.elapsed())) {
    }

    void FpsLogger::increment() {
        thisSecond = (int) timer.elapsed();
        if (thisSecond == lastSecond) {
            frames++;
        } else {
            out << frames << std::endl;
            frames = 1;
        }
        lastSecond = thisSecond;
    }
}