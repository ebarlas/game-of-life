#include "Dimension.h"

using namespace gameoflife;

Dimension::Dimension(int w, int h) : width(w), height(h) {

}

int Dimension::getWidth() const {
    return width;
}

int Dimension::getHeight() const {
    return height;
}