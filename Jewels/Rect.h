#ifndef _RECT_H_
#define _RECT_H_

struct Rect
{
  //public:
    //Rect(int X, int Y, int W, int H):
    //    x(X), y(Y), w(W), h(H) {}
    int x;
    int y;
    int w;
    int h;
};

Rect makeRect(int X, int Y, int W, int H);
bool pointInside(Rect *r, int X, int Y);

#endif