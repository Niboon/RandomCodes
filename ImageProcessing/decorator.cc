#include "decorator.h"

Decorator::Decorator(Image *image): image{image} {};
Decorator::~Decorator(){ delete image;}

//Helper Functions
unsigned int getComponent( Pixel &pixel, char which) {
    if (which=='r') return pixel.r;
    else if (which=='g') return pixel.g;
    else if (which=='b') return pixel.b;
    else return 0;
}

void setComponent(int i, std::vector<Pixel> &pixels, unsigned int val, char which) {
    if (which=='r') pixels[i].r = val;
    else if (which=='g') pixels[i].g = val;
    else if (which=='b') pixels[i].b = val;
}

void swapComponent(std::vector<Pixel> &pixels1, std::vector<Pixel> &pixels2, int index1, int index2, char which) {
    unsigned int temp = getComponent(pixels1[index1], which);
    setComponent(index1, pixels1, getComponent(pixels2[index2], which), which);
    setComponent(index2, pixels2, temp, which);
}
