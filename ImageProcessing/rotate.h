#ifndef ROTATE_H
#define ROTATE_H

#include "decorator.h"

class Rotate: public Decorator {
    void copy(std::vector<Pixel> &from, std::vector<Pixel> &to, int a, int b);
public:
    explicit Rotate(Image *image);
    void render(PPM &ppm) override;
};
#endif
