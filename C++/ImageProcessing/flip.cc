#include "flip.h"

using namespace std;

Flip::Flip(Image *image): Decorator{image} {}

void Flip::render(PPM &ppm) {
    image->render(ppm);
    // Flip Image Horizontally
    std::vector<Pixel> &pixels = ppm.getPixels();
    int &width = ppm.getWidth();
    int &height = ppm.getHeight();
    for (int x=0; x < width/2; ++x) {
        for (int y = 0; y < height; ++y) {
            flipX(pixels, x+width*y, width*y+width-x-1);
        }
    }
}

void Flip::flipX(std::vector<Pixel> &pixels, int a, int b) {
    swapComponent(pixels, pixels, a, b, 'r');
    swapComponent(pixels, pixels, a, b, 'g');
    swapComponent(pixels, pixels, a, b, 'b');
}
