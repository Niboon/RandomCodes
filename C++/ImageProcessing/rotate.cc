#include "rotate.h"

using namespace std;


Rotate::Rotate(Image *image) : Decorator{image} {}

void Rotate::render(PPM &ppm) {
    image->render(ppm);
    // Rotate Image 90 deg CW
    std::vector<Pixel> &pixels = ppm.getPixels();
    int width = ppm.getWidth();
    int height = ppm.getHeight();
    std::vector<Pixel> temps{pixels};
    for (int x=0; x < width; ++x) {
        for (int y=0; y < height; ++y) {
            copy(pixels, temps, x * height + y, width * (height - y - 1) + x);
        }
    }
    pixels=temps;
    int &widthSetting = ppm.getWidth();
    widthSetting = height;
    int &heightSetting = ppm.getHeight();
    heightSetting = width;
}

void Rotate::copy(std::vector<Pixel> &from, std::vector<Pixel> &to, int a, int b) {
    setComponent(a, to, getComponent(from[b],'r'), 'r');
    setComponent(a, to, getComponent(from[b],'g'), 'g');
    setComponent(a, to, getComponent(from[b],'b'), 'b');
}
