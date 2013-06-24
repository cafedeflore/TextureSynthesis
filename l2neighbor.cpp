#include "l2neighbor.h"
#include "iostream"
using namespace std;

L2Neighbor::L2Neighbor()
{
}

L2Neighbor::L2Neighbor(IplImage* L1Img, IplImage* L2Img, int x, int y, int width) {
    lowerNeighbor = new Neighbor(L1Img, x, y, width);
    upperNeighbor = new RectNeighbor(L2Img, x/2, y/2, (width+2)/4*2+1);
}

L2Neighbor::~L2Neighbor() {
    delete lowerNeighbor;
    delete upperNeighbor;
}

int L2Neighbor::getRGB(int index, int type){
    if (index <= lowerNeighbor->size){
        return lowerNeighbor->char2int(lowerNeighbor->data[index*3+type]);
    }
    else{
        index -= lowerNeighbor->size;
        return upperNeighbor->char2int(upperNeighbor->data[index*3+type]);
    }
}

double L2Neighbor::difL2Neighbor(L2Neighbor *l2Neighbor) {
    double result = 0;
    result += lowerNeighbor->difNeighbor(l2Neighbor->lowerNeighbor);
//    cout<<result<<endl;
    result += upperNeighbor->difRectNeighbor(l2Neighbor->upperNeighbor);
//    cout<<result<<endl;
    return result;
}
