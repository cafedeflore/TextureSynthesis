#ifndef L2NEIGHBOR_H
#define L2NEIGHBOR_H

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "neighbor.h"
#include "rectneighbor.h"

class L2Neighbor
{
public:
    Neighbor* lowerNeighbor;    //新生成的
    RectNeighbor* upperNeighbor;    //已生成的
public:
    L2Neighbor();
    //L1Img->lower  L2Img->upper
    L2Neighbor(IplImage* L1Img, IplImage* L2Img, int x, int y, int width);
    ~L2Neighbor();
    int getRGB(int index, int type);
    double difL2Neighbor(L2Neighbor *l2Neighbor);
};

#endif // L2NEIGHBOR_H
