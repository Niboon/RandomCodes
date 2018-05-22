#ifndef SEPIA_H
#define SEPIA_H

#include "decorator.h"

class Sepia: public Decorator {
public:
    explicit Sepia(Image *image);
    void render(PPM &ppm) override;
};
#endif
