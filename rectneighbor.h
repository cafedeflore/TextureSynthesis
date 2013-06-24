#ifndef RECTNEIGHBOR_H
#define RECTNEIGHBOR_H

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

class RectNeighbor
{
public:
    char* data;
    int width;
    int size;
public:
    //n is the width of the neighborhood
    //x & y are the horizontal and vertical coordinates
    RectNeighbor();
    RectNeighbor(IplImage* img, int x, int y, int n);
    ~RectNeighbor();
    double difRectNeighbor(RectNeighbor *rect);

public:
    void getColor(IplImage* img, int x, int y, char* color);
    double L2Norm(char* color1, char* color2);
    int getCoor(int x, int n);
    int char2int(char c);
};

#endif // RECTNEIGHBOR_H
