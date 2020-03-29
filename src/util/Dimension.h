#ifndef GAMEOFLIFE_DIMENSION_H
#define GAMEOFLIFE_DIMENSION_H

namespace gameoflife {
    class Dimension {
    public:
        Dimension(int width, int height);
        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;
    private:
        const int width;
        const int height;
    };
}

#endif
