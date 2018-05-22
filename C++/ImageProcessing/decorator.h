#ifndef DECOR_H
#define DECOR_H

#include "image.h"

class Decorator: public Image {
protected:
    Image *image;
public:
    explicit Decorator(Image *image);
    virtual ~Decorator();
};

//Helper Functions
void swapComponent(std::vector<Pixel> &pixels1, std::vector<Pixel> &pixels2, int index1, int index2, char which);
unsigned int getComponent(Pixel &pixel, char i1);
void setComponent(int i, std::vector<Pixel> &pixels, unsigned int val, char i1);
#endif
