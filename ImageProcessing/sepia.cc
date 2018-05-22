#include "sepia.h"

using namespace std;

Sepia::Sepia(Image *image) : Decorator{image} {}

void Sepia::render(PPM &ppm) {
    image->render(ppm);
    // Sepia Image
    std::vector<Pixel> &pixels = ppm.getPixels();
    int width = ppm.getWidth();
    int height = ppm.getHeight();
    std::vector<Pixel> temps{pixels};
    for (int x=0; x < width; ++x) {
        for (int y=0; y < height; ++y) {
            int i = x + y * width;
            Pixel &p = pixels[i];
            Pixel &t = temps[i];
            double valR = t.r * .393 + t.g * .769 + t.b * .189;
            p.r = valR < colourMax ? (unsigned int) valR : colourMax;
            double valG = t.r * .349 + t.g * .686 + t.b * .168;
            p.g = valG < colourMax ? (unsigned int) valG : colourMax;
            double valB = t.r * .272 + t.g * .534 + t.b * .131;
            p.b = valB < colourMax ? (unsigned int) valB : colourMax;
        }
    }
}
