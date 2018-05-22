#ifndef FLIP_H
#define FLIP_H

#include "decorator.h"

class Flip: public Decorator {
    void flipX(std::vector<Pixel> &pixels, int a, int b);
public:
    explicit Flip(Image *image);
    void render(PPM &ppm) override;

};
#endif
