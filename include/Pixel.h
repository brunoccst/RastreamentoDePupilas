#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
    public:
        Pixel(int x, int y);
        int getX() { return x; }
        int getY() { return y; }
    protected:
    private:
        int x;
        int y;
};

#endif // PIXEL_H
