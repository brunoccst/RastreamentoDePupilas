#ifndef OLHO_H
#define OLHO_H

#include "Pixel.h"
#include <vector>

class Olho
{
    public:
        Olho(Pixel pixels[]);
        Pixel getPixels() { return *pixels; }
    protected:
    private:
        vector<Pixel> pixels;
        Pixel getMedia();
};

#endif // OLHO_H
