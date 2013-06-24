#ifndef NEIGHBOR_H
#define NEIGHBOR_H

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

class Neighbor
{
public:
    char* data;
    int width;
    int size;
public:
    //n is the width of the neighborhood
    //x & y are the horizontal and vertical coordinates
    Neighbor();
    Neighbor(IplImage* img, int x, int y, int n);
    void set(IplImage* img, int x, int y, int n);
    ~Neighbor();
    int getRGB(int index, int type);
    double difNeighbor(Neighbor *neighbor);

public:
    void getColor(IplImage* img, int x, int y, char* color);
    double L2Norm(char* color1, char* color2);
    int getCoor(int x, int n);
    int char2int(char c);
};

#endif // NEIGHBOR_H
